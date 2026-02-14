#define NOP     0x00    // No Op
#define JZ      0x04    // 00000100-JZ[8]   Jump to address in MADDR if Zero Flag=1
#define JNZ     0x08    // 00001000-JNZ[8]	Jump to address in MADDR if Zero Flag=0
#define JC      0x0C    // 00001100-JC[8]	Jump to address in MADDR if Carry Flag=1
#define JNC     0x10    // 00010000-JNC[8]  Jump to address in MADDR if Carry Flag=0
#define JT      0x14    // 00010100-JT[8]   Jump to address in MADDR if True Flag=1
#define JMP     0x18    // 00011000-JMP[8]		Jump to address in MADDR
#define CALL    0x1C    // 00011100-CALL[8]		Call to address in MADDR and save return address in stack
#define RET     0x20    // 00100000-RET[8]		Return to return address saved in stack
#define MUL     0x24    // 00100100-MUL[8]		RC*RD=[RB:RA] and update flags
#define DIV     0x28    // 00101000-DIV[8]		RC/RD=[Remainer in RB][Quotient in RA] and update flags
#define BT      0x2C    // 00101100-BT[8]		Copy the bit value in RA at position specified by the value in RB, position value from 0 to 7
#define BTS     0x30    // 00110000-BTS[8]		Set bit in RA at position specified by the value in RB, position value from 0 to 7
#define BTC     0x34    // 00110100-BTC[8]		Clear bit in RA at position specified by the value in RB, position value from 0 to 7
#define ACR     0x38    // 00111000-ACR[8]		(A)dd (C)arry to (R)A, RA+CF=RA and update flags
#define SCR     0x3C    // 00111100-SCR[8]		(S)ub (C)arry from (R)eg, RA-CF=RA and update flags
#define MGS     0x40    // 01000000-MGS[8]		(M)ove (G)PR to (S)PR, move value from [RB:RA] to SRC SPR specified in RC
#define MSG     0x44    // 01000100-MSG[8]		(M)ove (G)PR to (S)PR, move value from SRC SPR specified in RC to [RB:RA]
#define FENCE   0x48    // 01001000-FENCE[8]	Used to serialise all previous memory operations
#define LWO     0x4C    // 01001100-LWO[8]		(L)oad (W)ith (O)ffset, Load value from address MADDR+RA into RB
#define SWO     0x50    // 01010000-SWO[8]		(S)tore (W)ith (O)ffset, Store value from RB to address MADDR+RA
#define INTR    0x54    // 01010100-INTR[8]		Signal Interrupt, Interrupt number is specified in RC
#define SFB     0x58    // 01011000-SFB[8]		(S)et (F)lag (B)it, set flag specified in RA
#define CFB     0x5C    // 01011100-CFB[8]		(C)lear (F)lag (B)it, clear flag specified in RA
#define CLRGP   0x60    // 01100000-CLRGP[8]	Clear all the GPRs
#define CLRGP   0x64    // 01100100-CLRRB[8]    Clear all the Register Banks, excluding GPRs
#define CFB     0x68    // 01101000-SWRB0[8]	(S)wap (W)ith (R)egister (B)ank 0, values of GPRs and Reg Bank0 is swapped
#define CFB     0x6C    // 01101100-SWRB1[8]	(S)wap (W)ith (R)egister (B)ank 1, values of GPRs and Reg Bank1 is swapped
#define CFB     0x70    // 01110000-SWRB2[8]	(S)wap (W)ith (R)egister (B)ank 2, values of GPRs and Reg Bank2  is swapped
#define CFB     0x74    // 01110100-CMP[8]		Compare, RB-RA and update flags
#define CFB     0x78    // 01111000-LDH[8]		Load half word/2 bytes from address in MADDR to [RB:RA]
#define CFB     0x7C    // 01111100-STH[8]		Store half word/2 bytes to address in MADDR from [RB:RA]

// 10000000-11111100 [OPEX DEFINED]

#define IMM         0x01    //     0001-IMM[4]  Immediate[4]				Move 4-bit immediate value to the lower 4-bits of RA
#define IMM_MASK    0xF0
#define LD          0x05    //    00101-LD[5]   SRC[3]		SRC -> GPR		Load value from address in MADDR into SRC reg 
#define LD_MASK     0xE0
#define ST          0x09    //    01001-ST[5]   SRC[3]		SRC -> GPR		Store value in SRC reg into address in MADDR
#define ST_MASK     0xE0
#define PUSH        0x0D    //    01101-PUSH[5] SRC[3]		SRC -> GPR		Push the value in SRC reg onto the stack and update SP
#define PUSH_MASK   0xE0
#define POP         0x15    //    10101-POP[5]  SRC[3]		SRC -> GPR		Pop the value from stack into SRC reg and update SP
#define POP_MASK    0xE0
#define INC         0x19    //    11001-INC[5]  SRC[3]		SRC -> GPR		Increment the value in SRC by 1
#define INC_MASK    0xE0
#define DEC         0x1D    //    11101-DEC[5]  SRC[3]		SRC -> GPR		Decrement the value in SRC by 1
#define DEC_MASK    0xE0
#define ADD         0x02    //    00010-ADD[5]  SRC[3]		SRC -> GPR		Add SRC to RA and store the result in RA, update flags
#define ADD_MASK    0xE0
#define SUB         0x06    //    00110-SUB[5]  SRC[3]		SRC -> GPR		Sub SRC from RA and store the result in RA, update flags
#define SUB_MASK    0xE0
#define AND         0x0A    //    01010-AND[5]  SRC[3]		SRC -> GPR		AND SRC to RA and store the result in RA, update flags
#define AND_MASK    0xE0
#define OR          0x0E    //    01110-OR[5]   SRC[3]		SRC -> GPR		OR SRC to RA and store the result in RA, update flags
#define OR_MASK     0xE0
#define XOR         0x12    //    10010-XOR[5]  SRC[3]		SRC -> GPR		XOR SRC to RA and store the result in RA, update flags
#define XOR_MASK    0xE0
#define NOT         0x16    //    10110-NOT[5]  SRC[3]		SRC -> GPR		NOT SRC to RA and store the result in RA, update flags
#define NOT_MASK    0xE0
#define SHL         0x1A    //    11010-SHL[5]  SRC[3]		SRC -> GPR		Shift Left value in RA by the value in SRC, update flags
#define SHL_MASK    0xE0
#define SHR         0x1E    //    11110-SHR[5]  SRC[3]		SRC -> GPR		Shift Right value in RA by the value in SRC, update flags
#define SHR_MASK    0xE0
#define RMV         0x03    //       11-RMV[2]  DST[3] SRC[3]  DST and SRC -> GPR	Move value from SRC reg to DST reg
#define RMV_MASK    0xFC