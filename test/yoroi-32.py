import tools

'''
n = 128
l = 4
n_in = 32
m = 28
t = 4
MDS matrix = 
2 3 1 1
1 2 3 1
1 1 2 3
3 1 1 2
'''
# x = [0] * 2**32

# parameters
# Sbox
# sbox1,sbox1_inv = tools.gen_sbox(32)
# sbox2,sbox2_inv = tools.gen_sbox(32)
# sbox3,sbox3_inv = tools.gen_sbox(32)
# 32-bit bi

# p1 = tools.get_prime(32)
# p2 = tools.get_prime(32)
# p3 = tools.get_prime(32)

# p1_inv = 1
# while p1*p1_inv % 2**32 != 1:
#     p1_inv += 1

# p2_inv = 1
# while p2*p2_inv % 2**32 != 1:
#     p2_inv += 1

# p3_inv = 1
# while p3*p3_inv % 2**32 != 1:
#     p3_inv += 1

# print(p1)
# print(p1_inv)
# print(p2)
# print(p2_inv)
# print(p3)
# print(p3_inv)

p1 = 2251353311
p1_inv = 1171640095
p2 = 3125116693
p2_inv = 119265341
p3 = 3782377831
p3_inv = 2176322135


def sbox1(x):
    return x*p1 % 2**32


def sbox1_inv(x):
    return x*p1_inv % 2**32


def sbox2(x):
    return x*p2 % 2**32


def sbox2_inv(x):
    return x*p2_inv % 2**32


def sbox3(x):
    return x*p3 % 2**32


def sbox3_inv(x):
    return x*p3_inv % 2**32


t = 112
st = sbox1(t)
t1 = sbox1_inv(st)
print(t1)

# MDS matrix
M = [2, 1, 1, 3, 3, 2, 1, 1, 1, 3, 2, 1, 1, 1, 3, 2]  # save with column

# MDS inverse matrix
M_inv = [14, 9, 13, 11, 11, 14, 9, 13, 13, 11, 14, 9, 9, 13, 11, 14]  #

# compute MDS inverse matrix


def comput_M_inv():
    for a in range(1, 16):
        for b in range(1, 16):
            for c in range(1, 16):
                for d in range(1, 16):
                    if tools.mul_gf4(a, 2) ^ tools.mul_gf4(b, 3) ^ tools.mul_gf4(c, 1) ^ tools.mul_gf4(d, 1) == 0 and \
                            tools.mul_gf4(a, 1) ^ tools.mul_gf4(b, 2) ^ tools.mul_gf4(c, 3) ^ tools.mul_gf4(d, 1) == 0 and \
                            tools.mul_gf4(a, 1) ^ tools.mul_gf4(b, 1) ^ tools.mul_gf4(c, 2) ^ tools.mul_gf4(d, 3) == 0 and \
                            tools.mul_gf4(a, 3) ^ tools.mul_gf4(b, 1) ^ tools.mul_gf4(c, 1) ^ tools.mul_gf4(d, 2) == 1:
                        print(a, b, c, d)


def mul_M(x):
    x0 = x[0] & 0xf
    x1 = x[1] & 0xf
    x2 = x[2] & 0xf
    x3 = x[3] & 0xf

    for i in range(4):
        tmp = tools.mul_gf4(x0, M[i*4]) ^ tools.mul_gf4(x1, M[i*4+1]
                                                        ) ^ tools.mul_gf4(x2, M[i*4+2]) ^ tools.mul_gf4(x3, M[i*4+3])
        x[i] = (x[i] & 0xfffffff0) ^ tmp


def mul_M_inv(x):
    x0 = x[0] & 0xf
    x1 = x[1] & 0xf
    x2 = x[2] & 0xf
    x3 = x[3] & 0xf

    for i in range(4):
        tmp = tools.mul_gf4(x0, M_inv[i*4]) ^ tools.mul_gf4(x1, M_inv[i*4+1]
                                                            ) ^ tools.mul_gf4(x2, M_inv[i*4+2]) ^ tools.mul_gf4(x3, M_inv[i*4+3])
        x[i] = (x[i] & 0xfffffff0) ^ tmp


def encrypt(x):
    # [1，R-1]-th rounds
    for i in range(1, 16):  # 1 <= i <= 15
        # S-layer
        if i == 1:
            for j in range(4):
                x[j] = sbox1(x[j])
        else:
            for j in range(4):
                x[j] = sbox2(x[j])

        # Affine layer
        for j in range(4):
            x[j] = x[j] ^ i

        # Linear layer
        mul_M(x)

    # R-th round
    # S-layer
    for j in range(4):
        x[j] = sbox3(x[j])

    # AES layer


def decrypt(x):
    # [1，R-1]-th rounds
    for i in range(1, 16):  # 1 <= i <= 15
        # S-layer
        if i == 1:
            for j in range(4):
                x[j] = sbox3_inv(x[j])
        else:
            for j in range(4):
                x[j] = sbox2_inv(x[j])

        # Affine layer
        for j in range(4):
            x[j] = x[j] ^ (16-i)

        # Linear layer
        mul_M_inv(x)

    # R-th round
    # S-layer
    for j in range(4):
        x[j] = sbox1_inv(x[j])

    # AES layer


if __name__ == '__main__':
    pass
    x = [1, 2, 3, 4]  # 4*32-bit
    # encrypt(x)
    # print(x)
    # decrypt(x)
    # print(x)
    mul_M(x)
    print(x)
    mul_M_inv(x)
    print(x)
