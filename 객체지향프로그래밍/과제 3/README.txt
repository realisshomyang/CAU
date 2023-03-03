20193802 조명근
OS type : MS-windows 11 OS
compile from visual studio 2022

HOW TO EXECUTE
1. move directory into oop_proj3 and choose virtualleog.sln press ctrl f5 to run program
2. execute Virtuallego.exe

HOW TO PLAY
press SPACE key to start the game
You can control green ball, green ball is cursor. greenball can be moved by when the right mouse clicked.

WHAT I MODIFY

----CSphere class----
i added isblue member variable that describingwhat type of the object CSphere is.
In isintersected function, compared absolute value coordinates of targetball and yellow ball(moving ball) that is smaller than 2*radius. 
In hitby function, Hitby calculates the bounce angle based on the angle between the ball and the ball, depending on the quadrant that collides with it. 
In addition, the isblue meber variable was used to operate in different cases depending on whether it was a yellow ball or a blue ball.

----Cwall class----
The cwall class adds the wall number as a member variable.
In the isintersected function, it is configured to be false if the billiard ball is within the moving range (green range) and true if the billiard ball is above the moving range.
Hitby reverses the x-coordinate speed of the left and right walls at the moment it hits, and reverses the z-coordinate at the moment it hits the top.

----Callback function----
In the callback function, the specific part of the mousemove part has been deleted so that the screen can be fixed so that it does not rotate.
Also, the movement of the green ball was fixed left and right with mousemove. Also, the situation of moving left to right has been added so that it works based on the shootflag.




