@echo off

echo(

nasm vfork.asm -o vfork.o -f win32
if %errorlevel% neq 0 (
    echo Blad kompilacji pliku ASM
    exit /b 1
)

gcc vfork.o -o vfork.exe -m32
if %errorlevel% neq 0 (
    echo Blad linkowania
    exit /b 1
)

echo Program napisany w assemblerze:
vfork.exe

echo(

gcc vfork.c -o vfork.exe
if %errorlevel% neq 0 (
    echo Blad kompilacji pliku C
    exit /b 1
)

echo Program napisany w C:
vfork.exe

echo(
pause
