/*********************************************************************
PURPOSE: ( Simulation Functionality )
*********************************************************************/
#include <stddef.h>
#include <stdio.h>
#include "trick/integrator_c_intf.h"
#include "../include/sim_body.h"

#ifndef SIM_BODY_CPP
#define SIM_BODY_CPP

int sim_deriv(CollisionHandler* C) {

    //Velocities are constant so nothing happens here
    return(0);
}

int sim_integ(CollisionHandler* C) {
    int ipass;

    load_state(
        &C->block1.pos ,
        &C->block2.pos ,
        NULL); //Always end with null

    load_deriv(
        &C->block1.vel ,
        &C->block2.vel ,
        NULL);

    ipass = integrate();

    unload_state(
        &C->block1.pos ,
        &C->block2.pos ,
        NULL );

    return(ipass);
}

int sim_default_data(CollisionHandler* C) {
    C->block1.pos0 = 1; //These are arbitrary. All that matters is that block2 has a higher x value and both are positive
    C->block2.pos0 = 3;

    C->block1.vel0 = 0;
    C->block2.vel0 = -1;

    C->block1.mass = 1;
    C->block2.mass = 100;

    C->time = 0.0;
    C->numCollisions = 0;

    C->verbose = true;

    return 0;
}

int sim_init(CollisionHandler* C) {
   
    C->block1.pos = C->block1.pos0;
    C->block2.pos = C->block2.pos0;

    C->block1.vel = C->block1.vel0;
    C->block2.vel = C->block2.vel0;

    return 0; 
}

double wall_block_impact(CollisionHandler* C) {
    double tgo ; 
    double now ; // current integration time.
    
    Block& b1 = C->block1;
    Block& b2 = C->block2;

    C->wallBlockCollision.error = C->block1.pos;
    now = get_integ_time();
    tgo = regula_falsi( now, &(C->wallBlockCollision) );
    if (tgo == 0.0) {
        now = get_integ_time();
        reset_regula_falsi( now, &(C->wallBlockCollision) ); 
        C->numCollisions += 1;
        double newB1Velocity = -b1.vel;
        b1.vel = newB1Velocity;

        b2.pos -= b1.pos; //Shifting both blocks away from the negative side of the wall
        b1.pos = 0; //For some reason, shifting the blocks away does not improve results but takes way longer. I am not sure why.

        if (C->verbose) {
            fprintf(stderr, "\n\nIMPACT: t = %.9f, position = %.9f\n\n", now, b1.pos);
        }
    }
    return (tgo) ;
}

double inter_block_impact(CollisionHandler* C) {
    double tgo ; 
    double now ;
    
    Block& b1 = C->block1;
    Block& b2 = C->block2;

    C->interBlockCollision.error = C->block2.pos - C->block1.pos - 1;
    now = get_integ_time() ;                         
    tgo = regula_falsi( now, &(C->interBlockCollision) );
    if (tgo == 0.0) {
        now = get_integ_time();
        reset_regula_falsi( now, &(C->interBlockCollision) );
        C->numCollisions += 1;
        double newB1Velocity = ((b1.mass-b2.mass)*b1.vel + 2*b2.mass*b2.vel) / (b1.mass + b2.mass);
        double newB2Velocity = (2*b1.mass*b1.vel - (b1.mass-b2.mass)*b2.vel) / (b1.mass + b2.mass);
        b1.vel = newB1Velocity;
        b2.vel = newB2Velocity;
        
        if (C->verbose) {
            fprintf(stderr, "\n\nIMPACT: t = %.9f, position = %.9f\n\n", now, b1.pos);
        }
    }
    return (tgo) ;
}

int check_if_over(CollisionHandler* C) {
    Block& b1 = C->block1;
    Block& b2 = C->block2;

    //If both blocks are moving to the right and the left block is slower, there will be no more collisions.
    if(b1.vel >= 0 && b2.vel >= 0 && b1.vel < b2.vel) { 
        printf("Collision no longer possible. Exiting...\n");
        exec_terminate("End of simulation", "Collision no longer possible");
    }

    return 0;
}

int sim_shutdown(CollisionHandler* C) {
    double t = exec_get_sim_time();
    printf( "========================================\n");
    printf( "      Blocks State at Shutdown     \n");
    printf( "t = %g\n", t);
    printf( "num collisions = [%.9d]\n", C->numCollisions);
    printf( "========================================\n");
    return 0 ;
}
#endif