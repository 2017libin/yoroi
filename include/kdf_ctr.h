#ifndef KDF_CTR_H
#define KDF_CTR_H

#include "common.h"

// input: s (seed) and x (input variable)
// output: rand (rand bytes, the output of hash_drbg)
// return: 0 if success, else -1
int PRF(u8 *s, size_t s_len, u8 *x, size_t x_len, u8 *rand, size_t rand_len);

// input: KI (key derivation key), lable(the purpose of KO), context(the
// information related to KO) output: KO (keying material)
void KDF_ctr(const u8 *KI, size_t KI_len, u8 *lable, size_t lable_len,
             u8 *context, size_t context_len, u8 *KO, size_t KO_len);

#endif