STACK SEGMENT PARA STACK 'stack'
	db 100h DUP(0)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
	buffer DB 5 DUP(5)
	string dw 0
	res dw 001
	qr dw 0
	cons dw 10h
	filename db 'laab4out.txt',0
DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
	ASSUME CS: CODE, DS: DATA, SS: STACK
	extrn toWord:near
	MAIN:
		mov ax, DATA
		mov DS, ax
		
		mov ah, 0ah
		mov dx, offset buffer
		int 21h
		jc wrong
		
		lea bx, buffer
		inc bx
		xor ax, ax
		mov al, byte ptr [bx]
		push ax
		mov cx, ax

		lea ax, buffer
		push ax
		lea ax, res
		push ax
		call toWord
		cmp ax, 1h
		je wrong
		mov ax,res
		
		mov ah, 3ch
		mov cx, 0
		mov dx, offset filename
		int 21h
		jc wrong
		
		mov bx , ax ;handle
		pop di
		call output
		wrong:
		mov ax, 4C00h
		int 21h
		
       output proc
		mov cx,di
		mov ax, res
	toostack:
		cwd
		xor dx,dx
		idiv cons
		push dx
		loop toostack
		
	baitout:
		pop ax
		cmp ax, 0Ah
		jl itsnum
		add ax, 7h
	itsnum:
		add ax, 30h
		mov string,ax
		mov ah, 40h
		mov al,0
		mov cx, 1
		mov dx, offset string
		int 21h
		jc wrong
		dec di
		cmp di, 0
		jne baitout
		
		ret
	output endp
	

CODE ENDS
	END MAIN
