#!/bin/bash

# Allow X server connection
xhost +local:root
docker run -it --rm \
    --gpus device=0 \
    --env="DISPLAY" \
    --env="QT_X11_NO_MITSHM=1" \
    --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
    --volume="/home/arcblock:/home/host" \
    --privileged \
    --net=host \
    ros-kimera-semantics bash 
# Disallow X server connection
xhost -local:root

#docker run --rm -it --gpus all -v /home/arcware/:/root -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=$DISPLAY -e QT_X11_NO_MITSHM=1 cslam
