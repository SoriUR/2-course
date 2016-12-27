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
		mov bx, [bp+14]	
		mov al, byte ptr[bx]
		cmp al, '-'
		jne skip
		mov cx, [bp+12]
		cmp cx, 5
		jne skip2
		inc bx
		mov al, byte ptr[bx]
		cmp al, '7'
		jg wrong
skip2:	call nega
		jmp twFinal
skip:	call pos
		mov bx, [bp+10]
		mov [bx], dx
		xor ax, ax
		jmp twFinal
	wrong:
		mov ax, 1
	twFinal:
	mov ax,dx
		pop bp
		pop dx
		pop cx
		pop dx
		ret 6
		toWord endp
pos proc
		mov bx, [bp+14]
		mov cx, [bp+12]
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
		sub al, '1'
		jmp resume
	notChar:
		sub al, '0'
	resume:
		add dx, ax
		inc bx
		loop twLoop
		
		ret
pos endp

nega proc
		inc bx		
		mov cx, [bp+12] 
		dec cx
		xor dx,dx
		xor ax, ax
	twLoop2:
		shl dx, 1
		shl dx, 1
		shl dx, 1
		shl dx, 1
		mov al, byte ptr[bx]
		cmp al, 'A'
		jl num
		sub al, 'F'
		neg al
		jmp rewrite
	num:
		sub al, '?'
		neg al
	rewrite:
		add dx, ax
		inc bx
		loop twLoop2
		inc dx
		ret
nega endp		

CODE ENDS
END
