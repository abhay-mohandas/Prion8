# Prion8
-8 bit architecture and instruction length.
-16 bit address length.
-Separate Instruction, Data and System space. Each 2^16 bytes.
 	-Virtual address is used for Instruction and Data space.
 	-System Space will be split for various uses.
-8 8-bit General Purpose Registers: R0,R1,R2,R3,RES0,RES1,PD0,PD1.
-8 16-bit Special Purpose Registers: CTRL,FAULT,FLAGS,IP,PG,SP,MADDR,PID.

## Register Usage:
-R0-3 reg are general purpose register to temporarily store values and perform ALU operation.
-RES0/1 reg is used separately or together (RES1:RES0) to store the result of ALU operations or predefined uses.
-PD0/1 reg is used separately or together (PD1:PD0) for predefined uses.
-CTRL reg is used to configure the system behaviour.
-FAULT reg is used to store the error information.
-FLAGS reg is used to store different flags like Carry, Zero, etc.
-IR reg is the Program Counter, used to point to the instruction address.
-PG reg is used to store the base paging address, Page size of 256 bytes.
-SP reg is the Stack Pointer register, used for push, pop, etc.
-MADDR reg is used for address related instructions like jump/load/store.
-(?)PID reg holds the Program ID, idea is to provide some degree of isolation between programs.

### CTRL Register:
|Bits|Name      |Description                                         |
|----|----------|----------------------------------------------------|
|0   |USER      |In user mode if 1, else in system mode              |
|1   |PAGING    |Paging enabled if 1                                 |
