#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Hash_DRBG/header/rand.h"  // 头文件中定义hash_rand库的接口
int test_sha256_hash_drbg_without_prediction_resistance(void);
int use_case();

int main111(){
    // return test_sha256_hash_drbg_without_prediction_resistance();
    double u = clock();
    use_case();
    double v = clock() - u;
    printf("运行时间: %.7fms\n", v/CLOCKS_PER_SEC*1000);

    return 0;
}

int use_case()
{
    void *ctx;
    size_t len = 50;
    unsigned char bytes[len];
    size_t seed_len = 60;  // 至少超过55byte
    unsigned char seed[seed_len];
    size_t add_len = 60;
    unsigned char add[add_len];
    int ret;
    // 分配空间并初始化ctx
    ret = anyan_rand_new_and_init(&ctx);

    // 获得长度为len的随机字节
    if(ret == 0){  // ret为0表示正确初始化
        ret = anyan_rand_seed(ctx, seed, seed_len);
    }else{
        printf("ctx new 或 init 出错！\nerror code: %d\n",ret);
        return -1;
    }
    // 获得长度为len的随机字节
    if(ret == 0){  // ret为0表示正确初始化
        ret = anyan_rand_bytes_with_add(ctx, bytes, len, add, add_len);
    }else{
        printf("ctx new 或 init 出错！\nerror code: %x\n",ret);
        return -1;
    }
    if (ret == 0){  // ret为0表示成功获取随机字节
        printf("rand bytes: \n");
        for (int i = 0; i < len; ++i)
        {
            printf("%d, ", bytes[i]);
        }
        printf("\n");
    }else{
        printf("生成rand bytes出错！\nerror code: %x\n", ret);
        anyan_rand_free(ctx);
        return -1;
    }
    // 释放ctx空间
    anyan_rand_free(ctx);
    return 0;
}

// 测试时需要将MIN_BYTE_LENGTH 和 MIN_ENTROPY_BYTE_LENGTH改为440
int test_sha256_hash_drbg_without_prediction_resistance(void)
{
    int error_code;

    unsigned char entropy[] = {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6,
                               0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13,
                               0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E,
                               0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
                               0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34,
                               0x35, 0x36};

    unsigned char nonce[] = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27}; // 不是到24？

    unsigned char personal_str[] = {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46,
                                    0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52,
                                    0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E,
                                    0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A,
                                    0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76};

    unsigned char additional_input[] = {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
                                        0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72,
                                        0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E,
                                        0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A,
                                        0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96};

    unsigned char additional_input2[] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,
                                         0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2,
                                         0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE,
                                         0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA,
                                         0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6};

    unsigned int entropy_len, nonce_len, personal_str_len, additional_input_len, additional_input2_len;
    unsigned char random_bytes[64];
    unsigned int random_bytes_len;
    // const EVP_MD *md;
    int i;

    printf("\n****************************************************\n");
    printf("First call to generate random bytes.\n");
    entropy_len = sizeof(entropy);
    nonce_len = sizeof(nonce);
    personal_str_len = sizeof(personal_str);
    additional_input_len = sizeof(additional_input);
    additional_input2_len = sizeof(additional_input2);
    random_bytes_len = sizeof(random_bytes);


    void *ctx;
    if (error_code = anyan_rand_new_and_init_with_entropy(&ctx,
                                                           entropy,
                                                           entropy_len,
                                                           nonce,
                                                           nonce_len,
                                                           personal_str,
                                                           personal_str_len))
    {
        printf("ctx new 或 init 出错！\nerror code: %d\n", error_code);
        return  -1;
    }
    if (error_code = anyan_rand_bytes_with_add(ctx,
                                               random_bytes,
                                               random_bytes_len,
                                               additional_input,
                                               additional_input_len))
    {
        printf("生成rand bytes出错！\nerror code: %d\n", error_code);
        anyan_rand_free(ctx);
        return -1;
    }

    printf("Generated bytes:\n");
    for (i = 0; i < (int)random_bytes_len; i++)
    {
        printf("0x%x  ", random_bytes[i]);
    }
    printf("\n");

    printf("\n****************************************************\n");
    printf("Second call to generate random bytes.\n");
    if (error_code = anyan_rand_bytes_with_add(ctx,
                                               random_bytes,
                                               random_bytes_len,
                                               additional_input2,
                                               additional_input2_len))
    {
        printf("生成rand bytes出错！\nerror code: %d\n", error_code);
        anyan_rand_free(ctx);
        return -1;
    }

    printf("Generated bytes:\n");
    for (i = 0; i < (int)random_bytes_len; i++)
    {
        printf("0x%x  ", random_bytes[i]);
    }
    printf("\n");

    anyan_rand_free(ctx);
    return 0;
}