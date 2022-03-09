#ifndef WB_YOROI16_H
#define WB_YOROI16_H
typedef unsigned int u32;
typedef unsigned long u64;
typedef unsigned short u16;
typedef unsigned char u8;

// the T tables used in whitebox yoroi-16
extern unsigned short T1[65536];
extern unsigned short T2[65536];
extern unsigned short T3[65536];
extern unsigned short T1_inv[65536];
extern unsigned short T2_inv[65536];
extern unsigned short T3_inv[65536];

// regard the x[i*2]||x[i*+1] as a block, where i in [0, 7]
void yoroi16_wbenc(u8 *x);
void yoroi16_wbdec(u8 *x);
#endif