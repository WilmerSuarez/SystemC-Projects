#ifndef __DEFS_H__
#define __DEFS_H__
#include <vector>
#include "systemc.h"

#define MOBILE_NUM              4        // 4 Mobiles
#define ROI_NUM                 5        // 5 ROI per image
#define IMG_NUM                 5        // 5 Images
#define IMG_SIZE                8388608  // 8Mb

#define TUPLE_ENTRIES_N         3        // 3 integer entires per Tuple
#define PACKET_SIZE             20       // 20 Tuples
#define BIT_SIZE                64       // 64-bit Integers

/* MOBILE STATUS DEFINITIONS */
#define REQUEST     1
#define SENDING     2
#define DONE        4

/* Used to hold ROI dimensions for Mobile images received by the Server */
typedef std::vector<std::vector<std::pair<uint, uint> > > ROI;
/*struct ROI {
    std::vector<std::pair<uint, uint> > ROI_1;
    std::vector<std::pair<uint, uint> > ROI_2;
    std::vector<std::pair<uint, uint> > ROI_3;
    std::vector<std::pair<uint, uint> > ROI_4;
    std::vector<std::pair<uint, uint> > ROI_5;
};*/

#endif // __DEFS_H__
