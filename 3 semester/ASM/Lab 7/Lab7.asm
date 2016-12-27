.386					
.model flat, stdcall	
option casemap: none	

include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\masm32.inc
include c:\masm32\macros\macros.asm
includelib c:\masm32\lib\kernel32.lib
includelib c:\masm32\lib\masm32.lib
include c:\masm32\include\msvcrt.inc
includelib c:\masm32\lib\msvcrt.lib

.stack 100h

.data
	startMessage db "System Programming Languages, Lab 7.", 13, 10, 0
	funcMessage db "My func is:  arcth(x)", 13, 10, 0
	tableMessage db 13, 10, 10, "Resulted table: ", 13, 10, " |(x)", 9, " | my result", 9, " | c result", 9, " |series length", 9, " |", 13 , 10, 0
	getXmessage db "Input first x: ", 0			
	getDXmessage db "Input delta x: ", 0		
	getFXMessage db "Input last x: ", 0							
	getPrecisionMessage db "Input Precision: ", 0
	

	inFormat db "%lf", 0
	outFormat db "%d", 0
	
	
	endl db 10, 8, 0
	tab db 9, 0
	wall db ' ', '|', ' ', 0
.data?
	x1 dq ?
	deltaX dq ?
	x2 dq ?
	a dq ?
	prec dq ?
	
	strBuffer db 20 dup(?)
	rangeLength dd ?
	
.code
RowSum proc xPtr:dword, precPtr:dword	
	local i:word
	pusha
	mov i, 0	
	lea edx,i
	
	mov ecx, precPtr ;адрес погрешности
	mov eax, xPtr	;сам аргумент
	mov rangeLength, 0
	
	fldz				; st(2) = 0. 		для суммы
	fld qword ptr [ecx] ; st(1) = prec		погрешность

nextIter:	
	fld1; st(0)=1
	fld qword ptr [eax] ; st(0) = x ;
	
pow:		;2n+1
	xor ecx, ecx
	mov cx, i
	add cx, i
	add cx, 1
	
powLoop:
	fmul st(1), st(0)	; st(1) *= x
	loop powLoop
	faddp st(0), st(0) ; st(0)=x^(2n+1)
	fild word ptr ss:[edx]
	fild word ptr ss:[edx]
	faddp st(1),st(0)
	fld1
	faddp st(1), st(0)
	
	fdivp st(1), st(0)	;st(0)= x^(2n+1)/(2n+1)
	
postIter:
	fadd st(2), st(0)	; добавим к сумме элемент
	fabs
	inc i
	
	; если  модуль элемента меньше погрешности
	push eax
	fcomp st(1)	
	fstsw ax
	fwait
	sahf
	pop eax
	ja nextIter
	
	xor ecx, ecx
	mov cx, i
	mov rangeLength, ecx
	faddp st(0), st(0)
	
	popa
	ret 8
RowSum endp

AddDouble proc doublePtr:dword, additionPtr:dword
	pusha
	
	mov eax, doublePtr
	mov ebx, additionPtr
	
	fld qword ptr [ebx]	; s(1) = addition
	fld qword ptr [eax]	; s(0) = doublePtr
	fadd st(0), st(1)
	
	fstp qword ptr [eax]
	faddp st(0), st(0)
	
	popa
	ret 4
AddDouble endp

arcth proc xArgPtr:dword, resPtr:dword 
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
arcth endp

work proc x:qword
	local xBuffer:qword	
	pusha
	
	; запишем х в буфер
	mov eax, dword ptr[x]
	mov dword ptr xBuffer, eax
	mov eax, dword ptr[x+4]
	mov dword ptr xBuffer+4, eax
	
	;печатаем х
	invoke FloatToStr, xBuffer, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	
	; печатаем мой результат
	invoke RowSum, addr xBuffer, offset prec
	lea eax, x
	fstp qword ptr [eax]
	invoke FloatToStr, x, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
		

	
	; печатаем табличный
	invoke arcth, addr xBuffer,addr xBuffer
	invoke FloatToStr, ss:xBuffer, offset strBuffer
	print addr wall
	print addr strBuffer
	print addr tab
	
	; печатаем кол-во слагаемых
	print addr wall
	invoke crt_printf, addr outFormat, rangeLength
	print addr tab
	print addr tab
	print addr wall
	print addr endl
	
	popa
	ret 6
work endp

getUserData proc
	pusha
	
	print addr startMessage
    print addr funcMessage
	
	print addr getXmessage
	invoke crt_scanf, addr inFormat, addr x1
	
	print addr getDXmessage
	invoke crt_scanf, addr inFormat, addr deltaX
	
	print addr getFXMessage
	invoke crt_scanf, addr inFormat, addr x2
	
	print addr getPrecisionMessage
	invoke crt_scanf, addr inFormat, addr prec
	
	print addr tableMessage

	popa
	ret
getUserData endp

start:
	finit
	call getUserData
	
continueWork:
	invoke work, x1
	invoke AddDouble, offset x1, offset deltaX
	
	 ;cmp x1, x2
	 push ax
	 fld x1
	 fcomp x2
	 fstsw ax
	 fwait
	 sahf
	 pop ax
	 jb continueWork
	
    invoke ExitProcess, NULL
end start
