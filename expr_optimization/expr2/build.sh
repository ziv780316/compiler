#!/bin/bash

flags="O0 O3 Ofast"

for flag in $flags; do
	echo "compile with $flag ..."
	gcc -S expr.c -o expr_${flag}.s -${flag}
	gcc expr.c -o expr_${flag} -${flag}
done
