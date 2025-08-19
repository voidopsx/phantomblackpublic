@echo off
setlocal ENABLEDELAYEDEXPANSION

echo [*] PhantomBlack Build System
echo ------------------------------

REM Output directory
set OUTDIR=bin
if not exist %OUTDIR% (
    mkdir %OUTDIR%
)

REM Check for MSVC cl.exe
where cl >nul 2>&1
if %ERRORLEVEL%==0 (
    echo [*] MSVC detected. Compiling with cl.exe...
    cl src\PhantomBlack.cpp /nologo /O2 /std:c++17 /Fe:%OUTDIR%\PhantomBlack.exe
    goto :done
)

REM Check for MinGW g++
where g++ >nul 2>&1
if %ERRORLEVEL%==0 (
    echo [*] MinGW detected. Compiling with g++...
    g++ src\PhantomBlack.cpp -o %OUTDIR%\PhantomBlack.exe -std=c++17 -static -s -lntdll
    goto :done
)

echo [!] ERROR: No supported compiler found (cl.exe or g++)
goto :eof

:done
echo [✓] Build complete. Output: %OUTDIR%\PhantomBlack.exe
