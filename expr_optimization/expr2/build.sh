#!/bin/bash

gcc -S main.c -o main.s -Wsuggest-attribute=pure -Wsuggest-attribute=const -O2 #-Q --help=optimizer
gcc main.c -o run 

sed -rn '/^expr_O0:/,/ret/p' main.s > expr_O0.s
sed -rn '/^expr_O2_gcse:/,/ret/p' main.s > expr_O2_gcse.s
sed -rn '/^expr_O2_gcse_const:/,/ret/p' main.s > expr_O2_gcse_const.s
sed -rn '/^expr_O2_gcse_const_reciprocal:/,/ret/p' main.s > expr_O2_gcse_const_reciprocal.s
sed -rn '/^expr_O2_gcse_const_reciprocal_asscociative:/,/ret/p' main.s > expr_O2_gcse_const_reciprocal_asscociative.s
