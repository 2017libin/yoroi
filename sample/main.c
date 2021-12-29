#include "common.h"
#include "kdf_ctr.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"

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
  u8 KI[KI_len];
  u8 KO[KO_len];
  u8 lable[lable_len];
  u8 context[context_len];
  KDF_ctr(KI, KI_len, lable, lable_len, context, context_len, KO, KO_len);
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
  u8 key[6] = {0x11, 0x33, 0x55, 0x77, 0x99, 0xbb};
  u8 x[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  print_bytes(x, 16);

  yoroi16_enc(x, key);
  print_bytes(x, 16);

  yoroi16_dec(x, key);
  print_bytes(x, 16);

}

// 白盒yoroi16功能正确性测试
void sample_wbenc_wbdec() {
  u8 x[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
            0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};

  print_bytes(x, 16);

  yoroi16_wbenc(x);
  print_bytes(x, 16);

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


int main(){
  // printf("yoroi sample:\n");
  // sample_enc_dec();

  // printf("wbyoroi sample:\n");
  // sample_wbenc_wbdec();

  printf("present12 sample:\n");
  sample_enc12_dec12();

  // printf("S_16 sample:\n");
  // sample_S16_SINV16();

  // sample_kdf_ctr();
  return 0;
}
