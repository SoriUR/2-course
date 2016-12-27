.386 
.model flat,stdcall 
option casemap:none 
include \masm32\include\windows.inc 
include \masm32\include\user32.inc 
includelib \masm32\lib\user32.lib            ; calls to functions in user32.lib and kernel32.lib 
include \masm32\include\kernel32.inc 
includelib \masm32\lib\kernel32.lib
include \masm32\include\gdi32.inc
includelib \masm32\lib\gdi32.lib
WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
.DATA                     ; initialized data 
ClassName db "SimpleWinClass",0        ; the name of our window class 
AppName db "Lab8",0        ; the name of our window
ContentText db "another text",0
outString db  1000 dup(' '),0
    mass_in db 0FFH, 0FFH, 0FFH, 0FCH, 0AAH, 0FFH, 0DBH, 0BFH, 0FEH, 0CCH, 0FFH, 0FEH, 0EFH, 0FFH, 0DDH, 0FFH, 0F1H, 01FH, 0FFH, 022H, 0FFH, 0F3H, 03FH, 0FFH, 044H , 0FFH, 0F5H, 05FH, 0FFH, 066H, 0FFH, 0F7H, 07FH, 0FFH, 088H, 0FFH, 0F9H, 099H, 09FH, 0AAH
	mass_out db 300 dup(0)
	cap db 20
	cap1 db 28
	org_cap db 8
	temp DD 0
	current DB 0
	count DD 0FFD01H
	str_count dw 0
	car dw ?

.DATA?                ; Uninitialized data 
hInstance HINSTANCE 0        ; Instance handle of our program 
CommandLine LPSTR 0 

.CODE                ; Here begins our code 
start: 
invoke GetModuleHandle, NULL            ; get the instance handle of our program. 
                                                                       ; Under Win32, hmodule==hinstance mov hInstance,eax 
mov hInstance,eax 

invoke WinMain, hInstance,NULL,NULL, SW_SHOWDEFAULT        ; call the main function 
invoke ExitProcess, eax                           ; quit our program. The exit code is returned in eax from WinMain.

WinMain proc hInst:HINSTANCE,hPrevInst:HINSTANCE,CmdLine:LPSTR,CmdShow:DWORD 
    LOCAL wc:WNDCLASSEX                                            ; create local variables on stack 
    LOCAL msg:MSG 
    LOCAL hwnd:HWND

    mov   wc.cbSize,SIZEOF WNDCLASSEX                   ; fill values in members of wc 
    mov   wc.style, CS_HREDRAW or CS_VREDRAW 
    mov   wc.lpfnWndProc, OFFSET WndProc 
    mov   wc.cbClsExtra,NULL 
    mov   wc.cbWndExtra,NULL 
    push  hInstance 
    pop   wc.hInstance 
    mov   wc.hbrBackground,COLOR_WINDOW+1 
    mov   wc.lpszMenuName,NULL 
    mov   wc.lpszClassName,OFFSET ClassName 
    invoke LoadIcon,NULL,IDI_APPLICATION 
    mov   wc.hIcon,eax 
    mov   wc.hIconSm,eax 
    invoke LoadCursor,NULL,IDC_ARROW 
    mov   wc.hCursor,eax 
    invoke RegisterClassEx, addr wc                       ; register our window class 
    invoke CreateWindowEx,NULL,\ 
                ADDR ClassName,\ 
                ADDR AppName,\ 
                WS_OVERLAPPEDWINDOW,\ 
                CW_USEDEFAULT,\ 
                CW_USEDEFAULT,\ 
                390,\ 
                300,\ 
                NULL,\ 
                NULL,\ 
                hInst,\ 
                NULL 
    mov   hwnd,eax 
    invoke ShowWindow, hwnd,CmdShow               ; display our window on desktop 
    invoke UpdateWindow, hwnd                                 ; refresh the client area
    
    
    
    .WHILE TRUE                                                         ; Enter message loop 
                invoke GetMessage, ADDR msg,NULL,0,0 
                .BREAK .IF (!eax) 
                invoke TranslateMessage, ADDR msg 
                invoke DispatchMessage, ADDR msg 
   .ENDW 
    mov     eax,msg.wParam                                            ; return exit code in eax 
    ret 
WinMain endp

;macro
	load_byte MACRO mass, adr
	PUSH BX
	XOR BX, BX
	MOV BL, adr
	MOV DL, mass[BX] ; LOAD BYTE
	POP BX
	ENDM
	
	; WRITE val TO mass
write_byte MACRO mass, adr
	PUSH BX
	XOR BX, BX
	MOV BL, adr
	MOV mass[BX], DL ; WRITE BYTE
	POP BX
	ENDM
	
	my_shl MACRO arg, ct
	LOCAL OFFSET_LEFT, EX
	PUSH CX
	MOV CL, ct
	CMP CL, 0
	JE EX
	OFFSET_LEFT:
		SHL arg, 1
		LOOP OFFSET_LEFT
	EX:
	POP CX
	ENDM
	
	my_shr MACRO arg, ct
	LOCAL OFFSET_RIGHT, EX
	PUSH CX
	MOV CL, ct
	CMP CL, 0
	JE EX
	OFFSET_RIGHT:
		SHR arg, 1
		LOOP OFFSET_RIGHT
	EX:
	POP CX
	ENDM
	
	my_rol MACRO arg, ct
	LOCAL L
	PUSH CX
	MOV CL, ct
	L:
		ROL arg, 1
		LOOP L
	POP CX
	ENDM
	
	my_ror MACRO arg, ct
	LOCAL L
	PUSH CX
	MOV CL, ct
	L:
		ROR arg, 1
		LOOP L
	POP CX
	ENDM
	
	; FILL FIRST LEFT BITS BY 0
	zero_fill_left MACRO arg, ct
	; LEFT OFFSET
	my_shl arg, ct
	; RIGHT OFFSET
	my_shr arg, ct
	ENDM
	
	; FILL FIRST RIGHT BITS BY 0
	zero_fill_right MACRO arg, ct
	; RIGHT OFFSET
	my_shr arg, ct
	; LEFT OFFSET
	my_shl arg, ct
	ENDM
	
	calc_offset MACRO i
	XOR EAX, EAX
	MOV AL, cap
	MUL i
	DIV org_cap ; Now AL - count of origin bytes, AH - offset in original byte
	ENDM
	
	load MACRO mass, i ; load to edx
	LOCAL TRIM_LAST, TRIM_LAST_EXIT, L
	XOR EDX, EDX
	calc_offset i
	load_byte mass, AL
	INC AL
	zero_fill_left DL, AH ; GET ONLY PART OF BYTE
	
	XOR ECX, ECX
	; WE LOADED SOME BITS FROM FIRST BYTE BEFORE
	MOV CL, 8
	SUB CL, AH
	; LOAD BYTES
	L:
		SHL EDX, 8
		load_byte mass, AL
		INC AL
		
		ADD CL, 8
		CMP CL, cap
		JB L
	; WE LOADED FULL LAST BYTE
	; NOW WE NEED TO TRIM IT
	SUB CL, cap ; HOW MUCH BITS WE NEED TO TRIM
	TRIM_LAST:
		DEC CL
		CMP CL, 0
		JL TRIM_LAST_EXIT
		SHR EDX, 1
		JMP TRIM_LAST
	TRIM_LAST_EXIT:
	ENDM
	
	; WRITE EDX TO mass
	write MACRO mass, i
	LOCAL WRITE_NEXT_BYTE, WRITE_NEXT_BYTE_EXIT
	PUSHAD
	PUSH EDX
	PUSH EDX
	calc_offset i
	ADD AH, 12
	POP EDX
	PUSH AX
	my_shr EDX, AH 
	MOV DH, DL
	
	calc_offset i
	load_byte mass, AL
	NEG AH
	ADD AH, 8
	zero_fill_right DL, AH
	XOR CX, CX
	MOV CL, AH 
	
	ADD DL, DH
	calc_offset i
	write_byte mass, AL ; WRITE FIRST BYTE
	
	POP AX 
	INC AL 
	SUB AH, 8
	POP EDX
	my_ror EDX, AH ; DL - SECOND BYTE	
	
		WRITE_NEXT_BYTE:
		ADD CL, 8
		CMP CL, cap
		JA WRITE_NEXT_BYTE_EXIT
		write_byte mass, AL
		ROL EDX, 8
		INC AL
		JMP WRITE_NEXT_BYTE
	WRITE_NEXT_BYTE_EXIT:
	
	SUB CL, 8  ; HOW MUCH BITS WE DIDN'T COPY
	SUB CL, 12
	zero_fill_right DL, CL
	MOV DH, DL
	
	load_byte mass, AL
	NEG CL
	ADD CL, 8
	zero_fill_left DL, CL
	
	ADD DL, DH
	write_byte mass, AL
	

	POPAD
	ENDM
	
	print MACRO val
	LOCAL LP
	PUSHAD
	MOV EAX, val
	XOR ECX, ECX
	MOV CL, 32
	SUB CL, cap
	my_shl EAX, CL
	MOV Cl, cap
	LP:
        SHL EAX, 1
		MOV DL, '0'
		ADC DL, 0
		mov di, str_count
		MOV outString[di], dl
		add str_count, 1
		LOOP LP
	POPAD
	ENDM
	
	print_space MACRO
		PUSHAD
		MOV DL, ' '
		push bx 
		xor bx, bx 
		mov bx, str_count
		MOV outString[bx], dl
		add bl, 1
		mov str_count, bx 
		pop bx
		POPAD
	ENDM
	
	print_nl MACRO
		PUSHAD
		MOV DL, 0AH
		push bx 
		xor bx, bx 
		mov bx, str_count
		MOV outString[bx], dl
		add bl, 1
		mov str_count, bx 
		pop bx
		POPAD
	ENDM
	
    replace MACRO; 10-ls-bits from EAX go to 10-ls-bits of EDX, where 20bits number is stored
        MOV DL, AL
	    AND DH, 0FCh ; FC=11111100 - mask to get rid of 2-lsb
	    SHR AH, 1
	    JNC zero1
	    INC DH
    zero1:
        SHR AH, 1
		JNC zero2
		ADD DH, 2
    zero2:	
    endm


WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	LOCAL ps:PAINTSTRUCT
	LOCAL hdc:HDC
	LOCAL rect:RECT

	    mov str_count, 0
		
	MOV BL, 0
	GLOBAL_FOR:
	    CMP BL, 14 
		JNZ NOT_LAST
		MOV current, BL
		MOV BL, 0
		load mass_in, BL
		MOV temp, EDX
		MOV BL, current
		JMP REPL
		
   NOT_LAST:
	    INC BL
		load mass_in, BL
		MOV temp, EDX
		DEC BL

   REPL:			
		load mass_in, BL
		print EDX
		print_space
		MOV EAX, temp
		replace

		write mass_out, BL
		
		load mass_out, BL
		print EDX
		print_nl
		
		INC BL
		CMP BL, 15
		JB GLOBAL_FOR
	
	EXIT:
		
	

	mov rect.left, 20
	mov rect.top, 0
	mov rect.right, 390
	mov rect.bottom, 300
    .IF uMsg==WM_DESTROY                           ; if the user closes our window 
        invoke PostQuitMessage,NULL             ; quit our application 
    .ELSE 
    ;write text here
    	invoke BeginPaint, hWnd, addr ps
    	mov hdc, eax
    	invoke DrawText, hdc, addr outString, -1, addr rect,DT_LEFT
    	invoke EndPaint, hWnd, addr ps
        invoke DefWindowProc,hWnd,uMsg,wParam,lParam     ; Default message processing 
        ret 
    .ENDIF 
    xor eax,eax 
    ret 
WndProc endp

end start