@ECHO OFF
ECHO Rebuilding Compiler...
ECHO make bin/c_compiler
make bin/c_compiler
SET /A Number = 0
FOR %%A IN (.\test\translator\inputs\*.c) DO SET /A Number += 1
SET /A Count = 0
FOR /L %%A IN (1,1,%NUMBER%) DO (
    ECHO Running Test %%A:
    ECHO Test Output File: test\translator\outputs\%%A.py
    ECHO bin\c_compiler --translate test\translator\inputs\%%A.c -o test\translator\outputs\%%A.py
    bin\c_compiler --translate test\translator\inputs\%%A.c -o test\translator\outputs\%%A.py
    ECHO Comparing output program with reference...
    FC /b test\translator\outputs\%%A.py test\translator\reference\%%A.py > nul
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
ECHO Tests Passed: %Count%/%NUMBER%