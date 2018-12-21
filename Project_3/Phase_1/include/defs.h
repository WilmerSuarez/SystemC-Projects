#ifndef __DEFS_H__
#define __DEFS_H__
#include "systemc.h"

#define TUPLE_ENTRIES_N         3   // 3 integer entires per Tuple
#define PACKET_SIZE             20  // 20 Tuples
#define BIT_SIZE                64  // 64-bit Integers

/* 1 Mbs */
#define BANDIWDTH               1000000     

/* Amount of time for completion of Packet Transmition */
#define PACKET_TRANSMIT_TIME    ((PACKET_SIZE * TUPLE_ENTRIES_N * BIT_SIZE) / (double)BANDIWDTH)    

/* MOBILE STATUS DEFINITIONS */
#define REQUEST     1
#define SENDING     2
#define DONE        4

#endif // __DEFS_H__
