#!/bin/bash

gcc -shared libf.c -o libf.so -fPIC
gcc -c open_lib.c -o open_lib.o 
gcc -c main.c -o main.o -O0
gcc main.o open_lib.o -o run -ldl

objdump -d run > run.s
