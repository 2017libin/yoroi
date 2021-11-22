import random
import pyunit_prime
from sbox_16 import sbox1, sbox1_inv, sbox2, sbox2_inv, sbox3, sbox3_inv
from enc_dec_12 import enc, dec
from T_tables import T1, T2, T3

# 生成size-bit的置换表
# 返回：sbox、sbox_inv
def gen_sbox(size):
    sbox = list(range(2**size))

    random.shuffle(sbox)

    sbox_inv = [0] * 2**size
    for i in range(len(sbox)):
        sbox_inv[sbox[i]] = i

    return sbox, sbox_inv

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
    print('enc =', enc)
    print('dec =', dec)

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

        tmp = sbox2[(msb_12 << 4) ^ lsb_4]  # 再过sbox2

        msb_12 = enc[(tmp & 0xfff0) >> 4]  # 最后msb_12再过enc
        lsb_4 = tmp & 0xf

        T2.append((msb_12 << 4) ^ lsb_4)

    # gen T3
    T3 = []
    for i in range(2**16):
        msb_12 = dec[(i & 0xfff0) >> 4]  # msb_12先经过dec
        lsb_4 = i & 0xf

        tmp = sbox3[(msb_12 << 4) ^ lsb_4]  # 再过sbox3

        T3.append(tmp)

    print('T1 =', T1)
    print('T2 =', T2)
    print('T3 =', T3)

def gen_TINV_16():
    T1_inv = [0]*65536
    for i in range(len(T1)):
        T1_inv[T1[i]] = i

    T2_inv = [0]*65536
    for i in range(len(T1)):
        T2_inv[T2[i]] = i
    
    T3_inv = [0]*65536
    for i in range(len(T1)):
        T3_inv[T3[i]] = i
    return T1_inv,T2_inv,T3_inv

def print_TINV():
    T1_inv,T2_inv,T3_inv = gen_TINV_16()
    count = 0
    print("const unsigned int T1_inv[] = {", end="")
    for i in T1_inv:
        count += 1
        print(str(i)+", ", end="")
        if (count % 9 == 0):
            print("")

    count = 0
    print("const unsigned int T2_inv[] = ", end="")
    for i in T2_inv:
        count += 1
        print(str(i)+", ", end="")
        if (count % 9 == 0):
            print("")

    count = 0
    print("const unsigned int T3_inv[] = ", end="")
    for i in T3_inv:
        count += 1
        print(str(i)+", ", end="")
        if (count % 9 == 0):
            print("")

if __name__ == '__main__':
    print_TINV()
    # x = get_prime(16)
    # print(x)
    # x = 123
    # x1 = sbox1[x]
    # x2 = sbox2[x1]
    # x3 = sbox3[x2]
    # print(x3)

    # y = 123
    # y1 = T1[y]
    # y2 = T2[y1]
    # y3 = T3[y2]
    # print(y3)
    # gf4mul = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 2, 4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13, 0, 3, 6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2, 0, 4, 8, 12, 3, 7, 11, 15, 6, 2, 14, 10, 5, 1, 13, 9, 0, 5, 10, 15, 7, 2, 13, 8, 14, 11, 4, 1, 9, 12, 3, 6, 0, 6, 12, 10, 11, 13, 7, 1, 5, 3, 9, 15, 14, 8, 2, 4, 0, 7, 14, 9, 15, 8, 1, 6, 13, 10, 3, 4, 2, 5, 12, 11,
    #           0, 8, 3, 11, 6, 14, 5, 13, 12, 4, 15, 7, 10, 2, 9, 1, 0, 9, 1, 8, 2, 11, 3, 10, 4, 13, 5, 12, 6, 15, 7, 14, 0, 10, 7, 13, 14, 4, 9, 3, 15, 5, 8, 2, 1, 11, 6, 12, 0, 11, 5, 14, 10, 1, 15, 4, 7, 12, 2, 9, 13, 6, 8, 3, 0, 12, 11, 7, 5, 9, 14, 2, 10, 6, 1, 13, 15, 3, 4, 8, 0, 13, 9, 4, 1, 12, 8, 5, 2, 15, 11, 6, 3, 14, 10, 7, 0, 14, 15, 1, 13, 3, 2, 12, 9, 7, 6, 8, 4, 10, 11, 5, 0, 15, 13, 2, 9, 6, 4, 11, 1, 14, 12, 3, 8, 7, 5, 10]
    # x = 10
    # y = 11
    # z = (x << 4) + y
    # print(gf4mul[z])
    # print(mul_gf4(x, y))
    # gen sboxinv_4
    sbox = [0,1,9,0xe,0xd,0xb,7,6,0xf,2,0xc,5,0xa,4,3,8]
    sboxinv = [0]*16
    for i in range(len(sbox)):
        sboxinv[sbox[i]] = i
    print(sboxinv)
    
    x = get_prime(16)
    print(x)
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
    gf4mul = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 2, 4, 6, 8, 10, 12, 14, 3, 1, 7, 5, 11, 9, 15, 13, 0, 3, 6, 5, 12, 15, 10, 9, 11, 8, 13, 14, 7, 4, 1, 2, 0, 4, 8, 12, 3, 7, 11, 15, 6, 2, 14, 10, 5, 1, 13, 9, 0, 5, 10, 15, 7, 2, 13, 8, 14, 11, 4, 1, 9, 12, 3, 6, 0, 6, 12, 10, 11, 13, 7, 1, 5, 3, 9, 15, 14, 8, 2, 4, 0, 7, 14, 9, 15, 8, 1, 6, 13, 10, 3, 4, 2, 5, 12, 11,
              0, 8, 3, 11, 6, 14, 5, 13, 12, 4, 15, 7, 10, 2, 9, 1, 0, 9, 1, 8, 2, 11, 3, 10, 4, 13, 5, 12, 6, 15, 7, 14, 0, 10, 7, 13, 14, 4, 9, 3, 15, 5, 8, 2, 1, 11, 6, 12, 0, 11, 5, 14, 10, 1, 15, 4, 7, 12, 2, 9, 13, 6, 8, 3, 0, 12, 11, 7, 5, 9, 14, 2, 10, 6, 1, 13, 15, 3, 4, 8, 0, 13, 9, 4, 1, 12, 8, 5, 2, 15, 11, 6, 3, 14, 10, 7, 0, 14, 15, 1, 13, 3, 2, 12, 9, 7, 6, 8, 4, 10, 11, 5, 0, 15, 13, 2, 9, 6, 4, 11, 1, 14, 12, 3, 8, 7, 5, 10]
    x = 10
    y = 11
    z = (x << 4) + y
    print(gf4mul[z])
    print(mul_gf4(x, y))
    # for i in range(256):
    #     print(str(mul_gf4(i>>4, i&0xf))+", ",end="")

    # x = mul_gf4(10,3)
    # print(x)
    # gen_T_16()
