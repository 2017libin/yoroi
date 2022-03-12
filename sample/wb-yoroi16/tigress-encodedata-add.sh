#!/bin/bash
tigress --Seed=66 --Statistics=0 --Verbosity=1 --Environment=x86_64:Linux:Gcc:4.6  \
   --Transform=EncodeData \
      --GlobalVariables='T1,T2,T3,T1_inv,T2_inv,T3_inv' \
      --EncodeDataCodecs=add \
   --out=./yoroi_add.c ./wb_yoroi16.c
      # --out=./out/test-tigress.c ./in/test.c
# ./a.out

# rm a.out
