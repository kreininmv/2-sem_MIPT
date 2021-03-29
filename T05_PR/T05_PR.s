;/*  My version of print in C++.
; *  Entry:
; *      rdi, rsi, rdx, rcx, r8, r9 - arguments of printf() 
; *  Destroy list:
; *      r14 r15 r12 r10 r9 r8 rax cx rdx rsi rdi rbp 
; */
 global _printik
 section .text
 _printik:

  pop r14                 ; Save adress of returning
  mov r15, rbp            ; Save default base pointer

  push r9                 ; Push arguments from registers to stack
  push r8
  push rcx        
  push rdx
  push rsi
  push rdi
  mov rbp, rsp            ; Assign to point of start stack adress of top of stack

  mov r10, rdi            ; rdi - adress of string
  mov r12, 8              ; for moving to the next element in stack

  while:
  mov rax, '%'
  call strchr             ; find '%' in string

  cmp r10, 0              ; if there is no more '%' specificators, writing 
  je only_string

checking_sym:
  
  mov r9, r10             ; write all symbols before first '%'
  sub r9, rdi             ; len of str

  push rdi                ; saving parametres
  push rsi                ;
  mov rax, 1              ; mod of writing
  mov rsi, rdi            ; rsi - adress of string
  mov rdi, 1              ; rdi 
  mov rdx, r9             ; counter - len of str
  syscall                 ; write symbols string!!!
  pop rsi                 ; get parametres back to the registers
  pop rdi                 ;

  inc r10                 ; searching for symbol after '%'

  mov rbx, [r10]          ; push current symbol to rbx
  
  and rbx, 0xff

  mov rax, [8 * (rbx - '%') + table]
  jmp rax

  ;mov al, 'c'
  ;cmp al, bl
  ;je print_char           ; call print char

  ;mov al, 's'
  ;cmp al, bl
  ;je print_string         ; call print string
  
  ;mov al, 'd'
  ;cmp al, bl
  ;je print_decimal        ; call print decimal

  ;mov al, 'b'
  ;cmp al, bl
  ;je print_binary         ; call print binary

  ;mov al, 'h'
  ;cmp al, bl
  ;je print_hex            ; call print hex

  ;mov al, '%'             ; call print percent  
  ;cmp al, bl
  ;je print_percent   
;/************************************************************************/


;/************************************************************************/
;/* Print percent
; * Destroy list:
; *      rax rsi rdi r9 r10
; */
;/************************************************************************/
case_per:
print_percent:
  mov rax, '%'
  mov r9, buf
  mov [r9], rax
  mov rax, 1
  mov rsi, buf
  mov rdi, 1
  mov rdx, 1
  syscall

  inc r10
  mov rdi, r10

  jmp while
;/************************************************************************/


;/************************************************************************/
;/* Convert number to string in hexadecimal 
; * Destroy list:
; *      rax rbx rcx rsi rdi rdx r12 r10 r9
; */
;/************************************************************************/
case_hex:
print_hex:
  xor rcx, rcx
  mov rax, [rbp + r12]
  add r12, 8

repeat_hex:
  mov rbx, 16
  xor rdx, rdx
  div rbx
  cmp rax, rdx
  je checking_hex
  back_hex:
  add rdx, str_hex

  mov r9, buf
  add r9, rcx
  mov rbx, [rdx]
  mov [r9], bl
  inc rcx
  jmp repeat_hex

  checking_hex:
  cmp rax, 0
  jne back_hex

  end_hex:

  repeat_2_hex:
  mov rax, 1
  mov rsi, buf
  add rsi, rcx
  dec rsi
  mov rdi, 1
  mov rdx, 1
  push rcx
  syscall
  pop rcx
  dec rcx
  cmp rcx, 0
  jne repeat_2_hex

  inc r10
  mov rdi, r10

  jmp while
;/************************************************************************/


;/************************************************************************/
;/* Convert number to string in binary
; * Destroy list:
; *    rax rbx rcx rsi rdi rdx r12 r11 r10 r9
; */
;/************************************************************************/
case_bin:
print_binary:  
  xor rcx, rcx
  mov rax, [rbp + r12]
  add r12, 8

  rep_bin:        ;converting digit to hexadecimal look
  mov rdx, rax    ; 
  shr rax, 1      ; rax = rax / 2
  and rdx, 0x1    ; rdx = rax % 2

  cmp rax, rdx
  je check_bin
  back_bin:
  add rdx, str_hex

  mov r9, buf
  add r9, rcx
  mov rbx, [rdx]
  mov [r9], bl
  inc rcx
  jmp rep_bin

  check_bin:
  cmp rax, 0
  jne back_bin

  end_bin:

  rep_2_bin:      ;printing to standart output
  mov rax, 1
  mov rsi, buf
  add rsi, rcx
  dec rsi
  mov rdi, 1
  mov rdx, 1
  push rcx
  syscall
  pop rcx
  dec rcx
  cmp rcx, 0
  jne rep_2_bin

  inc r10
  mov rdi, r10

  jmp while
;/************************************************************************/


;/************************************************************************/
;/* Print converting numver to string in decimal
; * Destroy list:
; *    rax rbx rcx rsi rdi rdx r12 r10
; */ 
;/************************************************************************/
case_dec:
print_decimal:
  xor rcx, rcx            ; rcx = 0
  mov rax, [rbp + r12]    ; adress of number in stack 
  add r12, 8              ; increase of stakc

  mov rbx, 10             ;

repeat_decimal:
  xor rdx, rdx            ; rdx = 0
  div rbx                 ; rax = rax / rbx
  cmp rax, rdx            ; rax == 0
  je check_decimal        ; go to 

  back_decimal:
  add rdx, '0'            ; add ASCII symbol

  mov r9, buf             ; r9 = buf
  add r9, rcx             ; r9 = buf + rcx
  mov [r9], rdx           ; [r9] = rdx (num)
  inc rcx                 ; rcx++
  jmp repeat_decimal      

  check_decimal:
  cmp rax, 0              ;
  jne back_decimal        ; print number

  end_decimal:

  repeat_2_decimal: 
  mov rax, 1              ; mode of syscall for writing
  mov rsi, buf            ; rsi = buf - adress for writing
  add rsi, rcx            ; rsi = buf + rcx 
  dec rsi                 ; rsi--
  mov rdi, 1              ; rdi = 1 - stdout
  mov rdx, 1              ; rdx = 1 - size of bytes for writing
  push rcx                ; save rcx
  syscall                 ; write
  pop rcx                 ; getback rcx
  dec rcx                 ; rcx--
  cmp rcx, 0              ; end of num?
  jne repeat_2_decimal    ; continue

  inc r10                 ; r10++
  mov rdi, r10            ; rdi = r10

  jmp while
;/************************************************************************/


;/************************************************************************/
;/* Print converting number to string
; * Destroy list:
; *    rax rbx rsi rdi rdx r12 r10
; */ 
;/************************************************************************/
case_str:
print_string:
  mov rsi, [rbp + r12]
  add r12, 8
  mov rax, 1
  mov rdi, 1
  mov rdx, 1

repeat_string:
  syscall
  inc rsi
  mov rbx, [rsi]
  cmp bl, 0
  jne repeat_string

  inc r10
  mov rdi, r10

  jmp while
;/************************************************************************/


;/************************************************************************/
;/* Print number like a letter (%c)
; * Destroy list:
; *        rax rbx rsi rdi rdx r12 r10 r9
; */
;/************************************************************************/
case_ch:
print_char:
  mov rax, [rbp + r12]
  add r12, 8
  mov r9, buf
  mov [r9], rax
  mov rax, 1
  mov rsi, buf
  mov rdi, 1
  mov rdx, 1
  syscall 

  inc r10
  mov rdi, r10

  jmp while           ; return to the cicle
;/************************************************************************/


;/************************************************************************/
;/* Printing symbols without '%'
; * Destroy list:
; *        rax, rsi, rdi, rdx
; */
;/************************************************************************/
only_string:
  mov rax, 1                  ; mod of writing
  mov rsi, rdi                ; adress of string
  mov rdi, 1                  ; 
  mov rdx, 1                  ;

repeat_only_string:
  syscall
  inc rsi                     ; going to the next symbol

  cmp byte [rsi], 0           ; write while cur_sym != 0
  jne repeat_only_string      

  jmp exit                

;/************************************************************************/


;/************************************************************************/
;/* Find first letter in string. (Custom verison of strchr())
; * Entry:
; *        rax - symbol
; *        r10 - adress of string
; * Returns:
; *        If find symbol:         
; *          r10 - adress of symbol
; *        If doesn't find symbol: 
; *          r10 = 0
; */
;/************************************************************************/
global strchr
strchr:
  repeat:
  mov bl, [r10] 
  cmp bl, al
  je found

  cmp bl, 0
  je not_found

  inc r10
  jmp repeat
  
  found: ret

  not_found:
  xor r10, r10
  ret
;/************************************************************************/

case_default:
jmp while

;/************************************************************************/
;/* Exit from _printik
; * Entry: 
; *  r14 - returning adress
; *  r15 - default rpb
; */
;/************************************************************************/
exit:
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  pop rax
  mov rbp, r15
  push r14

  ret
;/************************************************************************/

section .data
table:                dq  print_percent ; '%'
  times('b' - '%' - 1)dq  case_default  ; ('%' - 'b')
                      dq  print_binary  ; 'b'
                      dq  print_char      
                      dq  print_decimal ; 'd'
  times('h' - 'd' - 1)dq  case_default                        
                      dq  print_hex     ; 'h'
  times('s' - 'h' - 1)dq  case_default    
                      dq  print_string  ; 's'

str_hex: db '0123456789ABCDEF'

section .bss
buf: resb 64
bufSize: equ $ - buf