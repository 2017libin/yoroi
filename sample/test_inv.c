#include <stdio.h>
#include "common.h"
#include "kdf_ctr.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/entropy.h"
#include "yoroi.h"
#include "T_tables.h"

// test the result of inverse of T
void test_correct(){
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

  u32 T1_b[65536];
  u32 T2_b[65536];
  u32 T3_b[65536];
  for (int i = 0; i < 65536; ++i){
      T1_b[T1[i]] = i;
      T2_b[T2[i]] = i;
      T3_b[T3[i]] = i;
  }

  yoroi16_print_T_table(T1, "T1");
  yoroi16_print_T_table(T2, "T2");
  yoroi16_print_T_table(T3, "T3");
  yoroi16_print_T_table(T1_b, "T1_inv");
  yoroi16_print_T_table(T2_b, "T2_inv");
  yoroi16_print_T_table(T3_b, "T3_inv");
}

// test the time of gen inverse of T
void test_time(){
  
}
#if 0
int main(){
    test();
    return 0;
}
#endif