#!/bin/bash
tigress --Seed=0 \
   --Environment=x86_64:Linux:Gcc:4.6 \
   --Inputs="+1:int:42,-1:length:1?10" \
   --Transform=InitImplicitFlow \
      --Functions=yoroi16_wbenc \
   --Transform=InitEntropy \
   --Transform=InitOpaque \
      --Functions=yoroi16_wbenc \
      --InitOpaqueCount=2 \
      --InitOpaqueStructs=list,array,input,env \
   --Transform=AddOpaque \
      --Functions=yoroi16_wbenc \
      --AddOpaqueKinds=question \
      --AddOpaqueSplitKinds=inside \
      --AddOpaqueCount=10 \
   wb_yoroi16.c --out=addopaque.c