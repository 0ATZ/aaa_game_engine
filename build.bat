@echo off

@REM echo Cleaning up the project... 
@REM make clean
@REM if %errorlevel% neq 0 (
@REM     echo Failed to clean the project!
@REM     exit /b
@REM )

echo Building the project... 
make -j4
if %errorlevel% neq 0 (
    echo Failed to build the project!
    exit /b
)

echo running the game... 
main.exe
