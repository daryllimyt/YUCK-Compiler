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


PASSED=0
CHECKED=0
FAILED=0

declare -a FAILARRAY

if [[ "$1" != "" ]] ; then
    compiler="$1"
else
    compiler="bin/c_compiler"
fi

have_compiler=0
if [[ ! -f bin/c_compiler ]] ; then
    >&2 echo "Warning : cannot find compiler at path ${compiler}. Only checking C reference against python reference."
    have_compiler=1
fi

input_dir="test/translator/inputs"
out_dir="test/translator/outputs"
ref_dir="test/translator/reference"

mkdir -p ${out_dir}

for i in ${input_dir}/*.c ; do
    base=$(echo $i | sed -E -e "s|${input_dir}/([^.]+)[.]c|\1|g");
    
    echo ""
    echo "==========================="
    echo "          TEST $base       "
    echo "==========================="
    echo ""

    # Compile the reference C version
    gcc $i -o $out_dir/$base
    
    # Run the reference C version
    $out_dir/$base
    REF_C_OUT=$?
    
    # Run the reference python version
    python3 ${ref_dir}/$base.py
    REF_P_OUT=$?
    
    if [[ ${have_compiler} -eq 0 ]] ; then
        
        # Create the DUT python version by invoking the compiler with translation flags
        $compiler --translate $i -o ${out_dir}/$base-got.py

        # Run the DUT python version
        python ${out_dir}/$base-got.py
        GOT_P_OUT=$?
    fi
    
    if [[ $REF_C_OUT -ne $REF_P_OUT ]] ; then
        echo "$base, REF_FAIL, Expected ${REF_C_OUT}, got ${REF_P_OUT}"

        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=${base};

    elif [[ ${have_compiler} -ne 0 ]] ; then
        echo "$base, Fail, No C compiler/translator"

        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=${base};

    elif [[ $REF_C_OUT -ne $GOT_P_OUT ]] ; then
        echo "FAILED! Expected ${REF_C_OUT}, got ${GOT_P_OUT}"
        FAILED=$(( ${FAILED}+1 ));
        FAILARRAY[${FAILED}]=${base};
    else
        echo "PASSED!"
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