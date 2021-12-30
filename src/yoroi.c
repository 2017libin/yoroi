#include "common.h"
#include "kdf_ctr.h"
#include "yoroi.h"
#include "S_16.h"

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

  debug("111\n");
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
  debug("222\n");

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
      x[j * 2 + 1] ^= 8 - i;  // only disturb the lsb4
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