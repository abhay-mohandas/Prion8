# Prion8
- 8 bit architecture and instruction length.
- 16 bit address length.
- 1/2/4/8 bytes -> byte, half-word, word, double-word
- Separate Instruction, Data and System space. Each 2^16 bytes.
	- Virtual address is used for Instruction and Data space.
	- System Space will be split for various uses.
- 8x8-bit General Purpose Registers: 
	- Head:RA,RB,RC,RD.
	- Tail:R0,R1,R2,R3.
- 16x16-bit Special Purpose Registers: CTRL,FAULT,FLAGS,IP,PG,SP,MA0,MA1,IOR,OPEX,FCR0,etc.
- 256 Regiser Banks, each with 4x8-bit registers as a part of Register Bank, these have predefined purpose.
	- RB0-RB7 reserved as Save register. Used to save values in Tail registers. Support for the Save register is specified in FR0.

## Register Usage:
- RA-D reg are called Head general purpose register, used to temporarily store values, perform ALU operation or have predefined uses.
- R0-3 reg are called Tail general purpose register, used to temporarily store values or perform ALU operation.
- CTRL reg is used to configure the system behaviour.
- FAULT reg is used to store the error information.
- FLAGS reg is used to store different flags like Carry, Zero, etc.
- IP reg is the Program Counter, used to point to the instruction address.
- PG reg is used to store the base paging address, Page size starting from 256 bytes.
- SP reg is the Stack Pointer register, used for push, pop, etc.
- MA0, MA1 reg is used for address related instructions like jump/load/store.
- IOR reg is used for I/O operations, holds the values to/from I/O devices.
- OPEX reg is used for opcode extension and holds the Opcode Set number.
	- Defines the behaviour of opcodes from 0x80[7:3]-0xFC[7:3] (32 instructions in total) based on the Opcode Set number.
	- This increases the theoretical limit of instructions from 32 to over 2M (32*(2**16)).
	- Support for OPEX is specified in FR0. OPEXn can have reserved opcodes.
	- Disabled if CTRL.OE is 0 and the OPEX instruction range will be same as OPEX=0(default instructions).
- FR0 (Feature Register 0) reg is a read-only register, holds the values to indicate various feature support.



### CTRL Register:
|Bits|Name      |Description                                         |
|----|----------|----------------------------------------------------|
|0   |US        |User Mode. Enabled if 1, else in supervisor mode    |
|1   |PG        |Paging enabled if 1                                 |
|2   |OE        |Opcode extention enabled if 1                       |
|3:15|RESERVED  |MBZ                                                 |


### FLAG Register:
|Bits|Name      |Description                   |
|----|----------|------------------------------|
|0   |CF        |Carry flag                    |
|1   |ZF        |Zero flag                     |
|2   |NF        |Negative flag                 |
|3   |TF        |True flag                     |
|4   |IF        |Interrupt flag                |
|5:15|RESERVED  |MBZ                           |


### FR0 Register:
|Bits|Name      	|Description                   						|
|----|--------------|------------------------------						|
|0   |SR Range		|Save Register range support starting from S0   	|
|	 |				|0= upto S3; 1= upto S7        						|
|1:3 |OPEX Range    |OPEX Range support starting from OPEX0         	|
|	 |				|0= OPEX0 only; 1= upto OPEX3; 2-7= Reserved	 	|
|4:15|RESERVED  	|MBZ                           						|