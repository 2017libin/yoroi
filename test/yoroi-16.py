'''
parameters:
n = 128
l = 8
n_in = 16
m = 12
t = 4
R = 8

MSD matrix:
5 4 A 6 2 D 8 3
4 5 6 A D 2 3 8
A 6 5 4 8 3 2 D
6 A 4 5 3 8 D 2
2 D 8 3 5 4 A 6
D 2 3 8 4 5 6 A
8 3 2 D A 6 5 4
3 8 D 2 6 A 4 5 

MSD matrix:
'''
import tools
from sbox_16 import sbox1, sbox1_inv, sbox2, sbox2_inv, sbox3, sbox3_inv
from T_tables import T1, T2, T3

# MDS matrix
M = [5, 4, 0xa, 6, 2, 0xd, 8, 3, 4, 5, 6, 0xa, 0xd, 2, 3, 8, 0xa, 6, 5, 4, 8, 3, 2, 0xd, 6, 0xa, 4, 5, 3, 8, 0xd, 2, 2, 0xd,
     8, 3, 5, 4, 0xa, 6, 0xd, 2, 3, 8, 4, 5, 6, 0xa, 8, 3, 2, 0xd, 0xa, 6, 5, 4, 3, 8, 0xd, 2, 6, 0xa, 4, 5]  # save with column

# MDS inverse matrix
M_inv = [7, 3, 14, 11, 8, 1, 6, 12, 3, 7, 11, 14, 1, 8, 12, 6, 14, 11, 7, 3, 6, 12, 8, 1, 11, 14, 3, 7, 12, 6, 1,
         8, 8, 1, 6, 12, 7, 3, 14, 11, 1, 8, 12, 6, 3, 7, 11, 14, 6, 12, 8, 1, 14, 11, 7, 3, 12, 6, 1, 8, 11, 14, 3, 7]  #

def mul_M(x):
    x0 = x[0] & 0xf
    x1 = x[1] & 0xf
    x2 = x[2] & 0xf
    x3 = x[3] & 0xf
    x4 = x[4] & 0xf
    x5 = x[5] & 0xf
    x6 = x[6] & 0xf
    x7 = x[7] & 0xf

    for i in range(8):
        tmp = tools.mul_gf4(x0, M[i*8]) ^ tools.mul_gf4(x1, M[i*8+1]) ^ tools.mul_gf4(x2, M[i*8+2]) ^ tools.mul_gf4(
            x3, M[i*8+3]) ^ tools.mul_gf4(x4, M[i*8+4]) ^ tools.mul_gf4(x5, M[i*8+5]) ^ tools.mul_gf4(x6, M[i*8+6]) ^ tools.mul_gf4(x7, M[i*8+7])
        x[i] = (x[i] & 0xfff0) ^ tmp


def mul_M_inv(x):
    x0 = x[0] & 0xf
    x1 = x[1] & 0xf
    x2 = x[2] & 0xf
    x3 = x[3] & 0xf
    x4 = x[4] & 0xf
    x5 = x[5] & 0xf
    x6 = x[6] & 0xf
    x7 = x[7] & 0xf

    for i in range(8):
        tmp = tools.mul_gf4(x0, M_inv[i*8]) ^ tools.mul_gf4(x1, M_inv[i*8+1]) ^ tools.mul_gf4(x2, M_inv[i*8+2]) ^ tools.mul_gf4(x3, M_inv[i*8+3]
                                                                                                                                ) ^ tools.mul_gf4(x4, M_inv[i*8+4]) ^ tools.mul_gf4(x5, M_inv[i*8+5]) ^ tools.mul_gf4(x6, M_inv[i*8+6]) ^ tools.mul_gf4(x7, M_inv[i*8+7])
        x[i] = (x[i] & 0xfff0) ^ tmp


def encrypt(x):
    # [1，R-1]-th rounds, R = 8
    for i in range(1, 8):
        # S-layer
        if i == 1:
            for j in range(8):
                x[j] = sbox1[x[j]]
        else:
            for j in range(8):
                x[j] = sbox2[x[j]]

        # Affine layer
        for j in range(8):
            x[j] = x[j] ^ i

        # Linear layer
        mul_M(x)

    # R-th round
    # S-layer
    for j in range(8):
        x[j] = sbox3[x[j]]
    pass
    # AES layer


def decrypt(x):
    # [1，R-1]-th rounds
    for i in range(1, 8):
        # S-layer
        if i == 1:
            for j in range(8):
                x[j] = sbox3_inv[x[j]]
        else:
            for j in range(8):
                x[j] = sbox2_inv[x[j]]

        # Linear layer and Affine layer can exchange position
        # Linear layer
        mul_M_inv(x)

        # Affine layer
        for j in range(8):
            x[j] = x[j] ^ (8-i)

    # R-th round
    # S-layer
    for j in range(8):
        x[j] = sbox1_inv[x[j]]

    # AES layer


def wb_encrypt(x):
    # [1，R-1]-th rounds, R = 8
    for i in range(1, 8):  # x[i] is 16-bit
        # S-layer
        if i == 1:
            for j in range(8):
                x[j] = T1[x[j]]
        else:
            for j in range(8):
                x[j] = T2[x[j]]

        # Affine layer
        for j in range(8):
            x[j] = x[j] ^ i

        # Linear layer
        mul_M(x)

    # R-th round
    # S-layer
    for j in range(8):
        x[j] = T3[x[j]]
    pass
    # AES layer


def printT():
    print("static const u32 T3 = {", end="")
    for i in range(len(T3)):
        print(str(hex(T3[i]))+", ", end="")
        if i > 0 and i % 2**8 == 0:
            print("\\")
    print("};")


if __name__ == '__main__':
    # printT()
    # pass
    x = [0x0011, 0x2233, 0x4455, 0x6677, 0x8899,
         0xaabb, 0xccdd, 0xeeff]  # 8*16-bit
    # print(x)
    # # mul_M_inv(x)
    # # for i in x:
    # #     print(hex(i), end="")

    # # black-box enc
    # encrypt(x)
    # print(x)

    # decrypt(x)
    # print(x)

    y = [0x0011, 0x2233, 0x4455, 0x6677, 0x8899,
         0xaabb, 0xccdd, 0xeeff]  # 8*16-bit
    # print(y)

    # white-box enc
    wb_encrypt(y)
    for i in y:
        print(hex(i), end="")
    # print(y)

    # decrypt(y)
    # print(y)
