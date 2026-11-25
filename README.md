# Prion8
- 8-bit architecture and instruction length.
- 16-bit address length.
- 1/2/4/8 bytes -> byte, half-word, word, double-word
- Separate Instruction and Data space. Each 2^16 bytes. Virtual address is used for Instruction and Data space.
- 8x8-bit General Purpose Registers: 
	- Head: RA,RB,RC,RD.
	- Tail: R0,R1,R2,R3.
- 16x16-bit Special Purpose Registers: CTRL,FAULT,FLAGS,IP,etc.
- 256 Regiser Banks, each with 4x8-bit registers as a part of Register Bank, these have predefined purpose.
	- RB0-RB7 reserved as Save register. Used to save values in Tail registers. Support for the Save register is specified in FR0.

## Register Usage:
- RA-D reg are called Head general purpose register, used to temporarily store values, perform ALU operation or have predefined uses.
- R0-3 reg are called Tail general purpose register, used to temporarily store values or perform ALU operation.
- CTRL reg is used to configure the system behaviour.
- FAULT reg holds the error information.
- FLAGS reg is used to store different flags like Carry, Zero, etc.
- IP reg is the Program Counter, used to point to the instruction address.
- IPG reg is used to store the base instruction paging address, Page size starting from 256 bytes.
- DPG reg is used to store the base data paging address, Page size starting from 256 bytes.
- SP reg is the Stack Pointer register, used for push, pop, etc.
- MA reg is used for address related instructions like jump/load/store.
- IOR reg is used for I/O operations, holds the values to/from I/O devices.
- FR0 (Feature Register 0) reg is a read-only register, holds the values to indicate various feature support.
- IVT reg holds the base address of the interrupt vector table.
- FADDR reg holds the faulting address, so the fault handler knows what went wrong.
- COREID reg holds the Core ID for multi-core processors


### SPR MAPPING
|Map |SPR	   |Read		    |Write	                                  |
|----|---------|----------------|-----------------------------------------|
|0   |CTRL     |Any mode        |Supervisor only                          |
|1   |FAULT    |Any mode        |Supervisor only                          |
|2   |FLAGS    |Any mode        |Any mode (SFB/CFB masking rules apply)   |
|3   |IP       |Next IP         |Any mode, and writing it is a jump       |
|4   |SP       |Any mode        |Any mode                                 |
|5   |MA       |Any mode        |Any mode                                 |
|6   |IOR      |Any mode        |Any mode                                 |
|7   |FR0      |Any mode	    |Fault (read-only)                        |
|8   |IPG      |Supervisor only |Supervisor only                          |
|9   |DPG      |Supervisor only |Supervisor only                          |
|10  |IVT      |Supervisor only |Supervisor only                          |
|11  |FADDR    |Supervisor only |Supervisor only                          |
|12  |COREID   |Any mode        |Fault (read-only)                        |
|13  |RESERVED |zero            |Fault                                    |
|14  |RESERVED |zero            |Fault                                    |
|15  |RESERVED |zero            |Fault                                    |


### Access rules:
- Accessing a supervisor-only SPR in user mode raises a privilege fault.
- Writing a read-only SPR (FR0, COREID) in any mode raises an invalid SPR access fault.
- Any access to a reserved SPR number (14 and above) raises an invalid SPR access fault.
- A faulting MGS/MSG changes nothing.


### CTRL Register:
|Bits|Name      |Description                                         |
|----|----------|----------------------------------------------------|
|0   |US        |User Mode. Enabled if 1, else in supervisor mode    |
|1   |PG        |Paging enabled if 1                                 |
|2   |OE        |Opcode extention enabled if 1                       |
|3:15|RESERVED  |MBZ                                                 |


### FLAGS Register:
|Bits|Name      |Description                   |
|----|----------|------------------------------|
|0   |CF        |Carry flag                    |
|1   |ZF        |Zero flag                     |
|2   |NF        |Negative flag                 |
|3   |OF        |Overflow flag                 |
|4   |IF        |Interrupt flag                |
|5:15|RESERVED  |MBZ                           |


### FR0 Register:
|Bits|Name      	|Description                   						|
|----|--------------|---------------------------------------------------|
|0   |SR Range		|Save Register range support starting from S0   	|
|	 |				|0= upto S3; 1= upto S7        						|
|1:15|RESERVED  	|MBZ                           						|


## Faults and the Fault registers

### FAULT fields:
- Bits 3:0 vector is the vector-table entry used for the fault.
- Bits 7:4 for sub-vector. Extra detail about the fault. It is 0 for faults that don't define one.
- Bit 8 is valid bit, set while a fault is active. Cleared once fault is handled.
- Bits 15:9 is reserved(MBZ).

### FADDR:
- Holds the faulting address or the address of the failing instruction.

### Fault Vector Table:
|Vector|Fault                                                                          |
|------|-------------------------------------------------------------------------------|
|0     |Divide by zero                                                                 |
|1     |Illegal instruction (reserved opcode, INTR with RC < 16, etc)                  |
|2     |Privilege violation (supervisor-only SPR,ERET in user mode,user change of IF)  |
|3     |Invalid SPR access (write to read-only SPR, reserved SPR number)               |
|4     |Page fault                                                                     |
|15:5  |RESERVED, MBZ                                                                  |

### Fault Sub-Vector:
- Page fault sub-vector:
	- Bits 6:4, access kind: 
		- 0	= Instruction fetch
		- 1	= Data read
		- 2 = Data write
		- 3 = ILD
		- 4 = IST
		- 5-7 = Reserved
	- Bit 7, reason: 0 = page not valid, 1 = permission denied.

"""" #UNDERWORK# """"
## Vector table
Interrupt Vector Table or IVT holds the data-space virtual address of the table: 256 entries x 2 bytes, 
each the instruction-space address of a handler (little endian). Entry n is at IVT + 2n.
- 0-4: faults (the fault vector). 5-15: reserved. 16-255: hardware interrupts and INTR.

## Exception and interrupt entry
Applies to faults, INTR and accepted hardware interrupts.
1. Fault only: FAULT = 0x100 | (sub-vector << 4) | vector (V = 1). FADDR = the faulting
   address for a page fault, otherwise the address of the faulting instruction.
2. Saved IP: the faulting instruction for a fault, the next instruction for INTR and
   hardware interrupts.
3. Push IP, FLAGS, CTRL (2 bytes each, same rule as CALL). Then [SP] = CTRL,
   [SP+2] = FLAGS, [SP+4] = IP.
4. IF = 0 and US = 0 (supervisor mode). Everything else is unchanged.
5. IP = the 16-bit value at [IVT + 2 x vector], read as a supervisor data access
   (translated if PG = 1).
- Double fault: a fault in step 3 or 5 halts the core. FAULT and FADDR record the second fault.
- Hardware interrupts are taken only between instructions, and only when IF = 1.
  Faults and INTR are never masked by IF.
- A faulting instruction has no effect (registers, flags, memory, SP and MA unchanged),
  so it can be retried. Multi-access instructions check every access first.
- Page fault access kind: XCHG, PUSH, CALL, RCALL and PUSHM report data write. POP, RET,
  POPM and ERET report data read.

## INTR
Vector number in RC. If RC < 16: illegal instruction fault (vector 1), in any mode.
Otherwise run the entry sequence with that vector. Allowed in any mode, not masked by IF.

## ERET
Supervisor only (user mode: privilege fault, vector 2).
CTRL = [SP], FLAGS = [SP+2], IP = [SP+4], SP = SP + 6. Reserved bits are ignored.
It restores the whole CTRL, so it returns to the saved mode. A handler may edit the saved
frame first (for example, to skip an instruction).
If the restored CTRL.US = 1, ERET also clears FAULT.V. Otherwise V is left unchanged
(supervisor-mode fault routines clear it in software, by writing 0 to FAULT).

## WAIT (proposed)
Resumes when a hardware interrupt request is pending, even if IF = 0. If IF = 1 the
interrupt is taken, with the instruction after WAIT as the saved IP. If IF = 0,
execution continues after WAIT.

## Reset
CTRL = 0 (supervisor mode, paging off, OE off), FLAGS = 0 (IF = 0), FAULT = 0, IP = 0x0000.
SP, IVT, FADDR and the other registers are undefined. FR0 and COREID are set by hardware.
Software sets SP and IVT before it sets IF.
""""