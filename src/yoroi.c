#include "common.h"
#include "kdf_ctr.h"
#include "yoroi.h"
#include "S_16.h"
#include "T_tables.h"

// master_key: K_len-byte
// round_key: 6-byte，used in S1,S2 and S3
void yoroi16_keyschedule(const u8 *master_key, u8 *round_key){
  u8 lable = 0x01;
  u8 context = 0x02;
  u8 buf[29];
  memset(buf, 0, 29);
  memcpy(buf, master_key, K_len);
  // the seed length should not less than 29
  // the length of master_key less than 29, padding with 0 
  KDF_ctr(buf, 29, &lable, 1, &context, 1, round_key, RK_len);
}

void yoroi16_gen_roundkey_enc(const u8 *master_key, u8 *round_key){
  yoroi16_keyschedule(master_key, round_key);
}

void yoroi16_gen_roundkey_dec(const u8 *master_key, u8 *round_key){
  u8 tmp[RK_len];

  yoroi16_gen_roundkey_enc(master_key, tmp);

  // reverse the encrypt roundkey
  // the sample of reverse: 0001 0203 0405 -> 0405 0203 0001
  int count = RK_len-1;
  while (count > 0)
  {
    round_key[RK_len-1 - count] = tmp[count-1];
    round_key[RK_len-1 - count + 1] = tmp[count];
    count -= 2;
  }
}

// name：the T table name
// T[]：include the T table elements
void yoroi16_print_T_table(u32 T[], char *name){
  char T0[10];

  printf("unsigned int %s[65536] = {", name);
  if (T[0] >= 0x1000){
    printf("0x%x",T[0]);
  }else if(T[0] >= 0x0100){
    printf("0x0%x",T[0]);
  }else if(T[0] >= 0x0010){
    printf("0x00%x",T[0]);
  }else{
    printf("0x000%x",T[0]);
  }

  for (int i = 1; i < 65536; i++)
  { 
    if (T[i] >= 0x1000){
      printf(", 0x%x",T[i]);
    }else if(T[i] >= 0x0100){
      printf(", 0x0%x",T[i]);
    }else if(T[i] >= 0x0010){
      printf(", 0x00%x",T[i]);
    }else{
      printf(", 0x000%x",T[i]);
    }
    
    if((i+1) % 16 == 0)
      printf("\n               ");
  }
  printf("};\n");
}

void yoroi16_gen_T_table(u8 key[], u8 pkey[], u32 T1[], u32 T2[], u32 T3[], u32 T1_inv[], u32 T2_inv[], u32 T3_inv[]){

  // yoroi roundkey
  u8 roundkey[RK_len];

  // present12 key
  // u8 pkey[10];

  // rk1、rk2以及rk3分别是S1、S2以及S3的密钥
  u8 rk1_enc[66];
  u8 rk1_dec[66];
  u8 rk2_enc[66];
  u8 rk2_dec[66];  
  u8 rk3_enc[66];
  u8 rk3_dec[66];

  yoroi16_gen_roundkey_enc(key, roundkey);
  memcpy(rk1_enc, roundkey, 66);
  memcpy(rk2_enc, roundkey + 66, 66);
  memcpy(rk3_enc, roundkey + 66*2, 66);

  yoroi16_gen_roundkey_dec(key, roundkey);
  memcpy(rk3_dec, roundkey, 66);
  memcpy(rk2_dec, roundkey + 66, 66);
  memcpy(rk1_dec, roundkey + 66*2, 66);

  // 2^16 = 65536
  u8 x[2];  // 16-bit into two 8-bit x[0], x[1]
  u8 t[3];  // 12-bit into three 3-bit t[0],t[1],t[3]

  // gen T1
  for(int i = 0; i < 65536; ++i){
    SPLITU16(i, x[0], x[1]);

    // pass S1
    S_16(x, rk1_enc);

    // pass Present12
    SPLITU8(x[0], t[0], t[1]);
    t[2] = (x[1] >> 4) & 0xf;
    present_enc_12(t, pkey);

    x[0] = MERGEU4(t[0], t[1]);
    x[1] = MERGEU4(t[2], x[1]);
    T1[i] = MERGEU8(x[0], x[1]);
  }

  // gen T2
  for(int i = 0; i < 65536; ++i){
    
    SPLITU16(i, x[0], x[1]);

    // pass present12_dec
    SPLITU8(x[0], t[0], t[1]);
    t[2] = (x[1] >> 4) & 0xf;
    present_dec_12(t, pkey);

    // pass S2
    x[0] = MERGEU4(t[0], t[1]);
    x[1] = MERGEU4(t[2], x[1]);
    S_16(x, rk2_enc);

    // pass Present12_enc
    SPLITU8(x[0], t[0], t[1]);
    t[2] = (x[1] >> 4) & 0xf;
    present_enc_12(t, pkey);

    x[0] = MERGEU4(t[0], t[1]);
    x[1] = MERGEU4(t[2], x[1]);
    T2[i] = MERGEU8(x[0], x[1]);
  }

  // gen T3
  for(int i = 0; i < 65536; ++i){
    
    SPLITU16(i, x[0], x[1]);

    // pass present12_dec
    SPLITU8(x[0], t[0], t[1]);
    t[2] = (x[1] >> 4) & 0xf;
    present_dec_12(t, pkey);
    
    // pass S3_inv
    x[0] = MERGEU4(t[0], t[1]);
    x[1] = MERGEU4(t[2], x[1]);
    S_16(x, rk3_enc);
    
    T3[i] = MERGEU8(x[0], x[1]);
  }

  // gen T3_inv
  for(int i = 0; i < 65536; ++i){
    // pass S3_inv
    SPLITU16(i, x[0], x[1]);
    SINV_16(x, rk3_dec);

    // pass Present12
    SPLITU8(x[0], t[0], t[1]);
    t[2] = (x[1] >> 4) & 0xf;
    present_enc_12(t, pkey);

    x[0] = MERGEU4(t[0], t[1]);
    x[1] = MERGEU4(t[2], x[1]);
    T3_inv[i] = MERGEU8(x[0], x[1]);
  }

  // gen T2_inv
  for(int i = 0; i < 65536; ++i){
    
    SPLITU16(i, x[0], x[1]);

    // pass present12_dec
    SPLITU8(x[0], t[0], t[1]);
    t[2] = (x[1] >> 4) & 0xf;
    present_dec_12(t, pkey);

    // pass S2_inv
    x[0] = MERGEU4(t[0], t[1]);
    x[1] = MERGEU4(t[2], x[1]);
    SINV_16(x, rk2_dec);

    // pass Present12_enc
    SPLITU8(x[0], t[0], t[1]);
    t[2] = (x[1] >> 4) & 0xf;
    present_enc_12(t, pkey);

    x[0] = MERGEU4(t[0], t[1]);
    x[1] = MERGEU4(t[2], x[1]);
    T2_inv[i] = MERGEU8(x[0], x[1]);
  }

  // gen T1_inv
  for(int i = 0; i < 65536; ++i){
    
    SPLITU16(i, x[0], x[1]);

    // pass present12_dec
    SPLITU8(x[0], t[0], t[1]);
    t[2] = (x[1] >> 4) & 0xf;
    present_dec_12(t, pkey);

    // pass S1_inv
    x[0] = MERGEU4(t[0], t[1]);
    x[1] = MERGEU4(t[2], x[1]);
    SINV_16(x, rk1_dec);

    T1_inv[i] = MERGEU8(x[0], x[1]);
  }

}

// the linear layer in yoroi16
void mul_M8(u8 x[16]) {
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
    v = GMul4(x0, M_88[i * 8]) ^ GMul4(x1, M_88[i * 8 + 1]) ^
        GMul4(x2, M_88[i * 8 + 2]) ^ GMul4(x3, M_88[i * 8 + 3]) ^
        GMul4(x4, M_88[i * 8 + 4]) ^ GMul4(x5, M_88[i * 8 + 5]) ^
        GMul4(x6, M_88[i * 8 + 6]) ^ GMul4(x7, M_88[i * 8 + 7]);
    PUTU4(x[i * 2 + 1], v);
  }
}

void mul_MINV8(u8 x[16]) {
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
    v = GMul4(x0, MINV_88[i * 8]) ^ GMul4(x1, MINV_88[i * 8 + 1]) ^
        GMul4(x2, MINV_88[i * 8 + 2]) ^ GMul4(x3, MINV_88[i * 8 + 3]) ^
        GMul4(x4, MINV_88[i * 8 + 4]) ^ GMul4(x5, MINV_88[i * 8 + 5]) ^
        GMul4(x6, MINV_88[i * 8 + 6]) ^ GMul4(x7, MINV_88[i * 8 + 7]);
    PUTU4(x[i * 2 + 1], v);
  }
}

// enc in black-box context
// the 6-byte key is used by S1,S2,S3 func
void yoroi16_enc(u8 *x, const u8 *key) {
  u32 t1;  // temporary var

  u8 roundkey[RK_len];
  yoroi16_gen_roundkey_enc(key, roundkey);

  // the 1~(R-1)-th rounds, R = 8
  for (int i = 1; i < 8; ++i) {
    // S-layer
    if (i == 1) {
      for (int j = 0; j < 8; ++j) {
        S_16(x + j * 2, roundkey);
      }
    } else {
      for (int j = 0; j < 8; ++j) {
        S_16(x + j * 2, roundkey + RK_len/3);
      }
    }

    // Linear layer
    mul_M8(x);

    // Affine layer
    for (int j = 0; j < 8; ++j) {
      x[j * 2 + 1] ^= i;  // only disturb the lsb4
    }

  }

  // S-layer
  for (int j = 0; j < 8; ++j) {
    S_16(x + j * 2, roundkey + 2*RK_len/3);
  }
  // AES layer
  // ...
}

// dec in black-box context
void yoroi16_dec(u8 *x, const u8 *key) {
  u32 t1;  // temporary var

  u8 roundkey[RK_len];
  yoroi16_gen_roundkey_dec(key, roundkey);

  // the 1~(R-1)-th rounds, R = 8
  for (int i = 1; i < 8; ++i) {
    // S-layer
    if (i == 1) {
      for (int j = 0; j < 8; ++j) {
        SINV_16(x + j * 2, roundkey);
      }
    } else {
      for (int j = 0; j < 8; ++j) {
        SINV_16(x + j * 2, roundkey + RK_len/3);
      }
    }
    
    // Affine layer
    for (int j = 0; j < 8; ++j) {
      x[j * 2 + 1] ^= 8 - i;  // only disturb the lsb4
    }

    // Linear layer
    mul_MINV8(x);
  }
  // S-layer
  for (int j = 0; j < 8; ++j) {
    SINV_16(x + j * 2, roundkey + 2*RK_len/3);
  }
  // AES layer
  // ...
}

// regard the x[i*2]||x[i*2+1] as a block, where i in [0, 7]
void yoroi16_wbenc(u8 *x) {
  u16 t1;  // temporary var
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

    // Linear layer
    mul_M8(x);

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
  u16 t1;  // temporary var
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
      x[j * 2 + 1] ^= 8 - i;  // only disturb the lsb4
    }

    // Linear layer
    mul_MINV8(x);
  }

  for (int j = 0; j < 8; ++j) {
    t1 = MERGEU8(x[j * 2], x[j * 2 + 1]);
    t1 = T1_inv[t1];  // T3 is 16-bit table
    SPLITU16(t1, x[j * 2], x[j * 2 + 1]);
  }

  // AES layer
  // ...
}