# xterm  -e  " source /opt/ros/kinetic/setup.bash; roscore" & 
# sleep 3
xterm  -e  "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/RoboND-HomeServiceRobot/src/world/lolo_enhanced.world" &
sleep 11
xterm  -e  "source devel/setup.bash; roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/RoboND-HomeServiceRobot/src/world/lolo_enhanced_map.yaml initial_pose_a:=-1.5707" &
sleep 4
# xterm  -e  "source devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
xterm  -e  "source devel/setup.bash; rviz -d /home/workspace/RoboND-HomeServiceRobot/src/rvizConfig/rviz_cfg.rviz" &
sleep 10
xterm  -e  "source devel/setup.bash; rosrun add_markers add_markers" &