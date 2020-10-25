#!/bin/sh

# Make files
# ../catkin_make
# source ../devel/setup.bash

# xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
# sleep 3
xterm  -e  "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/RoboND-HomeServiceRobot/src/world/lolo_enhanced.world" &
sleep 11
xterm  -e  "source devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch" &
sleep 4
xterm  -e  "source devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch" &
sleep 4
xterm  -e  "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
