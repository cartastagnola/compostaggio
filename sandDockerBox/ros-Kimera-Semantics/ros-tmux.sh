#!/bin/bash 

SESSIONNAME="kimera"
tmux has-session -t $SESSIONNAME &> /dev/null

if [ $? != 0 ]
 then
    tmux -2 new-session -d -s $SESSIONNAME -n roscore
    tmux send-keys -t $SESSIONNAME "roscore" C-m

    sleep 1
    tmux new-window -t $SESSIONNAME:1 -n rviz
    tmux send-keys -t $SESSIONNAME 'rviz -d $(rospack find kimera_semantics_ros)/rviz/kimera_semantics_gt.rviz' C-m

    sleep 1
    tmux new-window -t $SESSIONNAME:2 -n semantics
    tmux send-keys -t $SESSIONNAME 'roslaunch kimera_semantics_ros kimera_semantics.launch' C-m

    sleep 1
    tmux new-window -t $SESSIONNAME:3 -n rosbag
    tmux send-keys -t $SESSIONNAME 'rosbag play /root/catkin_ws/src/Kimera-Semantics/kimera_semantics_ros/rosbags/kimera_semantics_demo.bag --pause --clock --rate 2' C-m
    sleep 1
fi

tmux attach-session -t $SESSIONNAME

