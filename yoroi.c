#include "yoroi.h"
#include "T_tables.h"
#include "Hash_DRBG/header/rand.h"

#define PRINT 0
#define ROUNDS 1
// input: s (seed) and x (input variable)
// output: rand (rand bytes, the output of hash_drbg)
int PRF(u8 *s, size_t s_len, u8 *x, size_t x_len, u8 *rand, size_t rand_len)
{
    void *ctx;
    size_t len = 50;
    unsigned char bytes[len];
    size_t seed_len = 60;  // at least 55-byte
    unsigned char seed[seed_len];
    size_t add_len = 60;
    unsigned char add[add_len];
    int ret;
    // allocate memory and initial ctx
    ret = anyan_rand_new_and_init(&ctx);

    if(ret == 0){  // return 0 if success
        ret = anyan_rand_seed(ctx, s, s_len);
    }else{
        printf("ctx new 或 init 出错！\nerror code: %d\n",ret);
        return -1;
    }

    if(ret == 0){  // return 0 if success
        ret = anyan_rand_bytes_with_add(ctx, rand, rand_len, x, x_len);
    }else{
        printf("ctx new 或 init 出错！\nerror code: %x\n",ret);
        return -1;
    }
    if (ret == 0){  // return 0 if success
#if PRINT
        printf("rand bytes: \n");
        for (int i = 0; i < rand_len; ++i)
        {
            printf("%d, ", rand[i]);
        }
        printf("\n");
#endif
    }else{
        printf("生成rand bytes出错！\nerror code: %x\n", ret);
        anyan_rand_free(ctx);
        return -1;
    }
    // 释放ctx空间
    anyan_rand_free(ctx);
    return 0;
}

// master_key is the list of 8-bit
// round_key is the list of 4-bit
void present_keyschedule_12(u8 *master_key, u8 *round_key){  // the bit size of a round_key is 12 
  u8 tmp[10];
  for(int i = 0; i < ROUNDS+1; ++i){
    // rotated right shift 19-bit
    for(int j = 0; j < 10; ++j)
      tmp[j] = (master_key[2+j % 10] >> 3) + ((master_key[3+j % 10]^7) << 5);
    for(int j = 0; j < 10; ++j)
      master_key[j] = tmp[j];
    
    // the most significant 4-bit through the PRESENT S-box
    master_key[9] = (SBOX_4[master_key[9]>>4] << 4) + (master_key[9]&0xf);

    // the bits k19k18k17k16k15 is exclusive-ored with the round_counter
    master_key[1] = master_key[1] ^ ((i&0x01)<<7);  // k15 ^ round_counter[0]
    master_key[2] = master_key[2] ^ ((i&0x1e)>>1);  // k19k18k17k16 ^ round_counter[1]~[4]

    // a round_key consists the last significant 12-bit
    round_key[i*3] = master_key[0]&0xf;
    round_key[i*3+1] = (master_key[0]>>4)&0xf;
    round_key[i*3+2] = master_key[1]&0xf;
  }
}

// Small Scale Variants of PRESENT
// state and subkey is the list of 4-bit
void present_enc_12(u8 *state, u8 *subkey){  // the bit size of a block is 12
  u8 r = 1;
  u8 p;
  u32 t;
  // generateRoundKeys()
#if PRINT
  printf("1\n");
  print_bytes_(state, 3);
  print_bytes_(subkey, 3);
#endif
  // 0~(r-1)-th rounds, where r = 10
  for(int i = 0; i < ROUNDS; ++i){
    // addRoundKey
    for(int j = 0; j < 3; ++j){
      state[j] = state[j] ^ subkey[i*3 + j];
    }
#if PRINT
    printf("2\n");
    print_bytes_(state, 3);
#endif
    // sBoxLayer
    for(int j = 0; j < 3; ++j){
      state[j] = SBOX_4[state[j]];
    }
#if PRINT
    printf("3\n");
    print_bytes_(state, 3);
#endif
    // pLayer
    // the 12-bit state is denoted as s11s10...s1s0
    t = 0;  // t is the ans of bit permutation
    for(int j = 2; j >= 0; --j){
      for(int n = 0; n < 4; ++n){
        if((2-j)*4+n < 11){
          p = 3*((2-j)*4+n) % 11;  // P(i) = n*i mod (4n-1) for 0 <= i < 4n-1
#if PRINT
          printf("%d -> %d\n",(2-j)*4+n, p);
#endif
          t += ((state[j] >> n) & 1) << p;
        }else{
          t += ((state[j] >> 3) & 1) << 11;  // p(i) = 4n-1 for i = 4n-1
        }
      }
    }
    // update the state by the ans of bit permutation
    for(int j = 0; j < 3; ++j){  
      state[2-j] = (t >> (j*4)) & 0xf;
    }
#if PRINT
    printf("4\n");
    print_bytes_(state, 3);
#endif
  }

  // the r-round
  // addRoundKey
  for(int j = 0; j < 3; ++j){
    state[j] = state[j] ^ subkey[ROUNDS*3 + j];
  }
#if PRINT 
  printf("5\n");
  print_bytes_(state, 3);
#endif
}

void present_dec_12(u8 *state, u8 *subkey){
  u8 r = 1;
  u8 p;
  u32 t1, t2;
  // generateRoundKeys()
#if PRINT
  printf("1:\n");
  print_bytes_(state, 3);
  print_bytes_(subkey, 3);
#endif
  // 0~(r-1)-th rounds, where r = 10
  for(int i = 0; i < ROUNDS; ++i){

    // addRoundKey
    for(int j = 0; j < 3; ++j){
      state[j] = state[j] ^ subkey[i*3 + j];
    }
#if PRINT
    printf("2:\n");
    print_bytes_(state, 3);
#endif
    // pLayer
    // 12-bit state denoted s11s10...s1s0
    t1 = 0;  // t is the ans of bit permutation
    t2 = (state[2]&0xf) + ((state[1]&0xf)<<4) + ((state[0]&0xf)<<8);
#if PRINT
    printf("t2：%x\n",(((t2 >> 7)&1) << 6));
#endif
    for(int j = 0; j < 11; ++j){
      p = 4*j % 11;
      t1 += (((t2 >> j)&1) << p);
#if PRINT
      printf("%d -> %d\n", j, p);
      printf("%x\n",t1);
#endif
    }
    t1 += (t2>>11) << 11;
    // update the state by the ans of bit permutation
    for(int j = 0; j < 3; ++j){
      state[2-j] = (t1 >> (j*4)) & 0xf;
    }
#if PRINT
    printf("3:\n");
    print_bytes_(state, 3);
#endif
    // sBoxLayer
    for(int j = 0; j < 3; ++j){
      state[j] = SBOXINV_4[state[j]];
    }
#if PRINT
    printf("4:\n");
    print_bytes_(state, 3);
#endif

  }

  // the r-round
  // addRoundKey
  for(int j = 0; j < 3; ++j){
    state[j] = state[j] ^ subkey[r=ROUNDS*3 + j];
  }
#if PRINT
  printf("5:\n");
  print_bytes_(state, 3);
#endif

}

// key-dependent bijective 16-bit S-box
void S_16(u8 *state, u8 *subkey){
  u8 t0,t1;  // temporary var
  // 0-th round
  state[0] ^= subkey[0];
  state[1] ^= subkey[1];

  // 1~32-th rounds
  for(int i = 1; i <= 32; ++i){
    // SB
    state[0] = SBOX_8[state[0]];
    state[1] = SBOX_8[state[1]];

    // MC
    t0 = state[0];
    t1 = state[1];
    state[0] = GMul8(A_16[0], t0) ^ GMul8(A_16[1],t1);
    state[1] = GMul8(A_16[2], t0) ^ GMul8(A_16[3],t1);

    // AK
    state[0] ^= subkey[i*2];
    state[1] ^= subkey[i*2 + 1];
  }
}

// the subkey is the reverse of the original subkey
void SINV_16(u8 *state, u8 *subkey){
  u8 t0,t1;  // temporary var
  // 32-th round
  state[0] ^= subkey[0];
  state[1] ^= subkey[1];

  // 31~0-th rounds
  for(int i = 1; i <= 32; ++i){
    // MC
    t0 = state[0];
    t1 = state[1];
    state[0] = GMul8(AINV_16[0], t0) ^ GMul8(AINV_16[1],t1);
    state[1] = GMul8(AINV_16[2], t0) ^ GMul8(AINV_16[3],t1);

    // SB
    state[0] = SBOXINV_8[state[0]];
    state[1] = SBOXINV_8[state[1]];

    // AK
    state[0] ^= subkey[i*2];
    state[1] ^= subkey[i*2 + 1];
  }
}

// data x and key is 16-bit
void S1_16(u8 *x, u8 *key) {
  u32 t1, t2;  // temporary var
  u32 p = 62743;
  t1 = MERGEU8(x[0], x[1]);
  t2 = MERGEU8(key[0], key[1]);
  t1 = (t2 + t1 * p) % 65536;
  SPLITU16(t1, x[0], x[1]);
}

void S1INV_16(u8 *x, u8 *key) {
  u32 t1, t2;  // temporary var
  u32 p_inv = 37543;
  t1 = MERGEU8(x[0], x[1]);
  t2 = MERGEU8(key[0], key[1]);
  t1 = (t1 - t2) * p_inv % 65536;
  SPLITU16(t1, x[0], x[1]);
}

// data x and key is 16-bit
void S2_16(u8 *x, u8 *key) {
  u32 t1, t2;  // temporary var
  u32 p = 63127;
  t1 = MERGEU8(x[0], x[1]);
  t2 = MERGEU8(key[0], key[1]);
  t1 = (t2 + t1 * p) % 65536;
  SPLITU16(t1, x[0], x[1]);
}

void S2INV_16(u8 *x, u8 *key) {
  u32 t1, t2;  // temporary var
  u32 p_inv = 59687;
  t1 = MERGEU8(x[0], x[1]);
  t2 = MERGEU8(key[0], key[1]);
  t1 = (t1 - t2) * p_inv % 65536;
  SPLITU16(t1, x[0], x[1]);
}

// data x and key is 16-bit
void S3_16(u8 *x, u8 *key) {
  u32 t1, t2;  // temporary var
  u32 p = 58537;
  t1 = MERGEU8(x[0], x[1]);
  t2 = MERGEU8(key[0], key[1]);
  t1 = (t2 + t1 * p) % 65536;
  SPLITU16(t1, x[0], x[1]);
}

void S3INV_16(u8 *x, u8 *key) {
  u32 t1, t2;  // temporary var
  u32 p_inv = 65433;
  t1 = MERGEU8(x[0], x[1]);
  t2 = MERGEU8(key[0], key[1]);
  t1 = (t1 - t2) * p_inv % 65536;
  SPLITU16(t1, x[0], x[1]);
}

void mul_M88(u8 x[15]) {
  u8 x0 = GETU4(x[1]);
  u8 x1 = GETU4(x[3]);
  u8 x2 = GETU4(x[5]);
  u8 x3 = GETU4(x[7]);
  u8 x4 = GETU4(x[9]);
  u8 x5 = GETU4(x[11]);
  u8 x6 = GETU4(x[13]);
  u8 x7 = GETU4(x[15]);
  u8 v;
  for (int i = 0; i < 8; ++i) {
    v = GMul4(x0, M_88[i * 8]) ^
        GMul4(x1, M_88[i * 8 + 1]) ^
        GMul4(x2, M_88[i * 8 + 2]) ^
        GMul4(x3, M_88[i * 8 + 3]) ^
        GMul4(x4, M_88[i * 8 + 4]) ^
        GMul4(x5, M_88[i * 8 + 5]) ^
        GMul4(x6, M_88[i * 8 + 6]) ^
        GMul4(x7, M_88[i * 8 + 7]);
    PUTU4(x[i * 2 + 1], v);
  }
}

void mul_MINV88(u8 x[15]) {
  u8 x0 = GETU4(x[1]);
  u8 x1 = GETU4(x[3]);
  u8 x2 = GETU4(x[5]);
  u8 x3 = GETU4(x[7]);
  u8 x4 = GETU4(x[9]);
  u8 x5 = GETU4(x[11]);
  u8 x6 = GETU4(x[13]);
  u8 x7 = GETU4(x[15]);
  u8 v;
  for (int i = 0; i < 8; ++i) {
    v = GMul4(x0, MINV_88[i * 8]) ^
        GMul4(x1, MINV_88[i * 8 + 1]) ^
        GMul4(x2, MINV_88[i * 8 + 2]) ^
        GMul4(x3, MINV_88[i * 8 + 3]) ^
        GMul4(x4, MINV_88[i * 8 + 4]) ^
        GMul4(x5, MINV_88[i * 8 + 5]) ^
        GMul4(x6, MINV_88[i * 8 + 6]) ^
        GMul4(x7, MINV_88[i * 8 + 7]);
    PUTU4(x[i * 2 + 1], v);
  }
}

// enc in black-box context
// the 6-byte key is used by S1,S2,S3 func
void yoroi16_enc(u8 *x, u8 *key) {
  u32 t1;  // temporary var
  // the 1~(R-1)-th rounds, R = 8
  for (int i = 1; i < 8; ++i) {
    // S-layer
    if (i == 1) {
      for (int j = 0; j < 8; ++j) {
        S1_16(x + j * 2, key);
      }
    } else {
      for (int j = 0; j < 8; ++j) {
        S2_16(x + j * 2, key + 2);
      }
    }
    // Affine layer
    for (int j = 0; j < 8; ++j) {
      x[j * 2 + 1] ^= i;  // only disturb the lsb4
    }
  }
  // S-layer
  for (int j = 0; j < 8; ++j) {
    S3_16(x + j * 2, key + 4);
  }
  // AES layer
  // ...
}

// dec in black-box context
void yoroi16_dec(u8 *x, u8 *key) {
  u32 t1;  // temporary var
  // the 1~(R-1)-th rounds, R = 8
  for (int i = 1; i < 8; ++i) {
    // S-layer
    if (i == 1) {
      for (int j = 0; j < 8; ++j) {
        S3INV_16(x + j * 2, key + 4);
      }
    } else {
      for (int j = 0; j < 8; ++j) {
        S2INV_16(x + j * 2, key + 2);
      }
    }
    // Affine layer
    for (int j = 0; j < 8; ++j) {
      x[j * 2 + 1] ^= 8 - i;  // only disturb the lsb4
    }
  }
  // S-layer
  for (int j = 0; j < 8; ++j) {
    S1INV_16(x + j * 2, key);
  }
  // AES layer
  // ...
}

// regard the x[i*2]||x[i*+1] as a block, where i in [0, 7]
void yoroi16_wbenc(u8 *x) {
  u32 t1;  // temporary var
  // the 1~(R-1)-th rounds, R = 8
  for (int i = 1; i < 8; ++i) {
    // S-layer
    if (i == 1) {
      for (int j = 0; j < 8; ++j) {
        t1 = MERGEU8(x[j * 2], x[j * 2 + 1]);
        t1 = T1[t1];  // T1 is 16-bit table
        SPLITU16(t1, x[j * 2], x[j * 2 + 1]);
      }
    } else {
      for (int j = 0; j < 8; ++j) {
        t1 = MERGEU8(x[j * 2], x[j * 2 + 1]);
        t1 = T2[t1];  // T2 is 16-bit table
        SPLITU16(t1, x[j * 2], x[j * 2 + 1]);
      }
    }
    // Affine layer
    for (int j = 0; j < 8; ++j) {
      x[j * 2 + 1] ^= i;  // only disturb the lsb4
    }
  }
  for (int j = 0; j < 8; ++j) {
    t1 = MERGEU8(x[j * 2], x[j * 2 + 1]);
    t1 = T3[t1];  // T3 is 16-bit table
    SPLITU16(t1, x[j * 2], x[j * 2 + 1]);
  }

  // AES layer
  // ...
}

void yoroi16_wbdec(u8 *x) {
  u32 t1;  // temporary var
  // the 1~(R-1)-th rounds, R = 8
  for (int i = 1; i < 8; ++i) {
    // S-layer
    if (i == 1) {
      for (int j = 0; j < 8; ++j) {
        t1 = MERGEU8(x[j * 2], x[j * 2 + 1]);
        t1 = T3_inv[t1];  // T1 is 16-bit table
        SPLITU16(t1, x[j * 2], x[j * 2 + 1]);
      }
    } else {
      for (int j = 0; j < 8; ++j) {
        t1 = MERGEU8(x[j * 2], x[j * 2 + 1]);
        t1 = T2_inv[t1];  // T2 is 16-bit table
        SPLITU16(t1, x[j * 2], x[j * 2 + 1]);
      }
    }
    // Affine layer
    for (int j = 0; j < 8; ++j) {
      x[j * 2 + 1] ^= 8-i;  // only disturb the lsb4
    }
  }
  for (int j = 0; j < 8; ++j) {
        t1 = MERGEU8(x[j * 2], x[j * 2 + 1]);
        t1 = T1_inv[t1];  // T3 is 16-bit table
        SPLITU16(t1, x[j * 2], x[j * 2 + 1]);
  }

  // AES layer
  // ...
}

void print_bytes_(u8 *x, int len){
  for (int i = 0; i < len; ++i) {
    if (x[i] > 16)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");
}
// test the enc and dec func in black-box context
void test_enc_dec() {
  u8 key[6] = {0x11, 0x33, 0x55, 0x77, 0x99, 0xbb};
  u8 x[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  yoroi16_enc(x, key);
  for (int i = 0; i < 16; ++i) {
    if (x[i] > 9)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");

  yoroi16_dec(x, key);
  for (int i = 0; i < 16; ++i) {
    if (x[i] > 9)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");
}

// test the enc and dec func in black-box context
void test_wbenc_wbdec(){
  u8 x[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  yoroi16_wbenc(x);
  for (int i = 0; i < 16; ++i) {
    if (x[i] > 9)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");

  yoroi16_wbdec(x);
  for (int i = 0; i < 16; ++i) {
    if (x[i] > 9)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");
}

// test the key-dependent bijection function S16 and SINV_16
void test_S16_SINV16(){
  u8 x[] = {0x11, 0x22};
  u8 enck[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41};
  u8 deck[] = {0x40, 0x41, 0x3e, 0x3f, 0x3c, 0x3d, 0x3a, 0x3b, 0x38, 0x39, 0x36, 0x37, 0x34, 0x35, 0x32, 0x33, 0x30, 0x31, 0x2e, 0x2f, 0x2c, 0x2d, 0x2a, 0x2b, 0x28, 0x29, 0x26, 0x27, 0x24, 0x25, 0x22, 0x23, 0x20, 0x21, 0x1e, 0x1f, 0x1c, 0x1d, 0x1a, 0x1b, 0x18, 0x19, 0x16, 0x17, 0x14, 0x15, 0x12, 0x13, 0x10, 0x11, 0x0e, 0x0f, 0x0c, 0x0d, 0x0a, 0x0b, 0x08, 0x09, 0x06, 0x07, 0x04, 0x05, 0x02, 0x03, 0x00, 0x01};
  S_16(x,enck);
  for (int i = 0; i < 2; ++i) {
    if (x[i] > 15)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");

  SINV_16(x, deck);
  for (int i = 0; i < 2; ++i) {
    if (x[i] > 15)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");
}

void test_enc12_dec12(){
  u8 x[] = {0x0f, 0x03, 0x04};
  u8 enck[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
  u8 deck[] = {0x04, 0x05, 0x06, 0x01, 0x02, 0x03};
  present_enc_12(x,enck);
  for (int i = 0; i < 3; ++i) {
    if (x[i] > 15)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");

  present_dec_12(x,deck);
  for (int i = 0; i < 3; ++i) {
    if (x[i] > 15)
      printf("%x", x[i]);
    else
      printf("0%x", x[i]);
  }
  printf("\n");
}

int test_HashDrbg();

int main() {
  printf("hello world!\n");
  // test_HashDrbg();
  u8 s[80];
  u8 x[80];
  u8 rand[50];
  PRF(s, 80, x, 80, rand, 50);
  // test_enc12_dec12();
  return 0;
}

int test_HashDrbg()
{
    void *ctx;
    size_t len = 50;
    unsigned char bytes[len];
    size_t seed_len = 60;  // 至少超过55byte
    unsigned char seed[seed_len];
    size_t add_len = 60;
    unsigned char add[add_len];
    int ret;
    // 分配空间并初始化ctx
    ret = anyan_rand_new_and_init(&ctx);

    // 获得长度为len的随机字节
    if(ret == 0){  // ret为0表示正确初始化
        ret = anyan_rand_seed(ctx, seed, seed_len);
    }else{
        printf("ctx new 或 init 出错！\nerror code: %d\n",ret);
        return -1;
    }
    // 获得长度为len的随机字节
    if(ret == 0){  // ret为0表示正确初始化
        ret = anyan_rand_bytes_with_add(ctx, bytes, len, add, add_len);
    }else{
        printf("ctx new 或 init 出错！\nerror code: %x\n",ret);
        return -1;
    }
    if (ret == 0){  // ret为0表示成功获取随机字节
        printf("rand bytes: \n");
        for (int i = 0; i < len; ++i)
        {
            printf("%d, ", bytes[i]);
        }
        printf("\n");
    }else{
        printf("生成rand bytes出错！\nerror code: %x\n", ret);
        anyan_rand_free(ctx);
        return -1;
    }
    // 释放ctx空间
    anyan_rand_free(ctx);
    return 0;
}
