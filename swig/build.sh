#!/bin/bash

# =============================================================================

# specify target language (e.g. pyton, ruby, tcl, perl, xml ...)
target_language="python"

# C file name
c_file_prefix="c_module"

# specify output target language module name (e.g. *.py, *.rb, *.tcl ...)
output_python_module_prefix="${c_file_prefix}"

# specify *.so name (leading '_' make PyInit_c_module -> PyInit__c_module is necessary)
module_so_name="_${c_file_prefix}.so"

# specify C compile option
c_compile_option="-Wall -std=c99 -O -fPIC -I/usr/include/python3.8"

# specify C link option
c_link_option="-shared -lm -lpython3.8"

echo "====================================================="
echo "Following shows user's configuration:"
echo "+ target_language=${target_language}"
echo "+ c_file_prefix=${c_file_prefix}"
echo "+ output_wrapper_prefix=${output_wrapper_prefix}"
echo "+ output_python_module_prefix=${output_python_module_prefix}"
echo "+ module_so_name=${module_so_name}"
echo "+ c_compile_option=${c_compile_option}"
echo "+ c_link_option=${c_link_option}"
echo ""

# =============================================================================
# XXX Do not modify following command
# specify output C wrapper name
output_wrapper_prefix="${c_file_prefix}_wrap"

# speify convert C -> wrapper compile option
siwg_compile_options="-Wall -O"

# specify siwg debug information show on terminal
swig_debug_options="-v"

# converge *.c to wrapper
echo -e "\n====================================================="
echo "Swig compile ${c_file_prefix}.c -> ${output_wrapper_prefix}.c ..."
set -x
swig ${siwg_compile_options} -module ${output_python_module_prefix} ${swig_debug_options} -${target_language} c_module.i 
set +x
if [ $? -ne 0 ]; then
        echo "[Error] swig compile ${c_file_prefix}.c -> ${output_wrapper_prefix}.c fail"
        exit 1
fi

# compile .c -> .o
echo -e "\n====================================================="
echo "gcc compile ${c_file_prefix}.c -> ${c_file_prefix}.o ..."
set -x
gcc -c ${c_file_prefix}.c -o ${c_file_prefix}.o ${c_compile_option} 
set +x
if [ $? -ne 0 ]; then
        echo "[Error] gcc compile ${c_file_prefix}.c -> $c_file_prefix}.o fail"
        exit 1
fi

echo "gcc compile ${output_wrapper_prefix}.o -> ${output_wrapper_prefix}.o ..."
set -x
gcc -c ${output_wrapper_prefix}.c -o ${output_wrapper_prefix}.o ${c_compile_option} 
set +x
if [ $? -ne 0 ]; then
        echo "[Error] gcc compile ${output_wrapper_prefix}.c -> ${output_wrapper_prefixo}.o fail"
        exit 1
fi

# make wrapper to *.so
echo -e "\n====================================================="
echo "gcc link ${module_so_name} ..."
set -x
gcc ${c_file_prefix}.o ${output_wrapper_prefix}.o ${c_link_option} -o ${module_so_name}
set +x
if [ $? -ne 0 ]; then
        echo "[Error] gcc link ${output_wrapper_prefix}.o -> ${module_so_name} fail"
        exit 1
fi

echo -e "\n====================================================="
echo "Complete"
