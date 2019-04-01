@ECHO OFF
ECHO Copying input files from a_compiler to b_compiler
ECHO rm -f test\b_compiler\inputs\*
rm -f test\b_compiler\inputs\*
ECHO g++ test\b_compiler\reprint.cpp -o bin\reprint
g++ test\b_compiler\reprint.cpp -o bin\reprint
SET /A Number = 0
FOR %%A IN (.\test\a_compiler\inputs\*.c) DO SET /A Number += 1
FOR /L %%A IN (1,1,%NUMBER%) DO (
    ECHO Copying file %%A of %NUMBER%...
    bin\reprint test\a_compiler\inputs\%%A.c test\b_compiler\inputs\%%A.c
)
ECHO Update complete