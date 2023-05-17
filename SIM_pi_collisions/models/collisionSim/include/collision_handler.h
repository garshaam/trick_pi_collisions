/*************************************************************************
PURPOSE: ( Collision Handler Definition )
**************************************************************************/

#ifndef COLLISION_HANDLER_H
#define COLLISION_HANDLER_H

#include "block.h"
#include "trick/regula_falsi.h"
#include "trick_utils/comm/include/tc.h"
#include "trick_utils/comm/include/tc_proto.h"
#include "trick/exec_proto.h"

struct CollisionHandler {

    REGULA_FALSI interBlockCollision;
    REGULA_FALSI wallBlockCollision;

    Block block1;
    Block block2;

    double time;        /* s Model time */

    int numCollisions;

    bool verbose;
};
#endif