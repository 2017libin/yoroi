import random 
import pyunit_prime
from sbox_16 import sbox1,sbox1_inv,sbox2,sbox2_inv,sbox3,sbox3_inv
from enc_dec_12 import enc,dec
from T_tables import T1,T2,T3

# 生成size-bit的置换表
# 返回：sbox、sbox_inv
def gen_sbox(size):
    sbox = list(range(2**size))
    
    random.shuffle(sbox)

    sbox_inv = [0] * 2**size
    for i in range(len(sbox)):
        sbox_inv[sbox[i]] = i

    return sbox,sbox_inv

# GF(2^4)上的乘法，不可约多项式：x^4 + x + 1
# 返回：c = a*b
def mul_gf4(a, b):
    c = 0
    for i in range(4):
        if b & 1 == 1:
            c ^= a
        flag = a & 0x8
        a <<= 1
        if flag == 0x8:
            a ^= 0x13  # 还是 a ^= 0x03
        b >>= 1
    return c

# 获取n-bit素数
def get_prime(bit_len):
    return pyunit_prime.get_large_prime_bit_size(bit_len)

# 生成enc、dec 12-bit伪随机置换
def gen_enc_dec_12():
    enc, dec = gen_sbox(12)
    print('enc =',enc)
    print('dec =',dec)

def gen_T_16():
    # gen T1
    T1 = []
    for i in range(2**16):
        tmp = sbox1[i]  # 先经过sbox

        msb_12 = enc[(tmp & 0xfff0) >> 4]  # msb_12再过enc
        lsb_4 = tmp & 0xf

        T1.append((msb_12 << 4) ^ lsb_4)
    
    # gen T2
    T2 = []
    for i in range(2**16):
        msb_12 = dec[(i & 0xfff0) >> 4]  # msb_12先经过dec
        lsb_4 = i & 0xf

        tmp = sbox2[(msb_12 << 4) ^ lsb_4] # 再过sbox2

        msb_12 = enc[(tmp & 0xfff0) >> 4]  # 最后msb_12再过enc
        lsb_4 = tmp & 0xf

        T2.append((msb_12 << 4) ^ lsb_4)

    # gen T3
    T3 = []
    for i in range(2**16):
        msb_12 = dec[(i & 0xfff0) >> 4]  # msb_12先经过dec
        lsb_4 = i & 0xf

        tmp = sbox3[(msb_12 << 4) ^ lsb_4] # 再过sbox3

        T3.append(tmp)

    print('T1 =', T1)
    print('T2 =', T2)
    print('T3 =', T3)

if __name__ == '__main__':
    x = 123
    x1 = sbox1[x]
    x2 = sbox2[x1]
    x3 = sbox3[x2]
    print(x3)

    y = 123
    y1 = T1[y]
    y2 = T2[y1]
    y3 = T3[y2]
    print(y3)

    # gen_T_16()