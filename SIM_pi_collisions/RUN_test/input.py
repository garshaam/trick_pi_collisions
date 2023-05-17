exec(open("Modified_data/pi_collision_data.dr").read())

#Whether to print each impact to console
dyn.collisionHandler.verbose = False

#If the ratio of block2/block1 mass is equal to 100^n then (n+1) digits of pi are approximated.
dyn.collisionHandler.block1.mass = 1
dyn.collisionHandler.block2.mass = 1000000

#I would prefer to change the integrating timestep here but I cannot
#Therefore you can change block2's velocity as a proxy
#From my testing, too high speed will cause complete failure not gradual failure.
#This is probably because I do not test for block 2 moving past the 0 mark.

dyn.collisionHandler.block2.vel0 = -1

dyn_integloop.getIntegrator(trick.Euler, 2) #Adding a third timestep parameter does not work.

trick.stop(1000000) 