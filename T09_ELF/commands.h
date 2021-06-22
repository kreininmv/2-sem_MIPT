/* push register to stack */
#define PUSH_EAX 0x50
#define PUSH_ECX 0x51
#define PUSH_EDX 0x52
#define PUSH_EBX 0x53
#define PUSH_EBP 0x55
#define PUSH_ESI 0x56
#define PUSH_EDI 0x57

/* pop to register from stack */
#define POP_EAX 0x58
#define POP_ECX 0x59
#define POP_EDX 0x5a
#define POP_EBX 0x5b
#define POP_EBP 0x5d
#define POP_ESI 0x5e
#define POP_EDI 0x5f

/* push from ram by sum of register and number */
#define PUSH_EAX_RAM 0xffb0
#define PUSH_ECX_RAM 0xffb1
#define PUSH_EDX_RAM 0xffb2
#define PUSH_EBX_RAM 0xffb3
#define PUSH_EBP_RAM 0xffb5
#define PUSH_ESI_RAM 0xffb6
#define PUSH_EDI_RAM 0xffb7

/* pop to ram in sum of register and number from stack */
#define POP_EAX_RAM 0x8f80
#define POP_ECX_RAM 0x8f81
#define POP_EDX_RAM 0x8f82
#define POP_EBX_RAM 0x8f83
#define POP_EBP_RAM 0x8f84
#define POP_ESI_RAM 0x8f85
#define POP_EDI_RAM 0x8f86

/* push number */
#define PUSH 0x68

/* oooooh (<0>__<0>) */
#define NOP 0x90

/* jump relative */
#define JMP_REL 0xe9
#define JA_REL  0x0f87
#define JAE_REL 0x0f83
#define JB_REL  0x0f82
#define JBE_REL 0x0f86
#define JE_REL  0x0f84
#define JNE_REL 0x0f85

/* call and return */
#define CALL_REL 0xe8
#define RET      0xc3


//eax - 6, ebx - 3, ecx - 7, edx - 2
// ax - esi
// bx - ebx
// cx - edi
// dx - edx

/* mov eax to register */
#define MOV_EAX_EAX 0x8bc0
#define MOV_EAX_ECX 0x8bc1
#define MOV_EAX_EDX 0x8bc2
#define MOV_EAX_EBX 0x8bc3
#define MOV_EAX_ESP 0x8bc4
#define MOV_EAX_EBP 0x8bc5
#define MOV_EAX_ESI 0x8bc6
#define MOV_EAX_EDI 0x8bc7

/* mov ecx to register */
#define MOV_ECX_EAX 0x8bc8
#define MOV_ECX_ECX 0x8bc9
#define MOV_ECX_EDX 0x8bca
#define MOV_ECX_EBX 0x8bcb
#define MOV_ECX_ESP 0x8bcc
#define MOV_ECX_EBP 0x8bcd
#define MOV_ECX_ESI 0x8bce
#define MOV_ECX_EDI 0x8bcf

/* mov edx to register */
#define MOV_EDX_EAX 0x8bd0
#define MOV_EDX_ECX 0x8bd1
#define MOV_EDX_EDX 0x8bd2
#define MOV_EDX_EBX 0x8bd3
#define MOV_EDX_ESP 0x8bd4
#define MOV_EDX_EBP 0x8bd5
#define MOV_EDX_ESI 0x8bd6
#define MOV_EDX_EDI 0x8bd7

/* mov ebx to register */
#define MOV_EBX_EAX 0x8bd8
#define MOV_EBX_ECX 0x8bd9
#define MOV_EBX_EDX 0x8bda
#define MOV_EBX_EBX 0x8bdb
#define MOV_EBX_ESP 0x8bdc
#define MOV_EBX_EBP 0x8bdd
#define MOV_EBX_ESI 0x8bde
#define MOV_EBX_EDI 0x8bdf

/* mov esp to register */
#define MOV_ESP_EAX 0x8be0
#define MOV_ESP_ECX 0x8be1
#define MOV_ESP_EDX 0x8be2
#define MOV_ESP_EBX 0x8be3
#define MOV_ESP_ESP 0x8be4
#define MOV_ESP_EBP 0x8be5
#define MOV_ESP_ESI 0x8be6
#define MOV_ESP_EDI 0x8be7

/* mov ebp to register */
#define MOV_EBP_EAX 0x8be8
#define MOV_EBP_ECX 0x8be9
#define MOV_EBP_EDX 0x8bea
#define MOV_EBP_EBX 0x8beb
#define MOV_EBP_ESP 0x8bec
#define MOV_EBP_EBP 0x8bed
#define MOV_EBP_ESI 0x8bee
#define MOV_EBP_EDI 0x8bef

/* mov esi to register */
#define MOV_ESI_EAX 0x8bf0
#define MOV_ESI_ECX 0x8bf1
#define MOV_ESI_EDX 0x8bf2
#define MOV_ESI_EBX 0x8bf3
#define MOV_ESI_ESP 0x8bf4
#define MOV_ESI_EBP 0x8bf5
#define MOV_ESI_ESI 0x8bf6
#define MOV_ESI_EDI 0x8bf7

/* mov edi to register*/
#define MOV_EDI_EAX 0x8bf8
#define MOV_EDI_ECX 0x8bf9
#define MOV_EDI_EDX 0x8bfa
#define MOV_EDI_EBX 0x8bfb
#define MOV_EDI_ESP 0x8bfc
#define MOV_EDI_EBP 0x8bfd
#define MOV_EDI_ESI 0x8bfe
#define MOV_EDI_EDI 0x8bff

/* mov number to register */
#define MOV_EAX 0xb8
#define MOV_ECX 0xb9
#define MOV_EDX 0xba
#define MOV_EBX 0xbb
#define MOV_ESP 0xbc
#define MOV_EBP 0xbd
#define MOV_ESI 0xbe
#define MOV_EDI 0xbf

/* add register to eax */
#define ADD_EAX_EAX 0x01c0
#define ADD_ECX_EAX 0x01c1
#define ADD_EDX_EAX 0x01c2
#define ADD_EBX_EAX 0x01c3
#define ADD_ESP_EAX 0x01c4
#define ADD_EBP_EAX 0x01c5
#define ADD_ESI_EAX 0x01c6
#define ADD_EDI_EAX 0x01c7

/* add register to ecx */
#define ADD_EAX_ECX 0x01c8
#define ADD_ECX_ECX 0x01c9
#define ADD_EDX_ECX 0x01ca
#define ADD_EBX_ECX 0x01cb
#define ADD_ESP_ECX 0x01cc
#define ADD_EBP_ECX 0x01cd
#define ADD_ESI_ECX 0x01ce
#define ADD_EDI_ECX 0x01cf

/* add register to edx */
#define ADD_EAX_EDX 0x01d0
#define ADD_ECX_EDX 0x01d1
#define ADD_EDX_EDX 0x01d2
#define ADD_EBX_EDX 0x01d3
#define ADD_ESP_EDX 0x01d4
#define ADD_EBP_EDX 0x01d5
#define ADD_ESI_EDX 0x01d6
#define ADD_EDI_EDX 0x01d7

/* add register to ebx */
#define ADD_EAX_EBX 0x01d8
#define ADD_ECX_EBX 0x01d9
#define ADD_EDX_EBX 0x01da
#define ADD_EBX_EBX 0x01db
#define ADD_ESP_EBX 0x01dc
#define ADD_EBP_EBX 0x01dd
#define ADD_ESI_EBX 0x01de
#define ADD_EDI_EBX 0x01df

/* add register to esp */
#define ADD_EAX_ESP 0x01e0
#define ADD_ECX_ESP 0x01e1
#define ADD_EDX_ESP 0x01e2
#define ADD_EBX_ESP 0x01e3
#define ADD_ESP_ESP 0x01e4
#define ADD_EBP_ESP 0x01e5
#define ADD_ESI_ESP 0x01e6
#define ADD_EDI_ESP 0x01e7

/* add register ebp */
#define ADD_EAX_EBP 0x01e8
#define ADD_ECX_EBP 0x01e9
#define ADD_EDX_EBP 0x01ea
#define ADD_EBX_EBP 0x01eb
#define ADD_ESP_EBP 0x01ec
#define ADD_EBP_EBP 0x01ed
#define ADD_ESI_EBP 0x01ee
#define ADD_EDI_EBP 0x01ef

/* add register to esi */
#define ADD_EAX_ESI 0x01f0
#define ADD_ECX_ESI 0x01f1
#define ADD_EDX_ESI 0x01f2
#define ADD_EBX_ESI 0x01f3
#define ADD_ESP_ESI 0x01f4
#define ADD_EBP_ESI 0x01f5
#define ADD_ESI_ESI 0x01f6
#define ADD_EDI_ESI 0x01f7

/* add register edi */
#define ADD_EAX_EDI 0x01f8
#define ADD_ECX_EDI 0x01f9
#define ADD_EDX_EDI 0x01fa
#define ADD_EBX_EDI 0x01fb
#define ADD_ESP_EDI 0x01fc
#define ADD_EBP_EDI 0x01fd
#define ADD_ESI_EDI 0x01fe
#define ADD_EDI_EDI 0x01ff

/* subtraction eax from register */
#define SUB_EAX_EAX 0x2bc0
#define SUB_EAX_ECX 0x2bc1
#define SUB_EAX_EDX 0x2bc2
#define SUB_EAX_EBX 0x2bc3
#define SUB_EAX_ESP 0x2bc4
#define SUB_EAX_EBP 0x2bc5
#define SUB_EAX_ESI 0x2bc6
#define SUB_EAX_EDI 0x2bc7

/* subtraction ecx from register */
#define SUB_ECX_EAX 0x2bc8
#define SUB_ECX_ECX 0x2bc9
#define SUB_ECX_EDX 0x2bca
#define SUB_ECX_EBX 0x2bcb
#define SUB_ECX_ESP 0x2bcc
#define SUB_ECX_EBP 0x2bcd
#define SUB_ECX_ESI 0x2bce
#define SUB_ECX_EDI 0x2bcf

/* subtraction edx from register */
#define SUB_EDX_EAX 0x2bd0
#define SUB_EDX_ECX 0x2bd1
#define SUB_EDX_EDX 0x2bd2
#define SUB_EDX_EBX 0x2bd3
#define SUB_EDX_ESP 0x2bd4
#define SUB_EDX_EBP 0x2bd5
#define SUB_EDX_ESI 0x2bd6
#define SUB_EDX_EDI 0x2bd7

/* subtraction ebx from register */
#define SUB_EBX_EAX 0x2bd8
#define SUB_EBX_ECX 0x2bd9
#define SUB_EBX_EDX 0x2bda
#define SUB_EBX_EBX 0x2bdb
#define SUB_EBX_ESP 0x2bdc
#define SUB_EBX_EBP 0x2bdd
#define SUB_EBX_ESI 0x2bde
#define SUB_EBX_EDI 0x2bdf

/* subtraction esp from register */
#define SUB_ESP_EAX 0x2be0
#define SUB_ESP_ECX 0x2be1
#define SUB_ESP_EDX 0x2be2
#define SUB_ESP_EBX 0x2be3
#define SUB_ESP_ESP 0x2be4
#define SUB_ESP_EBP 0x2be5
#define SUB_ESP_ESI 0x2be6
#define SUB_ESP_EDI 0x2be7

/* subtraction epb from register */
#define SUB_EBP_EAX 0x2be8
#define SUB_EBP_ECX 0x2be9
#define SUB_EBP_EDX 0x2bea
#define SUB_EBP_EBX 0x2beb
#define SUB_EBP_ESP 0x2bec
#define SUB_EBP_EBP 0x2bed
#define SUB_EBP_ESI 0x2bee
#define SUB_EBP_EDI 0x2bef

/* subtraction esi from register */
#define SUB_ESI_EAX 0x2bf0
#define SUB_ESI_ECX 0x2bf1
#define SUB_ESI_EDX 0x2bf2
#define SUB_ESI_EBX 0x2bf3
#define SUB_ESI_ESP 0x2bf4
#define SUB_ESI_EBP 0x2bf5
#define SUB_ESI_ESI 0x2bf6
#define SUB_ESI_EDI 0x2bf7

/* subtraction edi from register */
#define SUB_EDI_EAX 0x2bf8
#define SUB_EDI_ECX 0x2bf9
#define SUB_EDI_EDX 0x2bfa
#define SUB_EDI_EBX 0x2bfb
#define SUB_EDI_ESP 0x2bfc
#define SUB_EDI_EBP 0x2bfd
#define SUB_EDI_ESI 0x2bfe
#define SUB_EDI_EDI 0x2bff

/* compare register with eax */
#define CMP_EAX_EAX 0x39c0
#define CMP_ECX_EAX 0x39c1
#define CMP_EDX_EAX 0x39c2
#define CMP_EBX_EAX 0x39c3
#define CMP_ESP_EAX 0x39c4
#define CMP_EBP_EAX 0x39c5
#define CMP_ESI_EAX 0x39c6
#define CMP_EDI_EAX 0x39c7

/* compare register with ecx */
#define CMP_EAX_ECX 0x39c8
#define CMP_ECX_ECX 0x39c9
#define CMP_EDX_ECX 0x39ca
#define CMP_EBX_ECX 0x39cb
#define CMP_ESP_ECX 0x39cc
#define CMP_EBP_ECX 0x39cd
#define CMP_ESI_ECX 0x39ce
#define CMP_EDI_ECX 0x39cf

/* compare register with edx */
#define CMP_EAX_EDX 0x39d0
#define CMP_ECX_EDX 0x39d1
#define CMP_EDX_EDX 0x39d2
#define CMP_EBX_EDX 0x39d3
#define CMP_ESP_EDX 0x39d4
#define CMP_EBP_EDX 0x39d5
#define CMP_ESI_EDX 0x39d6
#define CMP_EDI_EDX 0x39d7

/* compare register with ebx */
#define CMP_EAX_EBX 0x39d8
#define CMP_ECX_EBX 0x39d9
#define CMP_EDX_EBX 0x39da
#define CMP_EBX_EBX 0x39db
#define CMP_ESP_EBX 0x39dc
#define CMP_EBP_EBX 0x39dd
#define CMP_ESI_EBX 0x39de
#define CMP_EDI_EBX 0x39df

/* compare register with esp*/
#define CMP_EAX_ESP 0x39e0
#define CMP_ECX_ESP 0x39e1
#define CMP_EDX_ESP 0x39e2
#define CMP_EBX_ESP 0x39e3
#define CMP_ESP_ESP 0x39e4
#define CMP_EBP_ESP 0x39e5
#define CMP_ESI_ESP 0x39e6
#define CMP_EDI_ESP 0x39e7

/* compare register with epb */
#define CMP_EAX_EBP 0x39e8
#define CMP_ECX_EBP 0x39e9
#define CMP_EDX_EBP 0x39ea
#define CMP_EBX_EBP 0x39eb
#define CMP_ESP_EBP 0x39ec
#define CMP_EBP_EBP 0x39ed
#define CMP_ESI_EBP 0x39ee
#define CMP_EDI_EBP 0x39ef

/* compare register with esi */
#define CMP_EAX_ESI 0x39f0
#define CMP_ECX_ESI 0x39f1
#define CMP_EDX_ESI 0x39f2
#define CMP_EBX_ESI 0x39f3
#define CMP_ESP_ESI 0x39f4
#define CMP_EBP_ESI 0x39f5
#define CMP_ESI_ESI 0x39f6
#define CMP_EDI_ESI 0x39f7

/* compare register with edi */
#define CMP_EAX_EDI 0x39f8
#define CMP_ECX_EDI 0x39f9
#define CMP_EDX_EDI 0x39fa
#define CMP_EBX_EDI 0x39fb
#define CMP_ESP_EDI 0x39fc
#define CMP_EBP_EDI 0x39fd
#define CMP_ESI_EDI 0x39fe
#define CMP_EDI_EDI 0x39ff

/* add number to register */
#define ADD_EAX 0x81c0
#define ADD_ECX 0x81c1
#define ADD_EDX 0x81c2
#define ADD_EBX 0x81c3
#define ADD_ESP 0x81c4
#define ADD_EBP 0x81c5
#define ADD_ESI 0x81c6
#define ADD_EDI 0x81c7

/* subtraction number from register */
#define SUB_EAX 0x81e8
#define SUB_ECX 0x81e9
#define SUB_EDX 0x81ea
#define SUB_EBX 0x81eb
#define SUB_ESP 0x81ec
#define SUB_EBP 0x81ed
#define SUB_ESI 0x81ee
#define SUB_EDI 0x81ef

/* compare number with register */
#define CMP_EAX 0x81f8
#define CMP_ECX 0x81f9
#define CMP_EDX 0x81fa
#define CMP_EBX 0x81fb
#define CMP_ESP 0x81fc
#define CMP_EBP 0x81fd
#define CMP_ESI 0x81fe
#define CMP_EDI 0x81ff

/* multimply number with rergister */
#define MUL_EAX 0xf7e0
#define MUL_ECX 0xf7e1
#define MUL_EDX 0xf7e2
#define MUL_EBX 0xf7e3
#define MUL_ESP 0xf7e4
#define MUL_EBP 0xf7e5
#define MUL_ESI 0xf7e6
#define MUL_EDI 0xf7e7

/* divide with register */
#define DIV_EAX 0xf7f0
#define DIV_ECX 0xf7f1
#define DIV_EDX 0xf7f2
#define DIV_EBX 0xf7f3
#define DIV_ESP 0xf7f4
#define DIV_EBP 0xf7f5
#define DIV_ESI 0xf7f6
#define DIV_EDI 0xf7f7
