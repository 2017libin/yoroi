#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "internal.h"

void shuffle(ELEM_TYPE *x){
    // init array to [0,1,2,...,range-1]
    for (size_t i = 0; i < range; ++i)
        x[i] = i;
    // init seed
    srand((unsigned)time(NULL));
    ELEM_TYPE index, tmp;

    // shuffle array
    for (size_t i = 0; i < range; i++)
    {
        // swap x[i] withe x[index], where index = rand(i, range)
        index = i + rand()%(range-i);
        tmp = x[i];
        x[i] = x[index];
        x[index] = tmp;
    }
}

void gen_sbox(ELEM_TYPE *x){
    FILE *fp = NULL; 
    fp = fopen("sbox.c", "w");
    size_t count = 0;
    if (TABLE_SIZE == 16)
    {
        fprintf(fp, "unsigned short x[] = {\n\t");
    }else if (TABLE_SIZE == 32)
    {
        fprintf(fp, "unsigned int x[] = {\n\t");
    }
    for (size_t i = 0; i < range-1; i++)
    {
        fprintf(fp, "%u,", x[i]);
        ++count;
        if(!(count % 16)){
            count = 0;
            fprintf(fp, "\\\n\t");
        }
    }
    fprintf(fp, "%u\n};\n", x[range-1]);
    fclose(fp);
}

void gen_sbox_bin(ELEM_TYPE *x){
    FILE *fp = NULL;
    fp = fopen("test.bin", "wb");
    fwrite(x, sizeof(ELEM_TYPE), range, fp);
    fclose(fp);

    // ELEM_TYPE *x_t = malloc(sizeof(ELEM_TYPE)*range);
    // fp = fopen("test.bin", "rb");
    // fread(x_t, sizeof(ELEM_TYPE), range, fp);
    // fclose(fp);

    // for (size_t i = 0; i < 100; i++)
    // {
    //     fprintf(stdout, "%d, %d\n", x[i], x_t[i]);
    // }

    // free(x_t);
}

int main(){
    ELEM_TYPE *x = malloc(sizeof(ELEM_TYPE)*range);
    shuffle(x);
    gen_sbox_bin(x);
    free(x);
    return 0;
}