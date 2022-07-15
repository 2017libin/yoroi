#!/bin/bash
tigress \
   --Environment=x86_64:Linux:Gcc:4.6 \
   --Transform=Virtualize \
      --Functions=yoroi16_wbenc \
      --VirtualizeDispatch=direct \
   --out=virtualize.c wb_yoroi16.c