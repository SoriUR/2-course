.model small
.486
STACK SEGMENT PARA STACK 'stack'
	db 100h DUP(0)
STACK ENDS
DATA SEGMENT PARA PUBLIC 'data'
    KEEP_ES DW 0        ;Буфер для хранения сегмента
    KEEP_IP DW 0        ;и смещения старого прерывания
	time db ?,?,':',?,?,':',?,?,020h,'$'
	dat db ?,?,'.',?,?,'.',?,?,0DH,'$'
	chr db '3','$'
DATA    ENDS
CODE SEGMENT PARA PUBLIC 'code'
	ASSUME CS: CODE, DS: DATA, SS: STACK  
START   PROC    NEAR    
    ;Сохранение адреса старого прерывания
    ;Функция 35 прерывания 21H возвращает текущее
    ;значение вектора прерывания,  помещая значение сегмента в ES,  а
    ;смещение в BX.
    mov AH,35h
    mov AL,08h
    int 21h
    mov KEEP_IP,ES
    mov KEEP_ES,BX
    ;Задание нового обработчика 08h
    ;Для установки написанного прерывания  в  поле  векторов
    ;прерываний  используется  функция 25H прерывания 21H, которая
    ;устанавливает вектор прерывания на указанный адрес.
    push DS
    mov DX,OFFSET Newint
    mov DS,AX
    mov AH,25h     ;функция установки вектора
    mov AL,08h     ;номер вектора
    int 21h           ;меняем прерывание
    pop DS
;------------Тело нового обработчика---------------
Newint  PROC FAR
    PUSHF
    push AX
	
	mov ah, 9;вывожу дату
    mov dx, offset dat
    int 21h
	
    pop AX
    mov AL,20h
    out 20h,AL
    iret
Newint  ENDP
;----Восстанавливаем адрес старого обработчика-----
    CLI
    push DS
    mov DX,KEEP_IP
    mov AX,KEEP_ES
    mov DS,AX
    mov AH,25h
    mov AL,08h
    int 21h           ;восстанавливаем вектор
    pop DS 
    STI
    ret 
START   ENDP
CODE    ENDS        ;Конец сегмента
    END start