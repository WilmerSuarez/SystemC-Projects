/* Robot Navigation - General Definitions */
#ifndef __DEFS_H__
#define __DEFS_H__
#include "systemc.h"

/* Shared Robot Definitions */
#define ROBOT_NUM           1       // One robot for now
#define ROBOT_STEP_SIZE     0.5     // 0.5m step size

/* Shared Obstacle Definitions */
#define OBSTACLE_STEP_SIZE  1       // 1m step size
#define MOVING_OBSTACLE_NUM 1       // One moving Obstacle for now
#define STATIC_OBSTACLE_NUM 1       // One static Obstacle for now

/* Shared Robot Status definitions */
#define STOPPED     "STOPPED"
#define IDLE        "IDLE"
#define MOVING      "MOVING"



/* Shared Grid definitions */
#define GRID_SIZE_X         2       // 2 meters
#define GRID_SIZE_Y         2       // 2 meters
#define MAX_GRID_INDEX      90      // Total number of grids (9x10 grid)
#define MAX_GRID_NUM_X      10      // 10 grids horizontally
#define MAX_GRID_NUM_Y      9       // 10 grids vertically
#define ROBOT_PATH_SIZE     5       // 5 grids

/* Holds a grid coordinate */
struct coord {
    uint x;
    uint y;
};

/* 
    Holds the Lower Left and Upper Right 
    coordinates (x, y) of a Grid 
*/
struct gridcoord{
    struct coord LL;      // Lower Left grid coordinate (x, y)
    struct coord UR;      // Upper Right grid coordinate (x, y)
};

extern struct gridcoord map[MAX_GRID_INDEX];

/* The RDS table holds the status for all robots */                       
struct RDS {
    uint CG;                // Current Grid
    uint NG;                // Next Grid
    std::string STATUS;     // Robot Status
};

extern struct RDS RDS[ROBOT_NUM];

/* MAP
    Individual Grid Dimensions: GRID_SIZE_X x GRID_SIZE_Y 
     ____ ____ ____ ____ ____ ____ ____ ____ ____ ____
    |    |    |    |    |    |    |    |    |    |    | 
    |____|____|____|____|____|____|____|____|____|____|

     
    Number of Grids: MAX_GRID_INDEX
*/

#endif // __DEFS_H__