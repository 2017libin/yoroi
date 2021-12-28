#include "common.h"

// master_key is the list of 8-bit
// round_key is the list of 4-bit
void present_keyschedule_12(
    u8 *master_key, u8 *round_key) {  // the bit size of a round_key is 12
  u8 tmp[10];
  for (int i = 0; i < ROUNDS + 1; ++i) {
    // rotated right shift 19-bit
    for (int j = 0; j < 10; ++j)
      tmp[j] =
          (master_key[2 + j % 10] >> 3) + ((master_key[3 + j % 10] ^ 7) << 5);
    for (int j = 0; j < 10; ++j) master_key[j] = tmp[j];

    // the most significant 4-bit through the PRESENT S-box
    master_key[9] = (SBOX_4[master_key[9] >> 4] << 4) + (master_key[9] & 0xf);

    // the bits k19k18k17k16k15 is exclusive-ored with the round_counter
    master_key[1] =
        master_key[1] ^ ((i & 0x01) << 7);  // k15 ^ round_counter[0]
    master_key[2] = master_key[2] ^
                    ((i & 0x1e) >> 1);  // k19k18k17k16 ^ round_counter[1]~[4]

    // a round_key consists the last significant 12-bit
    round_key[i * 3] = master_key[0] & 0xf;
    round_key[i * 3 + 1] = (master_key[0] >> 4) & 0xf;
    round_key[i * 3 + 2] = master_key[1] & 0xf;
  }
}

// Small Scale Variants of PRESENT
// state and subkey is the list of 4-bit
void present_enc_12(u8 *state, u8 *subkey) {  // the bit size of a block is 12
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
  for (int i = 0; i < ROUNDS; ++i) {
    // addRoundKey
    for (int j = 0; j < 3; ++j) {
      state[j] = state[j] ^ subkey[i * 3 + j];
    }
#if PRINT
    printf("2\n");
    print_bytes_(state, 3);
#endif
    // sBoxLayer
    for (int j = 0; j < 3; ++j) {
      state[j] = SBOX_4[state[j]];
    }
#if PRINT
    printf("3\n");
    print_bytes_(state, 3);
#endif
    // pLayer
    // the 12-bit state is denoted as s11s10...s1s0
    t = 0;  // t is the ans of bit permutation
    for (int j = 2; j >= 0; --j) {
      for (int n = 0; n < 4; ++n) {
        if ((2 - j) * 4 + n < 11) {
          p = 3 * ((2 - j) * 4 + n) %
              11;  // P(i) = n*i mod (4n-1) for 0 <= i < 4n-1
#if PRINT
          printf("%d -> %d\n", (2 - j) * 4 + n, p);
#endif
          t += ((state[j] >> n) & 1) << p;
        } else {
          t += ((state[j] >> 3) & 1) << 11;  // p(i) = 4n-1 for i = 4n-1
        }
      }
    }
    // update the state by the ans of bit permutation
    for (int j = 0; j < 3; ++j) {
      state[2 - j] = (t >> (j * 4)) & 0xf;
    }
#if PRINT
    printf("4\n");
    print_bytes_(state, 3);
#endif
  }

  // the r-round
  // addRoundKey
  for (int j = 0; j < 3; ++j) {
    state[j] = state[j] ^ subkey[ROUNDS * 3 + j];
  }
#if PRINT
  printf("5\n");
  print_bytes_(state, 3);
#endif
}

void present_dec_12(u8 *state, u8 *subkey) {
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
  for (int i = 0; i < ROUNDS; ++i) {
    // addRoundKey
    for (int j = 0; j < 3; ++j) {
      state[j] = state[j] ^ subkey[i * 3 + j];
    }
#if PRINT
    printf("2:\n");
    print_bytes_(state, 3);
#endif
    // pLayer
    // 12-bit state denoted s11s10...s1s0
    t1 = 0;  // t is the ans of bit permutation
    t2 = (state[2] & 0xf) + ((state[1] & 0xf) << 4) + ((state[0] & 0xf) << 8);
#if PRINT
    printf("t2：%x\n", (((t2 >> 7) & 1) << 6));
#endif
    for (int j = 0; j < 11; ++j) {
      p = 4 * j % 11;
      t1 += (((t2 >> j) & 1) << p);
#if PRINT
      printf("%d -> %d\n", j, p);
      printf("%x\n", t1);
#endif
    }
    t1 += (t2 >> 11) << 11;
    // update the state by the ans of bit permutation
    for (int j = 0; j < 3; ++j) {
      state[2 - j] = (t1 >> (j * 4)) & 0xf;
    }
#if PRINT
    printf("3:\n");
    print_bytes_(state, 3);
#endif
    // sBoxLayer
    for (int j = 0; j < 3; ++j) {
      state[j] = SBOXINV_4[state[j]];
    }
#if PRINT
    printf("4:\n");
    print_bytes_(state, 3);
#endif
  }

  // the r-round
  // addRoundKey
  for (int j = 0; j < 3; ++j) {
    state[j] = state[j] ^ subkey[r = ROUNDS * 3 + j];
  }
#if PRINT
  printf("5:\n");
  print_bytes_(state, 3);
#endif
}