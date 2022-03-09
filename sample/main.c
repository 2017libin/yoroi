#include "common.h"
#include "kdf_ctr.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"
#include "yoroi.h"
#include "T_tables.h"

// yoroi master_key
u8 key[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

// 十六进制打印字节流
void print_bytes(unsigned char *data, size_t size){
  for (int i = 0; i < size; ++i) {
    if (data[i] > 15)
      printf("%x", data[i]);
    else
      printf("0%x", data[i]);
  }
  printf("\n");
}

// 测试kdf_ctr功能
void sample_kdf_ctr(){
  size_t KI_len = 10;
  size_t lable_len = 10;
  size_t context_len = 10;
  size_t KO_len = 20;
  u8 KI[80]= {1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10,1,2,3,4,5,6,7,8,9,10};
  // u8 KI[10]={1,2,3,4,5,6,7,8,9,10};
  u8 KO[KO_len];
  u8 lable[10]= {1,2,3,4,5,6,7,8,9,10};
  u8 context[10]= {1,2,3,4,5,6,7,8,9,10};
  PRF(KI, 29, lable, 10, KO, 20);
  // KDF_ctr(KI, KI_len, lable, lable_len, context, context_len, KO, KO_len);
  print_bytes(KO, KO_len);
}

// 测试ctr_drbg功能
void sample_ctr_drbg(){
  int ret;
  unsigned char buf[10];

  mbedtls_ctr_drbg_context *drbg_ctx = malloc(sizeof(mbedtls_ctr_drbg_context));
  mbedtls_entropy_context *entropy_ctx = malloc(sizeof(mbedtls_entropy_context));

  // 初始化
  mbedtls_entropy_init(entropy_ctx);
  mbedtls_ctr_drbg_init(drbg_ctx);

  // 设置种子
  const char *pers = "seed";
  ret = mbedtls_ctr_drbg_seed(drbg_ctx, mbedtls_entropy_func, entropy_ctx, pers, strlen(pers));
  if(ret){
    printf("ret = %d\nseed error!\n", ret);
    return -1;
  }else{
    printf("seed success!\n");
  }

  // 生成随机字节
  ret = mbedtls_ctr_drbg_random(drbg_ctx, buf, sizeof(buf));
  if(ret){
    printf("rand error!\n");
    return -1;
  }else{
    printf("rand success!\n");
    for(int i = 0; i < 10; ++i){
      printf("data[%d]=%d\n", i, buf[i]);
    }
  }

  // 释放空间
  mbedtls_ctr_drbg_free(drbg_ctx);
  mbedtls_entropy_free(entropy_ctx);
}


// 黑盒yoroi16功能正确性测试
void sample_enc_dec() {
  u8 x[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  u8 key[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
#if 0
  // test gen roundkey
  u8 rk_enc[6];
  u8 rk_dec[6];
  yoroi16_gen_roundkey_enc(key, rk_enc);
  yoroi16_gen_roundkey_dec(key, rk_dec);
  print_bytes(rk_enc, 6);
  print_bytes(rk_dec, 6);
#endif

  print_bytes(x, 16);

  yoroi16_enc(x, key);
  print_bytes(x, 16);

  yoroi16_dec(x, key);
  print_bytes(x, 16);

}

void sample_print_T_table(){
  u8 yoroi_key[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  u32 present12_key[10];
  u32 T1[65536];
  u32 T2[65536];
  u32 T3[65536];
  u32 T1_inv[65536];
  u32 T2_inv[65536];
  u32 T3_inv[65536];

  yoroi16_gen_T_table(yoroi_key, present12_key, T1, T2, T3, T1_inv, T2_inv, T3_inv);
  yoroi16_print_T_table(T1, "T1");
  yoroi16_print_T_table(T2, "T2");
  yoroi16_print_T_table(T3, "T3");
  yoroi16_print_T_table(T1_inv, "T1_inv");
  yoroi16_print_T_table(T2_inv, "T2_inv");
  yoroi16_print_T_table(T3_inv, "T3_inv");
}

// 白盒yoroi16功能正确性测试
void sample_wbenc_wbdec() {
  u8 x[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  u8 key[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  
  // yoroi16_gen_T_table(key);
  printf("11.123\n");
  print_bytes(x, 16);

  printf("22.123\n");
  yoroi16_wbenc(x);
  print_bytes(x, 16);
  
  printf("33.123\n");
  yoroi16_wbdec(x);
  print_bytes(x, 16);
}

// test the key-dependent bijection function S16 and SINV_16
void sample_S16_SINV16() {
  u8 x[] = {0x11, 0x22};
  u8 enck[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
               0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13,
               0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
               0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
               0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31,
               0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,
               0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41};
  u8 deck[] = {0x40, 0x41, 0x3e, 0x3f, 0x3c, 0x3d, 0x3a, 0x3b, 0x38, 0x39,
               0x36, 0x37, 0x34, 0x35, 0x32, 0x33, 0x30, 0x31, 0x2e, 0x2f,
               0x2c, 0x2d, 0x2a, 0x2b, 0x28, 0x29, 0x26, 0x27, 0x24, 0x25,
               0x22, 0x23, 0x20, 0x21, 0x1e, 0x1f, 0x1c, 0x1d, 0x1a, 0x1b,
               0x18, 0x19, 0x16, 0x17, 0x14, 0x15, 0x12, 0x13, 0x10, 0x11,
               0x0e, 0x0f, 0x0c, 0x0d, 0x0a, 0x0b, 0x08, 0x09, 0x06, 0x07,
               0x04, 0x05, 0x02, 0x03, 0x00, 0x01};

#if 0
  u8 master_key[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
  u8 rk_enc[66];
  u8 rk_dec[66];

  yoroi16_gen_roundkey_enc(master_key, rk_enc);
  yoroi16_gen_roundkey_dec(master_key, rk_dec);

  print_bytes(rk_enc, 66);
  print_bytes(rk_dec, 66);
#endif

  print_bytes(x, 2);

  S_16(x, enck);
  print_bytes(x, 2);

  SINV_16(x, deck);
  print_bytes(x, 2);
}

void sample_enc12_dec12() {
  u8 x[] = {0x0f, 0x03, 0x04};
  u8 key[10];

#if 0
  // the test of 
  u8 rk_enc[3*(ROUNDS+1)];
  u8 rk_dec[3*(ROUNDS+1)];
  gen_roundkey_enc(key, rk_enc);
  gen_roundkey_dec(key, rk_dec);
  print_bytes(rk_enc, 3*(ROUNDS+1));
  print_bytes(rk_dec, 3*(ROUNDS+1));
#endif 

  print_bytes(x, 3);

  present_enc_12(x, key);
  print_bytes(x, 3);

  present_dec_12(x, key);
  print_bytes(x, 3);
}

void sample_test_T(){
  
  u32 i = 0x3211;
  // printf("T[0x1111] = %x\n", T1[i]);
  i = T3[T2[T1[i]]];
  i = T1_inv[T2_inv[T3_inv[i]]];
  // SPLITU16(i, x[0], x[1]);

  // SPLITU8(x[0], t[0], t[1]);
  // t[2] = (x[1] >> 4) & 0xf;
  // present_dec_12(t, pkey);
  // // print_bytes(t, 3);

  // x[0] = MERGEU4(t[0], t[1]);
  // x[1] = MERGEU4(t[2], x[1]);
  // print_bytes(x,2);

  // pass Sbox
  // SINV_16(x, rk3_dec);
  // SINV_16(x, rk2_dec);
  // SINV_16(x, rk1_dec);
  // print_bytes(x, 2);
  printf("0x%x\n", i);
}

#if 1
int main(){
  // printf("yoroi sample:\n");
  // sample_enc_dec();

  printf("wbyoroi sample:\n");
  sample_wbenc_wbdec();

  // printf("present12 sample:\n");
  // sample_enc12_dec12();

  // printf("S_16 sample:\n");
  // sample_S16_SINV16();

  // sample_kdf_ctr();

  // sample_print_T_table();
  // sample_test_T();
  return 0;
}
#endif