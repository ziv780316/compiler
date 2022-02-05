#!/bin/bash
gcc -c main.c -o main.o
gcc -c asm.s -o asm.o 
gcc main.o asm.o -o test
./test
