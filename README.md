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

Here is how PID components (for steering angle) affect the trajectory (source: http://www.udacity.com/):

<img src="https://github.com/SergeiDm/CarND-PID-Controller/blob/master/illustrations/PID.png" width="400" height="300"/>

P component creates periodic fluctuations, D component decreases them. At the same time I component is used for overcoming biases (for example a steering wheel has inappropriate adjustment).

In this project, manual series tuning was used for finding appropriate hyperparameters for PID components. Firstly for P component, after   testing that steering angle values were anough for keeping the vehicle on the track, hyperparameter for D was tuned in order to decrease periodic fluctuations. Finally, hyperparameter for I component was chosen according to making better staying the vehicle on the track. The final hyperparameters values are 0.06, 0.05, 0.06.

Hyperparameters for PID controller for speed were chosen according to the results how fast the vehicle can move on the track.
The final values are 0.4, 0, 0.1.

## Project result
Here is the result video of this project:

<a href="https://youtu.be/2VPTpG9AUoQ" target="_blank"><img src="http://img.youtube.com/vi/2VPTpG9AUoQ/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>
