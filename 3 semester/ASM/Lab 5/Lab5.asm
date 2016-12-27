.model small
.486
.stack 100h

.data
	mass dw 20 dup (1123h)
	arrSize equ 16
	strLen	equ 160
	columnWidth	equ 28
	tStart	equ 160*3+20
	n db 20
	buff	db 10 dup(0)
	bufSize db 0
	const db 8
	videoAdr	equ 0B800h

read macro index,arr_offset,Bit
local nullshiftt, moreshift,skipAnd
	push ax
	push bx
	push dx
	push cx
	xor esi,esi
	mov ax, index
	mov bx, arr_offset
	mul Bit
	cwd
	idiv const
	mov dl, ah ;смещение в байте
	mov ah, 0
	mov bx,ax;aдресс байта
	mov cl,[bx]


	cmp dx,4
	jne nullshiftt
	and cx,0fh
	nullshiftt:
	add si,cx
	inc bx
	mov cl,[bx]
	
	cmp dx,0
	jne moreshift
	shl cx,4
	moreshift:
	shl cx,4
	add si,cx
	xor cx,cx
	inc bx
	mov cl,[bx]
	
	cmp dx,0
	jne skipAnd
	and cx,0F0h
	skipAnd:
	shl ecx,12
	add esi,ecx
	
	pop cx
	pop dx
	pop bx
	pop ax
endm

write macro index, arr_offset, Bit, number
local nullShift, exit
		push ax
		push bx
		push di
		push si
		push dx
		push cx
		
		mov ax, index
		mov bx, arr_offset
		mov ecx, number
		mul Bit
		cwd
		idiv const
		mov dl, ah ;смещение в байте
		mov ah, 0
		mov bx,ax;aдресс байта
		
		cmp dx, 4
		jne nullShift
		mov dl, [bx]
		and dx, 0f0h
		mov si,cx
		and cl, 0fh
		add dl,cl
		mov cx,si
		mov [bx],dl
		inc bx
		shr ecx, 4
		mov [bx],cl
		inc bx
		shr cx,8
		mov [bx],cl
		jmp exit
		nullShift:
		mov [bx], cl
		shr ecx, 8
		inc bx
		mov [bx], cl
		shr cx, 4
		inc bx
		and cx, 0f0h
		mov dl, [bx]
		and dx, 0Fh
		add cl,dl
		mov [bx], cl
		exit:
		
		pop cx
		pop dx
		pop si
		pop di
		pop bx
		pop ax
endm

swap macro arr_offset
local firstbait,exit
		pusha
		xor cx,cx
		read cx,offset mass, n
		jmp firstbait
		for1:
		inc cx
		read cx,arr_offset,n
		push esi
		and esi, 0FFC00h
		add si,ax
		write cx,arr_offset,n,esi
		pop esi
		firstbait:
		and esi,03FFh
		mov ax,si
		cmp cx, 15
		je exit
		jmp for1
		exit:
		xor cx,cx
		read cx,arr_offset,n
		and esi, 0FFC00h
		add si,ax
		write cx,arr_offset,n,esi
		popa
endm
;------------------------------------------------------------------------
printSmth macro sym, count, incr
	local for
	mov cx, count
	mov al, sym
 for:
	mov es:[di], ax
	add di, incr	
	loop for
endm

printArray macro offset_ar, number
local cycle, printWord
	pusha
	mov ecx, 0
	mov di, tStart+strLen+4+number*58;смещение 
cycle:
    push cx
	xor eax, eax
	read cx, offset_ar, n ;результат в esi
    call convertWord
	xor ebx, ebx
	mov bl, bufSize;количество цифр в числе
	mov si, bx
printWord:
	xor eax, eax 
	dec si
	mov ah, 12h
	printSmth buff[si], 1, 2 ;askii код в al
	cmp si, 0
jne printWord
	shl bx, 1
	sub bx, strLen
	sub di, bx
	pop cx
	inc cx
	cmp cx, 15
jle cycle
	popa
endm
;_________________________________________________________________________________________________________________
.code
	MAIN:
		mov ax, DATA
		mov DS, ax
		call paintBackground
		call paintBorders
		printArray	offset mass, 0
	;	lea ax, mass
	;	mov edi, 12345h ; число для записи
	;	write writeI,ax,n,edi	
	;	lea ax, mass
	;	read readI, ax, n; результат в esi
		lea ax, mass
		swap ax
		
		printArray offset mass, 1
		
		mov ax, 4C00h
		int 21h
	;_________________________________________________________________________________________________________________	
		newLine proc
		pusha
		mov dl, 0Ah
		mov ah, 02h
		int 21h
		mov dl, 0dh
		mov ah, 02h
		int 21h
		popa
		ret
	newLine endp
	
	paintBorders proc
		pusha
		mov ax, videoAdr ;video-memory address
		mov es, ax

		mov ah, 1Bh ;colors
		mov di, tStart 	
		
		;top border
		printSmth 0C9h, 1, 2
		printSmth 0CDh, columnWidth, 2
		printSmth 0CBh, 1, 2
		printSmth 0CDh, columnWidth, 2
		printSmth 0BBh, 1, 2

		;bottom border		
		mov di, tStart 
		add di, strLen*(arrSize+1)	

		printSmth 0C8h, 1, 2
		printSmth 0CDh, columnWidth, 2
		printSmth 0CAh, 1, 2
		printSmth 0CDh, columnWidth, 2
		printSmth 0BCh, 1, 2

		;left vertical
		mov di, tStart 
		add di, strLen	
		printSmth 0BAh, arrSize, strLen
		
		;middle vertical
		mov di, tStart 
		add di, 160+(columnWidth+1)*2	
		printSmth 0BAh, arrSize, strLen

		;left vertical
		mov di, tStart 
		add di, strLen+(columnWidth+1)*4	
		printSmth 0BAh, arrSize, strLen

		popa
		ret
	paintBorders endp
	
		convertWord proc
		pusha
		mov bufSize, 0
		xor  dx, dx
		lea  di, buff
		mov cx,5
		bt esi, 20
		jnc  beginConvert
		and esi,07FFFFh
		mov  dl, '-'
		mov  [di], dl
		inc  di
		inc bufSize

	 beginConvert:
		mov dx,si
		and dx,0fh
		cmp dl, 10
		jl number
		add dl, 7
		number:
		add dl, 48
		mov [di], dl
		inc di
		inc bufSize
		shr esi, 4
		loop beginConvert

		popa
		ret
	convertWord endp
	
	paintBackground proc 
		push es
		push ax
		mov ax, 0b800h ;; видео-страница
		mov es, ax
		pop ax
		mov di, 0
		mov cx, 2000 ; 80x25
		mov ah, 10h ; синий фон
		mov al, 20H ; пробел
	 paintLoop:	
		mov es:[di], ax
		add di, 2
		loop paintLoop
		pop es
		ret
	paintBackground endp
	

CODE ENDS
	END MAIN