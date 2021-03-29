.model tiny
.code
org 100h

;=======================================================================================
; Start module
;=======================================================================================
Start:
	Call Welcome
	Call Scan
	Call Compare
	cmp ax, 1
	je Correct_Password
	jmp Incorrect_Password
;=======================================================================================

;=======================================================================================
; Write some greetings before writing password
;=======================================================================================
Welcome	proc	
	lea ds:dx, Greeting
	mov ah, 09h
	int 21h
	lea ds:dx, FieldForPassword
	int 21h
	ret
	endp
;=======================================================================================

;=======================================================================================
; Scanning password from the terminal
;=======================================================================================
Scan	proc
	lea bx, Input
	mov ah, 01h
rep_Scan:
	int 21h		
	cmp al, 13d
	je end_Scan
	mov [bx], al
	inc bx
	inc cx
	jmp rep_Scan
end_Scan:	
	ret
	endp
;=======================================================================================
	
;=======================================================================================
; Comparing giving password and right password
;=======================================================================================
Compare	proc
	mov  si, offset Input
	mov  di, offset Password
	dec si
	dec di
	mov cx, 2d
rep_com:
	inc si
	inc di
	mov bx, [si]
	mov si, bx
	mov bx, [di]
	mov di, bx
	cmp si, di 
	jne N_Eq
	loop rep_com
	
	mov ax, 1	;1 - means password is correct
	ret
 N_eq:
	mov ax, 0
	ret		;0 - means password is incoorect
	endp
;=======================================================================================

;=======================================================================================
; Case that user write correct answer
;=======================================================================================
Correct_Password:
	mov ah, 09h
	lea ds:dx, R_password  
	int 21h
	jmp Ex
;=======================================================================================

;=======================================================================================
; Case that user write incorrect answer
;=======================================================================================
Incorrect_Password:
	mov ah, 09h
	lea ds:dx, W_password
	int 21h
	jmp Ex		
;=======================================================================================

;=======================================================================================
; Exit from programm
;=======================================================================================
Ex:
	mov ax, 4c00h
	int 21h
;=======================================================================================


Input:   		db 17 dup (?)
Greeting:		db 'Welcome to Mossad!', 13, 10,  'Please enter passsword!', 13, 10, '$'
FieldForPassword: 	db 'Password:', '$'
Password: 		db 'MY'
R_password: 		db 'Congratulaions, you have wasted your time!)))', '$'
W_password: 		db 'Sorry, you are looser :(', '$'
end	Start