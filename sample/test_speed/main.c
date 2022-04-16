#include <stdio.h>
#include <time.h>
#include "internal.h"

#define TEST 10000

extern ELEM_TYPE x[];

int main() {
    ELEM_TYPE *x = malloc(sizeof(ELEM_TYPE)*range);
    ELEM_TYPE *x_inv = malloc(sizeof(ELEM_TYPE)*range);

    // intial array x by binary file
    FILE *fp = fopen("test.bin", "rb");
    fread(x, sizeof(ELEM_TYPE), range, fp);
    fclose(fp);

    double u = clock();

    for (size_t i = 0; i < TEST; i++)
    {
        for (size_t j = 0; j < range; j++)
        {
            x_inv[x[j]] = j;
        } 
    }

    double v = clock() - u;
    printf("run %d times, average run time: %.7fs\n",TEST, v / TEST / CLOCKS_PER_SEC );
    free(x);
    free(x_inv);
    return 0;
}


