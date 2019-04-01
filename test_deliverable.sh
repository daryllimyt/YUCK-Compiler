#!/bin/bash
PASSED=0
CHECKED=0
FAILED=0

declare -a FAILARRAY

make bin/c_compiler

if [[ -z "$1" ]]; then 
    COMPILER=bin/c_compiler
else
    COMPILER=$1
fi

have_compiler=0
if [[ ! -f bin/c_compiler ]] ; then
    >&2 echo "Warning : cannot find compiler at path ${COMPILER}."
    have_compiler=1
fi

input_dir="test_deliverable/test_cases"
output_dir="test_deliverable/outputs"

mkdir -p ${output_dir}


for DRIVER in $input_dir/*_driver.c ; do

    CHECKED=$(( ${CHECKED}+1 ));
    
    NAME=$(basename $DRIVER _driver.c)
    TESTCODE=$input_dir/$NAME
    OUTPUT=$output_dir/$NAME
    EXECUTABLE=$output_dir/${NAME}_exe
    
    echo ""
    echo "==========================="
    echo " TEST: $NAME"
    echo "==========================="
    echo ""
    
    if [[ ${have_compiler} -ne 0 ]] ; then
        echo "Warning! YUCK compiler not found!"
        echo ""
    fi

    # Compile test function with YUCK compiler under test to assembly
    $COMPILER -S $TESTCODE.c -o $OUTPUT.s 
    if [[ $? -ne 0 ]]; then
        >&2 echo "ERROR : YUCK Compiler returned error message."
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=${NAME};
        continue
    fi

    # Compile driver with normal GCC
    mips-linux-gnu-gcc -mfp32 -o $OUTPUT.o -c $OUTPUT.s
    if [[ $? -ne 0 ]]; then
        echo "ERROR : Couldn't compile driver program using GCC."
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=${NAME};
        continue
    fi
    
    # Link driver object and assembly into executable
    mips-linux-gnu-gcc -mfp32 -static -o $EXECUTABLE $OUTPUT.o $DRIVER
    if [[ $? -ne 0 ]]; then
        echo "ERROR : Linker returned error message."
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=${NAME};
        continue
    fi
    
    
    # Run the actual executable
    qemu-mips $EXECUTABLE
    

    ret=$?
    if [[ $ret -ne 0 ]]; then
        echo "FAILED! Testcase returned $ret, but expected 0."
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=${NAME};
    else
        echo "PASSED!"
        PASSED=$(( ${PASSED}+1 ));
    fi

    

    echo ""
    

done


echo "########################################"
echo "Passed ${PASSED} out of ${CHECKED}".
echo ""
echo "Failed cases:"
for case in "${FAILARRAY[*]}"
do
   echo $FAILARRAY[${case}]
done 