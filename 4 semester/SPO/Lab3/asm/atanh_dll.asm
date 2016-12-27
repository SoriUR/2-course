
    .486                    
    .model flat, stdcall   
    option casemap :none    

    include \masm32\include\windows.inc
    include \masm32\include\user32.inc
    include \masm32\include\kernel32.inc
    include \masm32\macros\macros.asm

    includelib \masm32\lib\user32.lib
    includelib \masm32\lib\kernel32.lib
    ATANH PROTO STDCALL :DWORD,:DWORD


    .data?
      hInstance dd ?

    .code

LibMain proc hInstDLL:DWORD, reason:DWORD, unused:DWORD
    .if reason == DLL_PROCESS_ATTACH
      invoke GetModuleHandle,NULL   
      mov hInstance, eax            
      mov eax, TRUE           
    .elseif reason == DLL_PROCESS_DETACH
    .endif
    ret
LibMain Endp

ATANH proc xArgPtr:dword, resPtr:dword 
		pusha 
		mov eax, xArgPtr 
		mov ebx, resPtr 
		fld1 
		fld1 
		fld1 
		faddp st(1), st(0) 
		fldl2e 
		fmulp st(1), st(0) 
		fdivp st(1), st(0) 

		fld qword ptr [eax] 
		fld st(0) 
		fld1 
		fsubp st(1), st(0) 
		fld1 
		faddp st(2), st(0) 
		fdivp st(1), st(0) 
		fyl2x 

		fstp qword ptr [ebx] 
		popa 
		ret 8 

ATANH endp


end LibMain
