# Prion8
- 8 bit architecture and instruction length.
- 16 bit address length.
- Separate Instruction, Data and System space. Each 2^16 bytes.
  - Virtual address is used for Instruction and Data space.
  - System Space will be split for various uses.
- 8x8-bit General Purpose Registers: RA,RB,RC,RD,R0,R1,R2,R3.
- 16x16-bit Special Purpose Registers: CTRL,FAULT,FLAGS,IP,PG,SP,MADDR,etc.

## Register Usage:
- RA-D reg are general purpose register to temporarily store values, perform ALU operation or have predefined uses.
- R0-3 reg are general purpose register to temporarily store values or perform ALU operation.
- CTRL reg is used to configure the system behaviour.
- FAULT reg is used to store the error information.
- FLAGS reg is used to store different flags like Carry, Zero, etc.
- IR reg is the Program Counter, used to point to the instruction address.
- PG reg is used to store the base paging address, Page size of 256 bytes.
- SP reg is the Stack Pointer register, used for push, pop, etc.
- MADDR reg is used for address related instructions like jump/load/store.

### CTRL Register:
|Bits|Name      |Description                                         |
|----|----------|----------------------------------------------------|
|0   |US        |User Mode. Enabled if 1, else in supervisor mode    |
|1   |PG        |Paging enabled if 1                                 |
|2   |OE        |Opcode extention enabled if 1                       |
|3   |RB        |Register Bank, 2 Banks in total                     |
|4:15|RESERVED  |MBZ                                                 |


### FLAG Register:
|Bits|Name      |Description                   |
|----|----------|------------------------------|
|0   |CF        |Carry flag                    |
|1   |ZF        |Zero flag                     |
|2   |NF        |Negative flag                 |
|3   |TF        |True flag                     |
|4   |IF        |Interrupt flag                |
|5:15|RESERVED  |MBZ                           |
