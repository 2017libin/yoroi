#include "common.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"

int set_seed (void *buf , unsigned char * seed, size_t seed_len){
  memcpy(seed, buf, seed_len);
  return 0;
}

// input: s (seed) and x (input variable)
// output: rand (rand bytes, the output of hash_drbg)
// return: 0 if success, else -1
int PRF(u8 *s, size_t s_len, u8 *x, size_t x_len, u8 *rand, size_t rand_len) {
  debug("开始执行PRF!\n");
  mbedtls_entropy_context *entropy_ctx =
      malloc(sizeof(mbedtls_entropy_context));
  mbedtls_ctr_drbg_context *drbg_ctx = malloc(sizeof(mbedtls_ctr_drbg_context));

  u8 buf[s_len];
  memcpy(buf, s, s_len);

  size_t byte_len = 50;
  unsigned char bytes[byte_len];
  size_t seed_len = 60;  // at least 55-byte
  unsigned char seed[seed_len];
  size_t add_len = 60;
  unsigned char add[add_len];
  int ret;

  // init ctx
  mbedtls_entropy_init(entropy_ctx);
  mbedtls_ctr_drbg_init(drbg_ctx);

  // set the seed of drbg
  ret = mbedtls_ctr_drbg_seed(drbg_ctx, set_seed, buf, s,
                              s_len);

  if (ret == 0) {  // return 0 if success
    ret = mbedtls_ctr_drbg_random_with_add(drbg_ctx, rand, rand_len, x,
                                           x_len);
  } else {
    printf("ctx seed error, error code: %x\n", ret);
    goto clean;
  }
  if (ret == 0) {  // return 0 if success
  } else {
    printf("rand bytes error, error code: %x\n", ret);
    goto clean;
  }

clean:
  // free the ctx
  mbedtls_ctr_drbg_free(drbg_ctx);
  mbedtls_entropy_free(entropy_ctx);
  
  debug("结束执行PRF!\n");

  return ret;
}

// input: KI (key derivation key), lable(the purpose of KO), context(the
// information related to KO) output: KO (keying material)
void KDF_ctr(const u8 *KI, size_t KI_len, u8 *lable, size_t lable_len,
             u8 *context, size_t context_len, u8 *KO, size_t KO_len) {
  
  debug("开始执行KDF!\n");
  size_t n, i, size_len, add_len;
  n = (KO_len / OUT_LEN_OF_KDF) + 1;  // at least run n times PRF
  size_len = sizeof(size_t);

  add_len = size_len + lable_len + 1 + context_len + size_len;
  
  u8 add[add_len];  // the input variable for PRF

  u8 *KO_t = KO;
  size_t KO_len_t = KO_len;

  u8 zero = 0x00;
  
  for (i = 0; i < n && KO_len_t > 0; ++i) {
    // add = [i]2 || lable || 0x00 || context || [KO_len]2
    memcpy(add, &i, size_len);
    memcpy(add + size_len, lable, lable_len);
    memcpy(add + size_len + lable_len, &zero, 1);
    memcpy(add + size_len + lable_len + 1, context, context_len);
    memcpy(add + size_len + lable_len + 1 + context_len, &KO_len, size_len);

    // use PRF function to generate keying material
    if (KO_len_t > OUT_LEN_OF_KDF) {
      PRF(KI, KI_len, add, add_len, KO_t, OUT_LEN_OF_KDF);
      KO_t += OUT_LEN_OF_KDF;  // the point move to the next block
      KO_len_t -= OUT_LEN_OF_KDF; 
    } else {
      PRF(KI, KI_len, add, add_len, KO_t, KO_len_t);  // the last block
      break;
    }
  }
  debug("结束执行KDF!\n");

}