.model large

.data
	str DB 'kjDf872’;/156AA56d23+ aA38*/-; 54d3 w%323 0212;;*/+12sDd2 dd224;'
	len EQU $-str
	res1 DB 64 DUP(0)
	res2 DB 64 DUP(0)
	mas DQ 0100111010111000110101110101010011101010011101011100011010111010b
	temp1 DB ?
	temp2 DB ?

.code
	mov		AX, @data 
	mov		DS, AX
	mov		ES, AX


	; вывод строки - начало
	lea	DX, str
	lea bx,str
	mov str[bx+64],'$' 
	mov	AH, 9h
	int	21h
	; вывод строки - конец
	
	; переход на новую строку - начало
	mov		DL,  10
	mov		AH,  02h
	int		21h
	; переход на новую строку - конец
	
	; формирование 1 результата - начало
	lea		SI, str
	mov		CX, 64
	mov		BX, 0
	cld

	mov		SP, 0
	mov		DI, 7
	mov		DL, byte ptr mas[DI]
	
	next:
	lodsb

	inc		SP
	cmp		SP, 8
	jle		no8
	dec		DI
	mov		DL, byte ptr mas[DI]
	mov		SP, 1
	no8:
	shl		DL, 1
	jnc		nullmask

	mov		temp1, DL
	mov		temp2, AL
	mov		DL,  49
	mov		AH,  02h
	int		21h
	mov		DL, temp1
	mov		AL, temp2
	
	cmp		AL, 48
	jb		skip
	cmp		AL, 57
	ja		skip

	mov		res1[BX], AL
	inc		BX
	jmp skip

	nullmask:
	mov		temp1, DL
	mov		temp2, AL
	mov		DL,  48
	mov		AH,  02h
	int		21h
	mov		DL, temp1
	mov		AL, temp2

	skip: 
	loop	next
	mov		res1[BX], '$'
	; формирование 1 результата - конец



	; переход на новую строку - начало
	mov		DL,  10
	mov		AH,  02h
	int		21h
	; переход на новую строку - конец



	; вывод 1 результата - начало
	lea		DX, res1
	mov		AH, 9h
	int		21h
	; вывод 1 результата - конец



	; переход на новую строку - начало
	mov		DL,  10
	mov		AH,  02h
	int		21h
	; переход на новую строку - конец



	; формирование 2 результата - начало
	std
	mov		BX, 0
	mov		CX, 64
	lea		SI, str
	add		SI, 63

	next2:
	lodsb
	
	cmp		AL, 32
	je		skip2

	cmp		AL, 65
	jne		write

	lodsb
	cmp		AL, 65
	jne		write1
	jmp		findend

	write1:
	mov		res2[BX], 'A'
	inc BX
	write:
	mov		res2[BX], AL
	inc		BX

	skip2:
	loop	next2
	findend:
	mov		res2[BX], '$'
	; формирование 2 результата - конец



	; вывод 2 результата - начало
	lea	DX, res2
	mov	AH, 9h
	int	21h
	; вывод 2 результата - конец



	mov		AX, 4c00h
	int		21h
end