#!/bin/sh

xterm -e "export ROBOT_INITIAL_POSE='-x 2 -y 1 -Y 3'; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/worlds/myWorld.world" &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/maps/map.yaml initial_pose_x:=1.0 initial_pose_y:=-2.0 initial_pose_a:=1.57" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "rosrun add_markers add_markers" &
sleep 10
xterm -e "rosrun pick_objects pick_objects"

