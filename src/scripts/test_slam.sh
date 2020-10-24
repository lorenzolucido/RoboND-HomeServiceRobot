#!/bin/sh

# Make files
# ../catkin_make
# source ../devel/setup.bash

xterm  -e  " gazebo " &
sleep 3
xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
sleep 3
xterm  -e  " rosrun rviz rviz" 
sleep 3
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch" &
sleep 3
xterm  -e  " roslaunch turtlebot_teleop keyboard_teleop.launch" &
sleep 3
xterm  -e  " roslaunch turtlebot_navigation gmapping_demo.launch" &
sleep 3
xterm  -e  " roslaunch turtlebot_rviz_launchers view_navigation.launch" &
