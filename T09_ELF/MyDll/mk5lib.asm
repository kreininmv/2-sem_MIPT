.686
.model flat, stdcall
option casemap: none

include C:\masm32\include\user32.inc
include C:\masm32\include\kernel32.inc

includelib C:\masm32\lib\kernel32.lib
includelib C:\masm32\lib\user32.lib

STD_OUTPUT_HANDLE	equ -11d
STD_INPUT_HANDLE 	equ -10d

GetStdHandle    	proto :dword
WriteConsoleA   	proto :dword, :dword, :dword, :dword, :dword
ReadConsoleA	        proto :dword, :dword, :dword, :dword, :dword
ExitProcess     	proto :dword

WriteSym		proto :byte
ToDec			proto :dword
mk5scanf		proto 

.data 
string			dd 255 DUP(?)
handle			dd 0
symbol			db 0 
len			db ?

.code
;=======================================================================
;	Entry point for my library
;=======================================================================
LibMain proc parameter1:DWORD, parameter2:DWORD, parameter3:DWORD

	mov eax, 1
	ret

LibMain endp
;=======================================================================

;=======================================================================
;        Procedur for writing symbol to console macro
;        Arguments: - sym - symbol to write         
;=======================================================================
WriteSym        proc, sym: byte
                nop
                push eax
                push ebx
                push ecx
                push edx

                invoke GetStdHandle, STD_OUTPUT_HANDLE

                xor edx, edx
                mov dl, sym
                
                mov byte ptr symbol, dl  

                invoke WriteConsoleA, eax, offset symbol, 1, 0, 0

                pop edx
                pop ecx
                pop ebx
                pop eax

                nop
                ret 
WriteSym        endp               
;=======================================================================

;=======================================================================
;               Define for ToDec function
;=======================================================================
DivTen          macro exit_label, next_label
                nop

                push edx
                xor edx, edx                
                mov eax, ebx            ; eax = ebx
                mov ebx, 10d            ; ebx = 10
                div ebx                 ; eax = eax / ebx

                cmp eax, 0
                je exit_label               
                                        ; edx = eax % ebx
                xchg eax, ebx           ; Swap(eax, ebx)
                pop eax

                jmp next_label

                nop
                endm
;=======================================================================

;=======================================================================
;       Convert number from decimal to string and writing it into console
;	That is my small version of printf in standart library
;       Arguments:                - num - number to convert 
;=======================================================================
ToDec           proc num: dword
                push eax
                push edx
                push ebx

                mov ebx, 1000000000d    ; ebx = 10e9
                push num
Next_prep:
                xor edx, edx            ; edx = 0
                mov eax, num            ; eax = num
                div ebx

                cmp eax, 0
                jne Convert

                DivTen Zero, Next_prep

Convert:        
                pop eax
                xor edx, edx
                
Next:           div ebx                 ; eax = eax / ebx
                                        ; edx = eax % ebx
                add al, '0'             ; al = '0'
                invoke WriteSym, al     ; putchar(al)

                DivTen Fnc_end, Next

Zero:           invoke WriteSym, '0'



Fnc_end:        
		xor eax, eax
		mov eax, 10d
          	invoke WriteSym, al
		pop ebx
                pop edx
                pop eax
                ret
ToDec           endp
;=======================================================================

;=======================================================================
;	Convert string to decimal number
;       Arguments:
;       	- ecx - len of string
;		- esi - adress of string
;	Output:		- eax - number that was converted
;=======================================================================
string_to_dec 	proc 
                add esi, ecx	; перемещаемся в конец строки		
		dec esi         ; esi = esi - 1 ; ptr--
		mov ebx, 1      ; ebx = 1
		xor eax, eax    ; eax = 0
		xor edi, edi    ; edi = 0
		std

circle:
		lodsb           ; al = [esi]
		sub al, 30h     ; al = al - '0' - чтобы привести из таблицы аски к числу
		mul ebx		; eax = eax * ebx
		add edi, eax    ; edi = edi + eax
		dec ecx		; ecx--
	
		jz ending       ; if (al < 0) тогда прыгает
       		
		mov eax, 0Ah    ; eax = 10 
		mul ebx		; eax = ebx * 10
		mov ebx, eax	; ebx = 10
		xor eax, eax	
		jmp circle

ending:
		mov eax, edi 	; eax = edi
		ret

string_to_dec	endp
;=======================================================================

;=======================================================================
;	Read string from console and covert it to the number 
;	That is my small version of scanf for decimal numbers
;=======================================================================
mk5scanf 	proc
		push esi
		push edi
		push ecx
                push edx
                push ebx

       		invoke GetStdHandle, STD_INPUT_HANDLE

;		invoke WriteConsoleA, eax, offset symbol, 1, 0, 0
		mov handle, eax

		invoke ReadConsoleA, EAX, offset string, 0Ch, offset len, 0

		mov     esi, offset string 	    	; esi = string
		mov     ecx, offset len			; ecx = len
		mov     ecx, [ecx]                      ; ecx = [ecx]           	
		sub     ecx, 2				; ecx = ecx - 2

		call 	string_to_dec			; call converter from string to decimale

Fnc_end:        pop ebx
                pop edx
		pop ecx
		pop edi
		pop esi

		ret

mk5scanf endp

end LibMain
