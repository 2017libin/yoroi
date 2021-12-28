#ifndef S_16_H
#define S_16_H

#include "common.h"

// key-dependent bijective 16-bit S-box
void S_16(u8 *state, u8 *subkey);

// the subkey is the reverse of the original subkey
// the inverse of S_16
void SINV_16(u8 *state, u8 *subkey);
#endif