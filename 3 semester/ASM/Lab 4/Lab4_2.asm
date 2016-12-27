CODE SEGMENT PARA PUBLIC 'code'
	ASSUME CS: CODE
;BX - Адрес начала строки
;CX - Размер строки
;DX - Результат
;AX - Флаг результата
public toWord	
	toWord proc
		push bx
		push cx
		push dx
		push bp
		
		mov bp, sp
		mov bx, [bp+12]
		add bx, 2
		mov al, byte ptr[bx]
		cmp al, '-'
		jne more0
		mov cx, [bp+14]
		cmp cx, 5
		jne less0
		inc bx
		mov al, byte ptr[bx]
		cmp al, '7'
		jg wrong
	less0:
		dec cx
		mov [bp+14], cx
		mov bx, [bp+12]
		add bx, 3
		call pos
		neg dx
		jmp reswrite
	more0:	
		mov cx, [bp+14]
		cmp cx, 4
		jg wrong
		call pos
	reswrite:
		mov bx, [bp+10]
		mov [bx], dx
		xor ax, ax
		jmp twFinal
	wrong:
		mov ax, 1h
	twFinal:
		pop bp
		pop dx
		pop cx
		pop dx
		ret 4
		toWord endp
pos proc
		xor dx, dx
		xor ax, ax
	twLoop:
		shl dx, 1
		shl dx, 1
		shl dx, 1
		shl dx, 1
		mov al, byte ptr[bx]
		cmp al, 'A'
		jl notChar
		sub al, 37h
		
		jmp resume
	notChar:
		sub al, '0'
	resume:
		add dx, ax
		inc bx
		loop twLoop
		ret
pos endp

CODE ENDS
END