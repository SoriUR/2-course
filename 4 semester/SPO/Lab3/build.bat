@echo off

if exist main.o del main.o
if exist main.exe del main.exe
if not exist Lab1.dll (
	if exist Lab1\Lab1.dll (
		copy Lab1\Lab1.dll Lab1.dll
	) else (
		echo Lab1.dll does not exist
		pause
		break
	)
)

if not exist Lab2.dll (
	if exist Lab2\Lab2.dll (
		copy Lab2\Lab2.dll Lab2.dll
	) else (
		echo Lab2.dll does not exist
		pause
		break
	)
)

if not exist atanh_dll.dll (
	if exist asm\atanh_dll.dll (
		copy asm\atanh_dll.dll atanh_dll.dll
	) else (
		echo atanh_dll.dll does not exist
		pause
		break
	)
)
g++ -c main.cpp
g++ -o main.exe main.o -L. -lLab1 -lLab2