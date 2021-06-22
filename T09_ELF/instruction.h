//DSL 
//#define _ ,

#define DATA_SIZE sizeof(int)

#define TO_INT(PT) *((int *)(PT))

#define OUT_ADD(code) 

#define INC_PC ++PC

#define INC_OUT ++buf_out

#define ADD_DATA_SIZE(num) num += DATA_SIZE;

#define ADD_DATA_PC PC += DATA_SIZE;

#define INC_BT {INC_PC; INC_OUT;}

#define ADD_BT {ADD_DATA_SIZE(PC) ADD_DATA_SIZE(buf_out)}

#define ADD_OUT(num) buf_out += num;

#define CODE(i) (code_ptr[PC + (i)]

#define OUT_CODE(i) (buf_out[i])

#define CUR_CODE (code_ptr[PC])

#define CUR_OUT_CODE (*buf_out)

#define PUT_BYTE_CMD(COMND) {CUR_OUT_CODE = (char)(COMND); INC_OUT;}

#define PUT_WORD_CMD(COMND)              \
{                                        \
  PUT_BYTE_CMD(((COMND) >> 8) & 0xff);   \
  PUT_BYTE_CMD((COMND) & 0xff);          \
}

#define BYTE(COM) PUT_BYTE_CMD(COM)

#define WORD(COM) PUT_WORD_CMD(COM)


#define DLL_CALL(i)                                                                                            \
    WORD(0xFF15);                                                                                              \
    printf("Call dll(%d) - %x\n", i, (unsigned int)(IMAGE_BASE + IMPORT_START + IMPORT_TABLE.GetProcAddr(i))); \
    *((unsigned int *)(buf_out)) = (unsigned int)(IMAGE_BASE + IMPORT_START + IMPORT_TABLE.GetProcAddr(i));    \
    buf_out += sizeof(unsigned int);

//eax - 6, ebx - 3, ecx - 7, edx - 2
// ax - esi
// bx - ebx
// cx - edi
// dx - edx

DEF_INSTR(push, 1,
  {
    PUT_BYTE_CMD(PUSH);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })
  
DEF_INSTR(pop , 2,
  {
    CUR_OUT_CODE = POP_EAX;    
  },
  {
  })

// pop eax
// pop ecx
// add eax, ecx
// push eax

DEF_INSTR(add, 3,
  {
    PUT_BYTE_CMD(POP_EAX);
    PUT_BYTE_CMD(POP_ECX);
    PUT_WORD_CMD(ADD_EAX_ECX);
    PUT_BYTE_CMD(PUSH_EAX);
  },
  {
  })

DEF_INSTR(sub, 5,
  {
    PUT_BYTE_CMD(POP_EAX);
    PUT_BYTE_CMD(POP_ECX);
    PUT_WORD_CMD(SUB_EAX_ECX);
    PUT_BYTE_CMD(PUSH_EAX);
  },
  {
  })

DEF_INSTR(mul, 6,
  {
    BYTE(POP_EAX);
    BYTE(POP_ECX);
    WORD(MUL_ECX);
    BYTE(PUSH_EAX);
  },
  {
  })

DEF_INSTR(div, 7,
  {
   PUT_BYTE_CMD(POP_EAX);
   PUT_BYTE_CMD(POP_ECX);
   PUT_BYTE_CMD(PUSH_EDX);
   PUT_WORD_CMD(XOR_EDX_EDX);
   PUT_WORD_CMD(DIV_ECX);
   PUT_BYTE_CMD(POP_EDX);
   PUT_BYTE_CMD(PUSH_EAX);
  },
  {
  })

DEF_INSTR(in, 12,
  {
   DLL_CALL(4);
   BYTE(PUSH_EAX);
  },
  {
  })

#define JMP_FILL_TBL                                            \
  TABLE.push_old_inf(&code_ptr[PC-1], code_ptr + code_ptr[PC]); \
  PC += sizeof(int);  

DEF_INSTR(hlt, 15,
  {
    BYTE(PUSH)
    TO_INT(buf_out) = 0;
    ADD_OUT(DATA_SIZE);
    DLL_CALL(0);
  },
  {
  })

  
DEF_INSTR(jmp, 17,
  {
    BYTE(JMP_REL);
    ADD_OUT(4);
    ADD_DATA_PC;
  },
  {
    JMP_FILL_TBL;
  })



DEF_INSTR(ja, 18,
  {
    BYTE(POP_EAX);
    BYTE(POP_ECX);
    WORD(CMP_EAX_ECX);
    WORD(JA_REL);
    ADD_OUT(4);
    ADD_DATA_PC;
  },
  {
    JMP_FILL_TBL;
  })

DEF_INSTR(jae, 19,
  {
    BYTE(POP_EAX);
    BYTE(POP_ECX);
    WORD(CMP_EAX_ECX);
    WORD(JAE_REL);
    ADD_OUT(4);
    ADD_DATA_PC;
  },
  {
    JMP_FILL_TBL;
  })

DEF_INSTR(jb, 20,
  {
    BYTE(POP_EAX);
    BYTE(POP_ECX);
    WORD(CMP_EAX_ECX);
    WORD(JB_REL);
    ADD_OUT(4);
    ADD_DATA_PC;
  },
  {
    JMP_FILL_TBL; 
  })

DEF_INSTR(jbe, 21,
  {
    BYTE(POP_EAX);
    BYTE(POP_ECX);
    WORD(CMP_EAX_ECX);
    WORD(JBE_REL);
    ADD_OUT(4);
    ADD_DATA_PC;
  },
  {
    JMP_FILL_TBL; 
  })

DEF_INSTR(je, 22,
  {
    BYTE(POP_EAX);
    BYTE(POP_ECX);
    WORD(CMP_EAX_ECX);
    WORD(JE_REL);
    ADD_OUT(4);
    ADD_DATA_PC;
  },
  {
    JMP_FILL_TBL;
  })

//Start
//push    ebp
//mov     ebp, esp

// End
//mov     esp, ebp
//pop     ebp
DEF_INSTR(jne, 23,
  {
    BYTE(POP_EAX);
    BYTE(POP_ECX);
    WORD(CMP_EAX_ECX);
    WORD(JNE_REL);
    ADD_OUT(4);
    ADD_DATA_PC;
  },
  {
    JMP_FILL_TBL;
  })


    DEF_INSTR(call, 24,
  {
    BYTE(CALL_REL);
    ADD_OUT(4);
    ADD_DATA_PC;
  },
  {
    JMP_FILL_TBL;
  })


DEF_INSTR(rtrn, 25,
  {
     BYTE(RET);
  },
  {
  })

DEF_INSTR(label, 244, 
  {
    BYTE(NOP);
  },
  {
   // JMP_FILL_TBL;
  })

DEF_INSTR(NOP, 245,
  {
    BYTE(NOP);
  },
{
  // JMP_FILL_TBL;
})
#undef JMP_FILL_TBL 
/*
DEF_INSTRRAM(push, 65,
  {
  })

DEF_INSTRRAM(pop, 67,
  {
  })

DEF_INSTR(neg , 98, 
  {
  })
  */
DEF_INSTR(out , 99, 
  {
    DLL_CALL(3);
  },
  {
  })

DEF_INSTRARG(push, ax, 132, 
  {
    BYTE(PUSH_ESI);
  },
  {
  })

DEF_INSTRARG(pop, ax, 134,
  {
    BYTE(POP_ESI);
  },
  {
  })

DEF_INSTRARG(push, bx, 136, 
  {
    BYTE(PUSH_EBX);
  },
  {
  })

DEF_INSTRARG(pop, bx, 138,
  {
    BYTE(POP_EBX);
  },
  {
  })

DEF_INSTRARG(push, cx, 144, 
  {
    BYTE(PUSH_EDI);
  },
  {
  })

DEF_INSTRARG(pop, cx, 146,
  {
    BYTE(POP_EDI);
  },
  {
  })

DEF_INSTRARG(push, dx, 160, 
  {
    BYTE(PUSH_EDX);
  },
  {
  })

DEF_INSTRARG(pop, dx , 162, 
  {
    BYTE(POP_EDX);
  },
  {
  })


DEF_INSTR(mov_ax_ax, 100,
  {
    WORD(MOV_ESI_ESI);
  },
  {
  })

DEF_INSTR(mov_ax_bx, 101,
  {
    WORD(MOV_ESI_EBX);
  },
  {
  })


DEF_INSTR(mov_ax_cx, 102,
  {
    WORD(MOV_ESI_EDI);
  },
{
})

DEF_INSTR(mov_ax_dx, 103,
  {
    WORD(MOV_ESI_EDX);
  },
  {
  })


DEF_INSTR(mov_bx_ax, 104,
  {
    WORD(MOV_EBX_ESI);
  },
  {
  })

DEF_INSTR(mov_bx_bx, 105,
  {
    WORD(MOV_EBX_EBX);
  },
  {
  })


DEF_INSTR(mov_bx_cx, 106,
  {
    WORD(MOV_EBX_EDI);
  },
{
})

DEF_INSTR(mov_bx_dx, 107,
  {
    WORD(MOV_EBX_EDX);
  },
  {
  })

DEF_INSTR(mov_cx_ax, 108,
  {
    WORD(MOV_EDI_ESI);
  },
  {
  })

DEF_INSTR(mov_cx_bx, 109,
  {
    WORD(MOV_EDI_EBX);
  },
  {
  })


DEF_INSTR(mov_cx_cx, 110,
  {
    WORD(MOV_EDI_EDI);
  },
{
})

DEF_INSTR(mov_cx_dx, 111,
  {
    WORD(MOV_EDI_EDX);
  },
  {
  })

DEF_INSTR(mov_dx_ax, 112,
  {
    WORD(MOV_EDX_ESI);
  },
  {
  })

DEF_INSTR(mov_dx_bx, 113,
  {
    WORD(MOV_EDX_EBX);
  },
  {
  })


DEF_INSTR(mov_dx_cx, 114,
  {
    WORD(MOV_EDX_EDI);
  },
{
})

DEF_INSTR(mov_dx_dx, 115,
  {
    WORD(MOV_EDX_EDX);
  },
  {
  })
//eax - 6, ebx - 3, ecx - 7, edx - 2
// ax - esi
// bx - ebx
// cx - edi
// dx - edx

DEF_INSTR(mov_ax, 116,
  {
    BYTE(MOV_ESI);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(mov_bx, 117,
  {
    BYTE(MOV_EBX);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(mov_cx, 118,
  {
    BYTE(MOV_EDI);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(mov_dx, 119,
  {
    BYTE(MOV_EDX);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(add_ax, 120,
  {
    WORD(ADD_ESI);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(add_bx, 121,
  {
    WORD(ADD_EBX);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(add_cx, 122,
  {
    WORD(ADD_EDI);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(add_dx, 123,
  {
    WORD(ADD_EDX);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(sub_ax, 124,
  {
    WORD(SUB_ESI);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(sub_bx, 125,
  {
    WORD(SUB_EBX);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(sub_cx, 126,
  {
    WORD(SUB_EDI);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

DEF_INSTR(sub_dx, 127,
  {
    WORD(SUB_EDX);
    TO_INT(buf_out) = TO_INT(code_ptr + PC);
    ADD_BT;
  },
  {
    ADD_DATA_SIZE(PC);
  })

    /*
#undef _

#undef DATA_SIZE

#undef STK_PUSH

#undef STK_POP

#undef GET_FST_SEC_VALUES

#undef CODE_INT

#undef PUT_REG

#undef JMP_DISASM

#undef JMP_ASM

#undef DEF_JMP

#undef DEST_PROCESS

#undef WORD

#undef BYTE
    */