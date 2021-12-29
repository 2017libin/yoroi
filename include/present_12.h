#ifndef PRESENT_12_H
#define PRESENT_12_H

#include "common.h"

// master_key is the list of 8-bit
// round_key is the list of 4-bit
void present_keyschedule_12(const u8 *master_key, u8 *round_key);

// master_key：8*10-bit
// round_key: 4*3*(ROUND+1)-bit
void present_gen_roundkey_enc(const u8 *master_key, u8 *round_key);
void present_gen_roundkey_dec(const u8 *master_key, u8 *round_key);

// master_key: 80-bit
// state: 12-bit
void present_enc_12(u8 *state, const u8 *master_key);
void present_dec_12(u8 *state, const u8 *master_key);

#endif