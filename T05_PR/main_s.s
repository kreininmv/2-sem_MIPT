section .text 

global main 
extern printf

section .data
msg     db '%c %s eda for %d%%!111111', 0
number  dq 30;
love    db 'love'
I       dq 73

section .text
main:
    mov rsi, [I]
    mov rdx, love
    mov rcx, [number]

    mov rdi, msg

    mov rax, 0

    call printf

    ret

;  push r9
;  push r8
;  push rcx        
;  push rdx
;  push rsi
;  push rdi