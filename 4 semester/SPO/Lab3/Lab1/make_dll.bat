@echo off

if exist Lab1.o del Lab1.o
if exist Lab1.dll del Lab1.dll

g++ -c -DLAB1_DLL Lab1.cpp
g++ -shared -o Lab1.dll Lab1.o

dir Lab1.*

pause