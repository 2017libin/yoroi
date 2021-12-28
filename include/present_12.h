#ifndef PRESENT_12_H
#define PRESENT_12_H

#include "common.h"

// master_key is the list of 8-bit
// round_key is the list of 4-bit
void present_keyschedule_12(u8 *master_key, u8 *round_key);

// Small Scale Variants of PRESENT
// state and subkey is the list of 4-bit
void present_enc_12(u8 *state, u8 *subkey);

void present_dec_12(u8 *state, u8 *subkey);

#endif