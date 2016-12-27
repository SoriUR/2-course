STACK SEGMENT PARA STACK 'stack'
	db 100h DUP(0)
STACK ENDS

DATA SEGMENT PARA PUBLIC 'data'
	len 	dw 10
	masIn   dw 0,5,2,-2,-3,6,4,-4,-1,-5
	masOut  dw 10h dup(0)
	masReg  dw 7h dup(0)

	min dw 0
	second dw 0
	yk dw 0
	kr dw 0
	sk dw 0
	fg dw 0
	adr dw 0

DATA ENDS

CODE SEGMENT PARA PUBLIC 'code'
	ASSUME CS: CODE, DS: DATA, SS: STACK

START:	mov ax, DATA
		mov DS, ax

		lea bx, masIn
		mov fg, 1
		
		lea bx, masIn
		mov di, bx				;указатель на 1 элемент массива
		
		mov cx, 10
		
		mov ax, [bx]
		mov min, ax				;начальная установка min первым элементом
		
		mov sk, 0
 		mov ax, [bx+2]
		mov second, ax 			;запомнили 2 элемент
								;ставим отрицательные числа вперед
num1:	mov ax, [bx]
		cmp ax, min
		
		jns nnn
		mov min, ax
nnn:	cmp ax, 0
		jns rrr
		inc sk				;счетчик отриц чисел +1
							; меняем местами элементы
		mov dx, [di]
		mov [bx], dx
		mov [di], ax
		add di, 2
rrr:	add bx, 2;
		loop num1
								; поставили
		xor ax,ax 
		add ax, min		
		add ax, second
		mov bx, 2
		cwd
		idiv bx; 
		mov kr,ax				;сохраним криетрий формирования массива-результата	
								;сортируем положительные числа
		mov ax,sk
		sub len, ax
uuu:	mov ax,[di]
		mov min, ax
		
		dec len
		mov ax, len
		mov cx, ax
		mov yk, ax
		
		mov ax, cx
		cmp ax,fg
		js yyy
		mov ax, di
		mov bx, ax
		add bx, 2
		
ggg:    mov ax, [bx]
		cmp ax, min
		jns lll
		mov min, ax
		mov adr,bx
lll:	add bx, 2 	
		loop ggg
		mov bx, adr
		cmp di,bx
		je kkk
									; меняем местами элементы	
		mov ax, [bx]
		mov si, [di]
		mov [bx], si
		mov [di], ax
kkk:	add di, 2
			
		mov ax,yk
		mov cx, ax
		
		loop uuu
								;отсортировали
								;формируем массив-рузельтат
yyy:	mov cx, 10
		xor si,si
		lea bx, masIn
iii:  	mov ax,[bx]
		cmp ax,kr
		js bbb
		mov masOut[si],ax
		add si, 2
bbb:	add bx,2
		loop iii
								;сформиовали
								;функция вывода массива-результата
		lea bx,masIn
		mov di,bx
		xor cx,cx
		add cx,10
		

		
		PRINTNUMBERS: MOV ax, [di] ; начало цикла, в котором мы берем каждый элемент массива (di адрес первого элемента)
;в сx хранится кол-во элементов массива
			 PUSH ax ; сохраняем в стэк
       		 MOV bx, 10 
       		 XOR si, si
       		 AND ax, 8000h ;здесь проверяем на отрицательность(мб попроще можно)
       		 cmp ax, 0
       		 JZ NOTNEGATIVE ; если не отрицательный, то идем нотнегатив
       		 ;if number is negative print minus first
       		 MOV dl, '-'; печатаем минус, если отрицательный
       		 MOV ah, 2 ; эти две строчки нужны для вывода минуса на консоль (2-код операции вывод)
       		 INT 21h ; прерывание дос-а
       		 ;find addition code, находим дополнительный код отрицательного числа
       		 POP ax 
       		 XOR ax, 0FFFFh
       		 ADD ax, 1
       		 JMP EACHDIGIT;переходим к печати
NOTNEGATIVE:  POP ax ; восстанавливаем изначальное значение элемента
       	EACHDIGIT:
       		XOR dx, dx ; в этом цикле мы делим число на 10
       		DIV bx ;вот здесь, остаток в dx, частное в ax
       		ADD dl,'0' ;так мы находим ascii код цифры 
       		PUSH dx ; заносим значения в стэк, чтобы потом напечатать в правильном порядке
       		ADD si,1 ;считаем, сколько у нас цифр в числе
       		cmp ax, 0 ; делаем так до тех пок, пока число не станет нулем
       		JNZ EACHDIGIT
  PRINTEACHNUMBER: ; здесь печатаем цифры числа поочереди
  			POP dx
  			MOV ah, 2
       		INT 21h	
       		SUB si,1
       		CMP si,0 
       		JNZ PRINTEACHNUMBER


       	ADD di, 2 ;устанавливаем адрес следующего элемента
       	MOV dl, ' ' ;печатаем пробел после каждого напечатанного элемента массива
       	MOV ah, 2
       	INT 21h
       	LOOP PRINTNUMBERS ;повторяем все для каждого элемента массива (числа)
									;вывели
		
		mov ax, 4C00h
		int 21h
		
		CODE ENDS
	END START
		