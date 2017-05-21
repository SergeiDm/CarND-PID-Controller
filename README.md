# CarND-PID-Controller
## Project Description
In this project PID (P-proportional, I-integral, D-differential) controller is applied to maneuver the vehicle around the track.
PID controller based on the cross track error (CTE) which is provided by [a car simulator](https://github.com/udacity/CarND-PID-Control-Project/releases).

## Project files
The project includes the following folder/files:
- src - the folder with c++ files with PID controller implementation.
- CMakeLists.txt - the file for building program.
- illustrations - the folder with pictures for README.md.

## Dependencies
For communication between the car simulator and the project, [uWebSockets == 0.13](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) should be used.

## Project explanation
In this project 2 PID controllers were applied:
- for steering angle. This PID is directly proprotional:

  - CTE
  - CTE change rate
  - Sum (integral) of CTE over time
It means the more CTE, the more steering angle.
- for speed (velocity). The PID is inversely proportional absolute values of the same things mentioned in previous PID. So, the more CTE, the less velocity. This is because a big value of CTE means increasing steering angle, so for staying on the track the velocity should be decreased.

Here is how PID components affect the trajectory (source: http://www.udacity.com/):

<img src="https://github.com/SergeiDm/CarND-PID-Controller/blob/master/illustrations/PID.png" width="500" height="400"/>


Describe the effect each of the P, I, D components had in your implementation.
Student describes the effect of the P, I, D component of the PID algorithm in their implementation. Is it what you expected?
Visual aids are encouraged, i.e. record of a small video of the car in the simulator and describe what each component is set to.

Describe how the final hyperparameters were chosen.
Student discusses how they chose the final hyperparameters (P, I, D coefficients). This could be have been done through manual tuning, twiddle, SGD, or something else, or a combination!

## Project result
Here is the result video of this project:

<a href="https://youtu.be/2VPTpG9AUoQ" target="_blank"><img src="http://img.youtube.com/vi/2VPTpG9AUoQ/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>
