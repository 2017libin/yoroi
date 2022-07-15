#!/bin/bash
tigress \
   --Environment=x86_64:Linux:Gcc:4.6 \
   --Transform=Flatten \
      --Functions=yoroi16_wbenc \
   --out=flatten.c wb_yoroi16.c
