#!/bin/bash

PASSED=0
CHECKED=0
FAILED=0

declare -a FAILARRAY

echo "========================================"

echo "========================================"
echo "Force building YUCK compiler (just incase)"
make bin/c_compiler
if [[ "$?" -ne "0" ]]; then
    echo "Error while building compiler."
    exit 1;
fi

mkdir -p test/b_compiler/assembly
mkdir -p test/b_compiler/objects
mkdir -p test/b_compiler/outputs

N=0

for i in test/b_compiler/inputs/* ; do

    N=$(( $N+1 ));
    
    echo ""
    echo "==========================="
    echo "          TEST $N      "
    echo "==========================="
    echo ""

    # Compile test function with YUCK compiler under test to assembly
    bin/c_compiler -S test/b_compiler/inputs/$N.c -o test/b_compiler/assembly/$N.s 
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : YUCK Compiler returned error message."
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=$N;
        continue
    fi

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -mfp32 -o test/b_compiler/objects/$N.o -c test/b_compiler/assembly/$N.s
    if [[ $? -ne 0 ]]; then
        echo "ERROR : Couldn't compile driver program using GCC."
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=$N;
        continue
    fi

    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -mfp32 -static -o test/b_compiler/outputs/${N}_exe test/b_compiler/objects/$N.o test/b_compiler/drivers/$N.c
    if [[ $? -ne 0 ]]; then
        echo "ERROR : Linker returned error message."
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=$N;
        continue
    fi

    # Run the linked and assembled executable
    qemu-mips test/b_compiler/outputs/${N}_exe
    ret=$?
    if [[ $ret -ne 0 ]]; then
        echo "FAILED! Testcase returned $ret, but expected 0."
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=$N;
    else
        echo "PASSED!"
        PASSED=$(( ${PASSED}+1 ));
    fi

    CHECKED=$(( $CHECKED+1 ));

    echo""
done

echo "########################################"
echo "Passed ${PASSED} out of ${CHECKED}".
echo ""
echo "Failed cases:"
for case in "${FAILARRAY[*]}"
do
   echo $FAILARRAY[${case}]
done 