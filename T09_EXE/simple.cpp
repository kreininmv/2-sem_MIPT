#include "trans.h"
//Примеры для упрощения:
/*
1.  push 1
    pop reg
    - mov reg, 1

2.  push reg1
    pop reg2
    - mov reg2, reg1

3.  push num
    push reg1
    add
    pop reg1
    - add reg1, num

4.  push reg1
    push num
    add
    pop reg1
    - add reg1, num

5. push reg1
   push num
   sub 
   pop reg1
   - sub reg1, num

6. push reg1
   push num
   jne: number to jump
   - cmp reg1, num
   - jne: number to jump
   
7. push num
   push reg1
   jne: number to jump
   - cmp reg1, num
   -jne: number to jump

8. push reg1
   push reg2
   jne: number to jump
   
   - cmp reg1, reg2
   - jne: number to jump
*/

/* Порядок регистров
 0  -   EAX
 1  -   ECX
 2  -   EDX
 3  -   EBX
 4  -   ESP
 5  -   EBP
 6  -   ESI
 7  -   EDI
*/
//push-popы
#define PUSH_NUM  1
#define PUSH_AX   132
#define POP_AX    134
#define PUSH_BX   136
#define POP_BX    138
#define PUSH_CX   144
#define POP_CX    146
#define PUSH_DX   160
#define POP_DX    162

//operations
#define ADD       3
#define SUB       5

//moves AX to register
#define MOV_AX_AX 100
#define MOV_AX_BX 101
#define MOV_AX_CX 102
#define MOV_AX_DX 103
//moves BX to register
#define MOV_BX_AX 104
#define MOV_BX_BX 105
#define MOV_BX_CX 106
#define MOV_BX_DX 107
//moves CX to register
#define MOV_CX_AX 108
#define MOV_CX_BX 109
#define MOV_CX_CX 110
#define MOV_CX_DX 111
//moves DX to register
#define MOV_DX_AX 112
#define MOV_DX_BX 113
#define MOV_DX_CX 114
#define MOV_DX_DX 115

//moves number
#define MOV_AX    116
#define MOV_BX    117
#define MOV_CX    118
#define MOV_DX    119

//add number to register
#define ADD_AX    120
#define ADD_BX    121
#define ADD_CX    122
#define ADD_DX    123

//sub number from register
#define SUB_AX    124
#define SUB_BX    125
#define SUB_CX    126
#define SUB_DX    126

//the usefull operation
#define NOP       245

#define BYTE(i) (unsigned char)(in.buf[i])

bool is_pop(unsigned char command) {
  if (command == POP_AX || command == POP_BX || command == POP_CX || command == POP_DX)
    return true;

  return false;
}

bool is_push(unsigned char command) {
  if (command == PUSH_AX || command == PUSH_BX || command == PUSH_CX || command == PUSH_DX)
    return true;

  return false;
}

int reg_number(unsigned char command) {
  if (command == PUSH_AX || command == POP_AX)
    return 0x6;
  if (command == PUSH_BX || command == POP_BX)
    return 0x3;
  if (command == PUSH_CX || command == POP_CX)
    return 0x7;
  if (command == PUSH_DX || command == POP_DX)
    return 0x2;

  return -1;
}


bool simplify(const mk5::buffer& in) {
  int flag = 0;
  for (size_t i = 16; i < in.size - 16; ) {
    //first example of simplify
    if (BYTE(i) == PUSH_NUM && is_pop(BYTE(i + 5))) {
      int reg = (int)log2(in.buf[i + 5] & 0x3c) - 2;
      in.buf[i] = MOV_AX + (int)log2(in.buf[i + 5] & 0x3c) - 2;
      in.buf[i + 5] = NOP;
      i += 6;
      flag = 1;
    }
    //second example of simplify
    else if (is_push(BYTE(i)) && is_pop(BYTE(i+1))) {
      int num_reg_push = (int)log2(BYTE(i) & 0x3c) - 2,
        num_reg_pop = (int)log2(BYTE(i) & 0x3c) - 2;
      
      in.buf[i] = MOV_AX_AX + num_reg_pop + num_reg_push * 4;
      in.buf[i + 1] = NOP;
      i += 2;
      flag = 1;
    }
    else if (BYTE(i) == PUSH_NUM && is_push(BYTE(i + 5))
      && BYTE(i + 6) == ADD && is_pop(BYTE(i + 7))
      && (BYTE(i + 5) & 0x3c) == (BYTE(i + 7) & 0x3c)) {

      int num_reg = (int)log2(BYTE(i + 5) & 0x3c) - 2;
      in.buf[i] = ADD_AX + num_reg;
      in.buf[i + 5] = in.buf[i + 6] = in.buf[i + 7] = NOP;
      i += 8;
      flag = 1;
    }
    else if (in.buf[i + 1] == PUSH_NUM && is_push(BYTE(i))
      && BYTE(i + 6) == ADD && is_pop(BYTE(i + 7))
      && (BYTE(i) & 0x3c) == (BYTE(i + 7) & 0x3c)) {

      int num_reg = (int)log2(BYTE(i) & 0x3c) - 2;
      in.buf[i + 1] = ADD_AX + num_reg;
      in.buf[i] = in.buf[i + 6] = in.buf[i + 7] = NOP;
      i += 8;
      flag = 1;
    }
    else if (BYTE(i + 1) == PUSH_NUM && is_push(BYTE(i))
      && BYTE(i + 6) == SUB && is_pop(BYTE(i + 7))
      && (BYTE(i) & 0x3c) == (BYTE(i + 7) & 0x3c)) {

      int num_reg = (int)log2(BYTE(i) & 0x3c) - 2;
      in.buf[i + 1] = SUB_AX + num_reg;
      in.buf[i] = in.buf[i + 6] = in.buf[i + 7] = NOP;
      i += 8;
      flag = 1;
    }
    else
      i++;
  }
  return flag;
}

//push-popы
#undef PUSH_NUM
#undef PUSH_AX 
#undef POP_AX  
#undef PUSH_BX 
#undef POP_BX  
#undef PUSH_CX 
#undef POP_CX  
#undef PUSH_DX 
#undef POP_DX  
#undef ADD      
#undef SUB      
#undef MOV_AX_AX
#undef MOV_AX_BX
#undef MOV_AX_CX
#undef MOV_AX_DX
#undef MOV_BX_AX
#undef MOV_BX_BX
#undef MOV_BX_CX
#undef MOV_BX_DX
#undef MOV_CX_AX
#undef MOV_CX_BX
#undef MOV_CX_CX
#undef MOV_CX_DX
#undef MOV_DX_AX
#undef MOV_DX_BX
#undef MOV_DX_CX
#undef MOV_DX_DX
#undef MOV_AX   
#undef MOV_BX   
#undef MOV_CX   
#undef MOV_DX   
#undef ADD_AX   
#undef ADD_BX   
#undef ADD_CX   
#undef ADD_DX   
#undef SUB_AX   
#undef SUB_BX   
#undef SUB_CX   
#undef SUB_DX   
#undef NOP      
#undef BYTE(i) 