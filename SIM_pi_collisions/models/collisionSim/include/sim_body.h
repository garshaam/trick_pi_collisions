/*************************************************************************
PURPOSE: ( Simulation Functionality Header )
**************************************************************************/

#ifndef SIM_BODY_H
#define SIM_BODY_H

#include "block.h"
#include "collision_handler.h"
#include "trick_utils/comm/include/tc.h"

//extern "C" required to prevent function definition mangling
extern "C" {

int sim_deriv(CollisionHandler* C);
int sim_integ(CollisionHandler* C);
int sim_default_data( CollisionHandler* C);
int sim_init(CollisionHandler* C);
double wall_block_impact(CollisionHandler* C);
double inter_block_impact(CollisionHandler* C);
int check_if_over(CollisionHandler* C);
int sim_shutdown(CollisionHandler* C);

}

#endif