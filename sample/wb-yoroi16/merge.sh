#!/bin/bash
tigress \
   --Environment=x86_64:Linux:Gcc:4.6 \
   --Transform=Merge \
      --Functions=yoroi16_wbenc,yoroi16_wbdec \
   --out=merge.c wb_yoroi16.c
