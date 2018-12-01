#!/bin/bash

gcc -S main.c -o main.s -Wsuggest-attribute=pure -Wsuggest-attribute=const -O2 -fjump-tables #-Q --help=optimizer
gcc main.c -o run 

sed -rn '/^f_switch_table:/,/ret/p' main.s > switch_table.s
sed -rn '/^f_switch_no_table:/,/ret/p' main.s > switch_no_table.s
sed -rn '/^f_if:/,/ret/p' main.s > if.s
