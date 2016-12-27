@echo off

if exist utils.o del utils.o
if exist fileMapping.o del fileMapping.o
if exist sort_util.o del sort_util.o
if exist Lab2.dll del Lab2.dll


g++ -c -DLAB2_DLL utils.cpp
g++ -c -DLAB2_DLL fileMapping.cpp
g++ -c -DLAB2_DLL sort_util.cpp
g++ -shared -o Lab2.dll utils.o fileMapping.o sort_util.o

dir Lab2.*

pause