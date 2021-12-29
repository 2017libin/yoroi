#include "common.h"


// key-dependent bijective 16-bit S-box
void S_16(u8 *state, u8 *subkey) {
  u8 t0, t1;  // temporary var
  // 0-th round
  state[0] ^= subkey[0];
  state[1] ^= subkey[1];
  
  // 1~32-th rounds
  for (int i = 1; i <= 32; ++i) {
    // SB
    state[0] = SBOX_8[state[0]];
    state[1] = SBOX_8[state[1]];

    // MC
    t0 = state[0];
    t1 = state[1];
    state[0] = GMul8(A_16[0], t0) ^ GMul8(A_16[1], t1);
    state[1] = GMul8(A_16[2], t0) ^ GMul8(A_16[3], t1);

    // AK
    state[0] ^= subkey[i * 2];
    state[1] ^= subkey[i * 2 + 1];
  }
}

// the subkey is the reverse of the original subkey
void SINV_16(u8 *state, u8 *subkey) {
  u8 t0, t1;  // temporary var
  // 32-th round
  state[0] ^= subkey[0];
  state[1] ^= subkey[1];

  // 31~0-th rounds
  for (int i = 1; i <= 32; ++i) {
    // MC
    t0 = state[0];
    t1 = state[1];
    state[0] = GMul8(AINV_16[0], t0) ^ GMul8(AINV_16[1], t1);
    state[1] = GMul8(AINV_16[2], t0) ^ GMul8(AINV_16[3], t1);

    // SB
    state[0] = SBOXINV_8[state[0]];
    state[1] = SBOXINV_8[state[1]];

    // AK
    state[0] ^= subkey[i * 2];
    state[1] ^= subkey[i * 2 + 1];
  }
}
