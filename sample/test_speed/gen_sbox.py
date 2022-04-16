import random

# size是bit长度
def gen_sbox(size:int):
    per = list(range(0,2**size))
    random.shuffle(per)
    lines = []

    if size == 16:
        lines.append("unsigned short x[] = {\n")
    elif size == 32:
        lines.append("unsigned int x[] = {\n")
    elif size == 64:
        lines.append("unsigned long x[] = {\n")
    else:
        print("输入无效size!")
        return -1

    # lines.append()
    count = 0
    line_t = "\t"
    print(len(per))
    for x in per:
        line_t += str(x) + ','
        count += 1
        # 每16个元素换行
        if count == 16:
            lines.append(line_t+"\\\n")
            count = 0
            line_t = "\t"
    lines[-1] = lines[-1][:-3] + "\\\n"
    lines.append("};\n")

    with open("sbox.c", "w") as fp:
        fp.writelines(lines)

if __name__ == "__main__":
    gen_sbox(16)