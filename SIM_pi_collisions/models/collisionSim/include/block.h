/*************************************************************************
PURPOSE: ( Block Definition )
**************************************************************************/
#ifndef BLOCK_H
#define BLOCK_H

#include "trick_utils/comm/include/tc.h"

struct Block {

    double vel0;    /* *i m Init velocity of block */
    double pos0;    /* *i m Init position of block */
    
    double vel;     /* m/s x-velocity */
    double pos;     /* m x-position */

    double mass;    /* kg mass of block*/
};
#endif