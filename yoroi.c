#include "yoroi.h"
#include "T_tables.h"
// irreducible polynomial: x^4 + x + 1
// return: a*b in GF(2^4)
// u8 mul_gf4(u8 a, u8 b){
//     u8 c = 0;
//     u8 flag;
//     for(int i = 0; i < 4 && b; ++i){
//         if(b & 1){
//             c ^= a;
//         }
//         a <<= 1;
//         flag = a & 0x10;
//         if(flag == 0x10){  // out of GF(2^4)
//             a ^= 0x13;
//         }
//         b >>= 1;
//     }
//     return c;
// }

// data x and key is 16-bit
void S1_16(u8 *x, u8 *key){
  u32 t1, t2;  // temporary var
  u32 p = 62743;
  t1 = MERGEU8(x[0],x[1]);
  t2 = MERGEU8(key[0],key[1]);
  t1 = (t2 + t1*p) % 65536;
  SPLITU16(t1, x[0], x[1]);
}

void S1INV_16(u8 *x, u8 *key){
  u32 t1, t2;  // temporary var
  u32 p_inv = 37543;
  t1 = MERGEU8(x[0],x[1]);
  t2 = MERGEU8(key[0],key[1]);
  t1 = (t1-t2)*p_inv % 65536;
  SPLITU16(t1, x[0], x[1]);
}

// data x and key is 16-bit
void S2_16(u8 *x, u8 *key){
  u32 t1, t2;  // temporary var
  u32 p = 63127;
  t1 = MERGEU8(x[0],x[1]);
  t2 = MERGEU8(key[0],key[1]);
  t1 = (t2 + t1*p) % 65536;
  SPLITU16(t1, x[0], x[1]);
}

void S2INV_16(u8 *x, u8 *key){
  u32 t1, t2;  // temporary var
  u32 p_inv = 59687;
  t1 = MERGEU8(x[0],x[1]);
  t2 = MERGEU8(key[0],key[1]);
  t1 = (t1-t2)*p_inv % 65536;
  SPLITU16(t1, x[0], x[1]);
}

// data x and key is 16-bit
void S3_16(u8 *x, u8 *key){
  u32 t1, t2;  // temporary var
  u32 p = 58537;
  t1 = MERGEU8(x[0],x[1]);
  t2 = MERGEU8(key[0],key[1]);
  t1 = (t2 + t1*p) % 65536;
  SPLITU16(t1, x[0], x[1]);
}

void S3INV_16(u8 *x, u8 *key){
  u32 t1, t2;  // temporary var
  u32 p_inv = 65433;
  t1 = MERGEU8(x[0],x[1]);
  t2 = MERGEU8(key[0],key[1]);
  t1 = (t1-t2)*p_inv % 65536;
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
    v = gf4mul[MERGEU4(x0, M_88[i * 8])] ^
        gf4mul[MERGEU4(x1, M_88[i * 8 + 1])] ^
        gf4mul[MERGEU4(x2, M_88[i * 8 + 2])] ^
        gf4mul[MERGEU4(x3, M_88[i * 8 + 3])] ^
        gf4mul[MERGEU4(x4, M_88[i * 8 + 4])] ^
        gf4mul[MERGEU4(x5, M_88[i * 8 + 5])] ^
        gf4mul[MERGEU4(x6, M_88[i * 8 + 6])] ^
        gf4mul[MERGEU4(x7, M_88[i * 8 + 7])];
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
    v = gf4mul[MERGEU4(x0, MINV_88[i * 8])] ^
        gf4mul[MERGEU4(x1, MINV_88[i * 8 + 1])] ^
        gf4mul[MERGEU4(x2, MINV_88[i * 8 + 2])] ^
        gf4mul[MERGEU4(x3, MINV_88[i * 8 + 3])] ^
        gf4mul[MERGEU4(x4, MINV_88[i * 8 + 4])] ^
        gf4mul[MERGEU4(x5, MINV_88[i * 8 + 5])] ^
        gf4mul[MERGEU4(x6, MINV_88[i * 8 + 6])] ^
        gf4mul[MERGEU4(x7, MINV_88[i * 8 + 7])];
    PUTU4(x[i * 2 + 1], v);
  }
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

int main() {
  u8 key[6] = {0x11, 0x33, 0x55, 0x77, 0x99, 0xbb};
  u8 x[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  // for (int i = 0; i < 16; ++i){
  //     if (x[i] > 9)
  //         printf("%x", x[i]);
  //     else
  //         printf("0%x", x[i]);
  // }

  // yoroi16_enc(x, key);
  // for (int i = 0; i < 16; ++i) {
  //   if (x[i] > 9)
  //     printf("%x", x[i]);
  //   else
  //     printf("0%x", x[i]);
  // }

  // printf("%d", mul_gf4(3, 10));

  return 0;
}