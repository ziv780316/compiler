#!/bin/bash

# compile and check undefined function
gcc -c main.c -o main.o -g3 -
objdump -t main.o > sym
echo "* UND symbol:"
grep "UND" sym | sed 's/\t/ /g' | tr -s ' ' | cut -d ' ' -f 4 | nl

# show glibc version and path
libc_version=`ldd --version | grep -i "libc"`
libc_path=`gcc -print-file-name=libc.a | xargs realpath`
libm_path=`gcc -print-file-name=libm.a | xargs realpath`
n_obj=`ar tv $libc_path | wc -l`
if [ $n_obj -eq 0 ]; then
	echo "* libc ld script path: $libc_path"
	libc_path=`grep -i 'GROUP.*\s\+\S\+libc\S\+.a' $libc_path | sed 's/.*\s\(\S\+libc-\S\+.a\)\s.*/\1/'`
	if [ "$libc_path" == "" ]; then
		echo "[Error] cannot find libc.a"
		exit 1
	fi
fi
n_obj=`ar tv $libm_path | wc -l`
if [ $n_obj -eq 0 ]; then
	echo "* libm ld script path: $libm_path"
	libm_path=`grep -i 'GROUP.*\s\+\S\+libm\S\+.a' $libm_path | sed 's/.*\s\(\S\+libm-\S\+.a\)\s.*/\1/'`
	if [ "$libm_path" == "" ]; then
		echo "[Error] cannot find libm.a"
		exit 1
	fi
fi
echo "* libc version: $libc_version"
echo "* libc path: $libc_path"
echo "* libm path: $libm_path"

# link manual
printf_sym=`objdump -t $libc_path | grep '\.text\s\+.*\s\+printf$'`
if [ "$printf_sym" == "" ]; then
	echo "[Error] cannot find printf symbol in $libc_path"
	exit 1
fi
echo "* printf locate at libc.a -> $printf_sym"
exp_sym=`objdump -t $libm_path | grep '\.text\s\+.*\s\+exp$'`
if [ "$exp_sym" == "" ]; then
	echo "[Error] cannot find exp symbol in $libm_path"
	exit 1
fi
echo "* exp locate at libc.a -> $exp_sym"

echo "relocate ..."
ld -r main.o $libc_path $libm_path -o relocate.o 
gcc relocate.o -o test -static

echo "run test ..."
./test 10

