Using the robot
---------------

Parts :

- the "electronic box", which is turned on via the power outlet
- the pressure valve (against the wall). Horizontal means close
- the emergency stop button, which blocks the pressure
- the control software server (pam_interface or o80_pam)

Warning :

What is to be avoided is to have the pressure applied to the robot when the electronic box is off, or the electronic box is on but the fpga has not been initialized (the fpga is initialized by the control software server). The electronic box and the server ensure that the pressure applied to the robot is limited. If the robot is exposed to the pressure while the electronic box is off or the fpga has not been initialized, the maximal pressure will be applied to it and damage may occur.
-> applying the pressure is always the last thing to do <-

What to do when in doubt :
Press the emergency button.

Starting state:

- power outlet off
- emergency button pressed
- pressure valve closed (horizontal)
- 4th degree of freedom of the robot "aligned" (silver paint marking aligned with zero)

Starting steps:

 1. Start electronic box (switch power outlet on)
 2. Start server (pam_interface or o80_pam)
 3. Turn on pressure on valve (vertical), pressures should reach their minimum value as set in the used json configuration file.
 4. Release emergency button
 5. Observe robot. A short motion (i.e. half a second) should be observed.
                   If the robot keeps moving, press emergency button.

Stopping steps:

1. Stop server (software has pressure decrease on exit)
2. Press emergency button
3. Close pressure supply valve
5. Turn off electronics
