@ECHO OFF
ECHO Rebuilding Compiler...
ECHO make bin/c_compiler
make bin/c_compiler
g++ test\a_compiler\comparator.cpp -o bin\comparator
SET /A Number = 0
FOR %%A IN (.\test\a_compiler\inputs\*.c) DO SET /A Number += 1
SET /A Count = 0
FOR /L %%A IN (1,1,%NUMBER%) DO (
    ECHO Running Test %%A:
    ECHO Test Output File: test\a_compiler\outputs\%%A.s
    ECHO Test Return File: test\a_compiler\returns\%%A.txt
    ECHO bin\c_compiler -S test\a_compiler\inputs\%%A.c -o test\a_compiler\outputs\%%A.s
    bin\c_compiler -S test\a_compiler\inputs\%%A.c -o test\a_compiler\outputs\%%A.s
    ECHO java -jar test\Mars4_5.jar nc sm db $v0 test\a_compiler\outputs\%%A.s
    ECHO Simulating compiled program...
    java -jar test\Mars4_5.jar nc sm db $v0 test\a_compiler\outputs\%%A.s > test\a_compiler\returns\%%A.txt
    ECHO Comparing output files...
    bin\comparator test\a_compiler\returns\%%A.txt test\a_compiler\reference\%%A.txt
    IF errorlevel 2 (
        ECHO Reference file not found
    ) ELSE IF errorlevel 1 (
        ECHO Test %%A Failed
    ) ELSE (
        ECHO Test %%A Passed
        SET /A Count += 1
    )
    ECHO.
)
ECHO Tests Passed: %Count%/%Number%