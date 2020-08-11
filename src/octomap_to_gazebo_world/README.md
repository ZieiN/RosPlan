# octomap_to_gazebo_world

# Installation
Clone this directory into your catkin_ws/src folder. Then run catkin_make install followed by resourcing your catkin_ws/devel/setup.bash file

# Usage
An example of how to use this program can be found in the run.sh file
Basically you need to provide a occupancy grid map in the form of a grid.txt file and a grid.yaml file (with the same name).
Examples are provided in the Maps folder.

Then just run
# To create the .world file:
roslaunch octomap_to_gazebo generate_world_and_contours.launch 

# To view the world in Gazebo run:
roslaunch octomap_to_gazebo launch_gazebo_world.launch world:=(name of world file).world
