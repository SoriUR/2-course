.model small
.486
STACK SEGMENT PARA STACK 'stack'
	db 100h DUP(0)
STACK ENDS
DATA SEGMENT PARA PUBLIC 'data'
    KEEP_ES DW 0        ;����� ��� �������� ��������
    KEEP_IP DW 0        ;� �������� ������� ����������
	time db ?,?,':',?,?,':',?,?,020h,'$'
	dat db ?,?,'.',?,?,'.',?,?,0DH,'$'
	chr db '3','$'
DATA    ENDS
CODE SEGMENT PARA PUBLIC 'code'
	ASSUME CS: CODE, DS: DATA, SS: STACK  
START   PROC    NEAR    
    ;���������� ������ ������� ����������
    ;������� 35 ���������� 21H ���������� �������
    ;�������� ������� ����������,  ������� �������� �������� � ES,  �
    ;�������� � BX.
    mov AH,35h
    mov AL,08h
    int 21h
    mov KEEP_IP,ES
    mov KEEP_ES,BX
    ;������� ������ ����������� 08h
    ;��� ��������� ����������� ����������  �  ����  ��������
    ;����������  ������������  ������� 25H ���������� 21H, �������
    ;������������� ������ ���������� �� ��������� �����.
    push DS
    mov DX,OFFSET Newint
    mov DS,AX
    mov AH,25h     ;������� ��������� �������
    mov AL,08h     ;����� �������
    int 21h           ;������ ����������
    pop DS
;------------���� ������ �����������---------------
Newint  PROC FAR
    PUSHF
    push AX
	
	mov ah, 9;������ ����
    mov dx, offset dat
    int 21h
	
    pop AX
    mov AL,20h
    out 20h,AL
    iret
Newint  ENDP
;----��������������� ����� ������� �����������-----
    CLI
    push DS
    mov DX,KEEP_IP
    mov AX,KEEP_ES
    mov DS,AX
    mov AH,25h
    mov AL,08h
    int 21h           ;��������������� ������
    pop DS 
    STI
    ret 
START   ENDP
CODE    ENDS        ;����� ��������
    END start