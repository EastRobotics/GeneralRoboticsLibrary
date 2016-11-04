# GeneralRoboticsLibrary
General Toolbox of Routines that can be reused


Notes for VEX RobotC Coding and Code simplification

Using #defines
You can use C Compiler #define Directive to simplify your code and make it much more readable.
the directive allows you to replace blocks of code with simpler code.  Then when the compiler sees the #defined item it simply replaces it with the original code.  The example below defines rf, rb, lf and lb as four motors.  In your code you can now use these in the same way you would use motor[xFront].  For example rf = 60 sets the motor speed to 60 just as motor[rFront] = 60 would, and is a lot less typing.
You can then reuse those to create more complex defines like mtrs rb=lb=lf=rf.  When the compiler sees this it would substitute back in motor[rBack]=motor[lBack]=motor=[lFront]=motor[rFront], thus if you say mtrs = 60 it would set all of your motors to power level 60.

 #define rf motor[rFront]
 
 #define rb motor[rBack]
 
 #define lf motor[lFront]
 
 #define lb motor[lBack]
 
 #define mtrs rb=lb=lf=rf
