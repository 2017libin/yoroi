#include "common.h"

// the 80-bit master_key is the list of 8-bit
// the 12*(ROUNDS+1)-bit round_key is the list of 4-bit
void present_keyschedule_12(
  const u8 *master_key, u8 *round_key) {  // the bit size of a round_key is 12
  u8 master_key_t[10];
  
  // copy the master_key
  for (int i = 0; i < 10; ++i){
    master_key_t[i] = master_key[i];
  }

  u8 tmp[10];
  for (int i = 0; i < ROUNDS + 1; ++i) {
    // rotated right shift 19-bit
    for (int j = 0; j < 10; ++j)
      tmp[j] =
          (master_key_t[2 + j % 10] >> 3) + ((master_key_t[3 + j % 10] ^ 7) << 5);
    
    for (int j = 0; j < 10; ++j) master_key_t[j] = tmp[j];

    // the most significant 4-bit through the PRESENT S-box
    master_key_t[9] = (SBOX_4[master_key_t[9] >> 4] << 4) + (master_key_t[9] & 0xf);

    // the bits k19k18k17k16k15 is exclusive-ored with the round_counter
    master_key_t[1] =
        master_key_t[1] ^ ((i & 0x01) << 7);  // k15 ^ round_counter[0]
    master_key_t[2] = master_key_t[2] ^
                    ((i & 0x1e) >> 1);  // k19k18k17k16 ^ round_counter[1]~[4]

    // a round_key consists the last significant 12-bit
    round_key[i * 3] = master_key_t[0] & 0xf;
    round_key[i * 3 + 1] = (master_key_t[0] >> 4) & 0xf;
    round_key[i * 3 + 2] = master_key_t[1] & 0xf;
  }
}


void present_gen_roundkey_enc(const u8 *master_key, u8 *round_key){
  present_keyschedule_12(master_key, round_key);
}

void present_gen_roundkey_dec(const u8 *master_key, u8 *round_key){
  int size = 3*(ROUNDS+1);
  u8 tmp[size];

  // generate encrypt roundkey
  present_gen_roundkey_enc(master_key, tmp);

  // reverse the encrypt roundkey
  int count = size - 1;
  while (count > 0)
  {
    // the sample of reverse: a0a1a2 a3a4a5 -> a3a4a5 a0a1a2
    round_key[size-1 - count] = tmp[count - 2];
    round_key[size-1 - count + 1] = tmp[count - 1];
    round_key[size-1 - count + 2] = tmp[count];
    count -= 3;
  }

}
// Small Scale Variants of PRESENT
// state and subkey is the list of 4-bit
// master_key: 80-bit
// state: 12-bit
void present_enc_12(u8 *state,const u8 *master_key) {  // the bit size of a block is 12
  u8 r = 1;
  u8 p;
  u32 t;
  u8 round_key[3*(ROUNDS+1)];
  // generateRoundKeys()
  present_gen_roundkey_enc(master_key, round_key);
  // 0~(r-1)-th rounds, where r = 10
  for (int i = 0; i < ROUNDS; ++i) {
    // addRoundKey
    for (int j = 0; j < 3; ++j) {
      state[j] = state[j] ^ round_key[i * 3 + j];
    }

    // sBoxLayer
    for (int j = 0; j < 3; ++j) {
      state[j] = SBOX_4[state[j]];
    }

    // pLayer
    // the 12-bit state is denoted as s11s10...s1s0
    t = 0;  // t is the ans of bit permutation
    for (int j = 2; j >= 0; --j) {
      for (int n = 0; n < 4; ++n) {
        if ((2 - j) * 4 + n < 11) {
          p = 3 * ((2 - j) * 4 + n) % 11;  // P(i) = n*i mod (4n-1) for 0 <= i < 4n-1
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
  }

  // the r-round
  // addRoundKey
  for (int j = 0; j < 3; ++j) {
    state[j] = state[j] ^ round_key[ROUNDS * 3 + j];
  }
}

// master_key: 80-bit
// state: 12-bit
void present_dec_12(u8 *state, const u8 *master_key) {
  u8 r = 1;
  u8 p;
  u32 t1, t2;
  u8 round_key[3*(ROUNDS+1)];
  // generateRoundKeys()
  present_gen_roundkey_dec(master_key, round_key);

  // 0~(r-1)-th rounds, where r = 10
  for (int i = 0; i < ROUNDS; ++i) {
    // addRoundKey
    for (int j = 0; j < 3; ++j) {
      state[j] = state[j] ^ round_key[i * 3 + j];
    }

    // pLayer
    // 12-bit state denoted s11s10...s1s0
    t1 = 0;  // t is the ans of bit permutation
    t2 = (state[2] & 0xf) + ((state[1] & 0xf) << 4) + ((state[0] & 0xf) << 8);

    for (int j = 0; j < 11; ++j) {
      p = 4 * j % 11;
      t1 += (((t2 >> j) & 1) << p);

    }
    t1 += (t2 >> 11) << 11;
    // update the state by the ans of bit permutation
    for (int j = 0; j < 3; ++j) {
      state[2 - j] = (t1 >> (j * 4)) & 0xf;
    }

    // sBoxLayer
    for (int j = 0; j < 3; ++j) {
      state[j] = SBOXINV_4[state[j]];
    }

  }

  // the r-round
  // addRoundKey
  for (int j = 0; j < 3; ++j) {
    state[j] = state[j] ^ round_key[r = ROUNDS * 3 + j];
  }
}