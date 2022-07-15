#!/bin/bash
# tigress --Seed=12 \
#    --Environment=x86_64:Linux:Gcc:4.6 \
#    --Transform=split \
#        --SplitKinds=deep,block,top \
#        --SplitCount=100 \
#        --Functions=yoroi16_wbenc \
#    --out=split.c wb_yoroi16.c
tigress --Seed=0 \
   --Environment=x86_64:Linux:Gcc:4.6 \
   --Transform=Split \
       --SplitKinds=deep,block,top \
       --SplitCount=100 \
       --Functions=yoroi16_wbenc \
   --out=split.c wb_yoroi16.c