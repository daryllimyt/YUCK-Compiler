#!/bin/bash

# Try to find a portable way of getting rid of
# any stray carriage returns
if which dos2unix ; then
    DOS2UNIX="dos2unix"
elif which fromdos ; then
    DOS2UNIX="fromdos"
else
    # This works on a GNU version of sed. I think this
    # will work in OSX as well, but don't have a machine
    # on which to test that. From reading the OSX docs,
    # it looks compatible.
    # The code \x0D is the ASCII code of carriage-return,
    # so it the regex should delete any CRs at the end of
    # a line (or anywhere in a line)
    DOS2UNIX="sed -e s/\x0D//g -"
    # Tested for combinations of:
    # - Ubuntu
    # - Cygwin
    # and inputs formats:
    # - LF
    # - CRLF
fi

echo "========================================"
echo "Cleaning the temporaries and outputs"
make clean


echo "========================================"
echo "Force building YUCK compiler (just incase)"
make -B yuck
if [[ "$?" -ne "0" ]]; then
    echo "Error while building compiler."
    exit 1;
fi

echo "========================================="
echo "Building comparator.."
g++ test/compiler/comparator.cpp -o bin/comparator
echo "========================================="


PASSED=0
CHECKED=0
FAILED=0

declare -a FAILARRAY


if [[ -z "$1" ]]; then 
    COMPILER=bin/c_compiler
else
    COMPILER=$1
fi

workingin="test/compiler/inputs"
workingout="test/compiler/outputs"
reference="test/compiler/reference"
return="test/compiler/returns"

mkdir -p -- ./$workingout
mkdir -p -- ./$return

for i in $workingin/* ; do
    
    NAME=$(basename $i .c)
    TESTCODE=$workingin/$NAME.c

    echo ""
    echo "==========================="
    echo "          TEST $NAME       "
    echo "==========================="
    echo ""

    # Compile test function with YUCK compiler under test to assembly
    $COMPILER -S $TESTCODE -o $workingout/${NAME}.s 

    echo "Simulating compiled program..."
    java -jar test/Mars4_5.jar nc sm \$v0 $workingout/${NAME}.s > $return/${NAME}.txt

    #compare output file and reference
    echo "Comparing output files..."
    # diff <(cat $return/${NAME}.txt) <(cat $reference/${NAME}.txt) > /dev/null	
    
    bin/comparator $return/${NAME}.txt $reference/${NAME}.txt


    if [[ $? -ne 0 ]]; then
        echo -e "FAILED!"
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=${NAME};
    else
        echo -e "PASSED!"
        PASSED=$(( ${PASSED}+1 ));
    fi

    CHECKED=$(( ${CHECKED}+1 ));

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
echo ""
echo "########################################"


RELEASE=$(lsb_release -d)
if [[ $? -ne 0 ]]; then
    echo ""
    echo "Warning: This appears not to be a Linux environment"
    echo "         Encouraged to run this on a lab machine or an Ubuntu VM"
else
    grep -q "Ubuntu 16.04" <(echo $RELEASE)
    FOUND=$?

    if [[ $FOUND -ne 0 ]]; then
        echo ""
        echo "Warning: This appears not to be the target environment"
        echo "         Encouraged to run this on a lab machine or an Ubuntu VM"
    fi
fi




