STACK SEGMENT PARA STACK 'stack'
	db 100h DUP(0)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
	string		db "F3F"
	strSize		dw 3
	res 		dw 3333
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
	ASSUME CS: CODE, DS: DATA, SS: STACK
extrn toWord:near

MAIN:
		mov ax, DATA
		mov DS, ax
		
		lea ax, string
		push ax
		lea ax, strSize
		push ax
		lea ax, res
		push ax
		call toWord	
		mov ax, bx		
		mov ax, 4C00h
		int 21h

CODE ENDS
	END MAIN
