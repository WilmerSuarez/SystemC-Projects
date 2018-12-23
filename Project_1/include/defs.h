#ifndef DEFS_H
#define DEFS_H

// ALU Op Codes
#define NOP     0x00
#define ADD     0x01
#define ADDI    0x02
#define SUB     0x03
#define SUBI    0x04
#define CMP     0x05
#define CMPI    0x06
#define AND     0x08
#define ANDI    0x0A
#define OR      0x0B
#define ORI     0x0C
#define XOR     0x0D
#define XORI    0x0E
#define MOV     0x0F
#define MOVI    0x10
#define LSH     0x11
#define LSHI_1  0x07
#define LSHI_2  0x17
#define ASH     0x12
#define ASHI_1  0x09
#define ASHI_2  0x19
#define LUI     0x13
#define LOAD    0x14
#define STOR    0x15  
#define BCOND   0x16
#define JCOND   0x18
#define JAL     0x1A

#endif // DEFS_H