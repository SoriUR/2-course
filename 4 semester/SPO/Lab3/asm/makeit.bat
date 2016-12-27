@echo off

if exist atanh_dll.obj del atanh_dll.obj
if exist atanh_dll.dll del atanh_dll.dll

\masm32\bin\ml /c /coff atanh_dll.asm

\masm32\bin\Link /SUBSYSTEM:WINDOWS /DLL /DEF:atanh_def.def atanh_dll.obj

dir atanh_dll.*

pause