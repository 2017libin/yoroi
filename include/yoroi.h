#ifndef YOROI_H
#define YOROI_H

#include "common.h"


// -------------------------------------------yoroi16---------------------------------------------------

// master_key: K_len-byte
// round_key: 6-byte，used in S1,S2 and S3
void yoroi16_keyschedule(const u8 *master_key, u8 *round_key);

// gen the RK_len-byte round_key
void yoroi16_gen_roundkey_enc(const u8 *master_key, u8 *round_key);
void yoroi16_gen_roundkey_dec(const u8 *master_key, u8 *round_key);

// the linear layer in yoroi16
void mul_M8(u8 x[16]);
void mul_MINV8(u8 x[16]);

// enc in black-box context
// the 6-byte key is used by S1,S2,S3 func
void yoroi16_enc(u8 *x,const u8 *key);

// dec in black-box context
void yoroi16_dec(u8 *x,const u8 *key);

// regard the x[i*2]||x[i*+1] as a block, where i in [0, 7]
void yoroi16_wbenc(u8 *x);

void yoroi16_wbdec(u8 *x);

// -----------------------------------------------------------------------------------------------------

#endif