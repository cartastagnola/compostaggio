# Use an official Python runtime as a parent image
#FROM osrf/ros:noetic-desktop-full
FROM osrf/ros:melodic-desktop-full

MAINTAINER the bros "thebros@mit.edu"

# To avoid tzdata asking for geographic location...
ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && apt-get upgrade -y
#RUN apt-get install -y software-properties-common 
#RUN add-apt-repository universe
#RUN add-apt-repository multiverse

# ros non-default dependencies (change melodic for other distribution
#RUN apt-get install -y ros-noetic-image-geometry \
#                        ros-noetic-pcl-ros ros-noetic-cv-bridge
RUN apt-get install -y ros-melodic-image-geometry \
                        ros-melodic-pcl-ros ros-melodic-cv-bridge
                        
RUN apt-get install -y --no-install-recommends apt \
                    cmake build-essential zip pkg-config autoconf \
                    tmux vim-gtk3 \
                    libboost-all-dev \
                    libjpeg-dev libpng-dev libtiff-dev \
                    libvtk6-dev libgtk-3-dev \
                    libatlas-base-dev gfortran \
                    libparmetis-dev \
                    python-wstool python-catkin-tools

# option GSTAM
RUN apt-get install -y libtbb-dev

ENV DIRPATH /root
WORKDIR $DIRPATH

# KimeraVIO ROS wrapper Installation
# Setup catkin workspace
RUN mkdir -p $DIRPATH/catkin_ws/src && \
        cd $DIRPATH/catkin_ws/  && \
        catkin init && \
        catkin config --cmake-args -DCMAKE_BUILD_TYPE=Release && \
        catkin config --merge-devel 

# Add workspace to bashrc for automatic sourcing of workspace.
RUN echo 'source $DIRPATH/catkin_ws/devel/setup.bash' >> ~/.bashrc

# Clone repo
WORKDIR $DIRPATH/catkin_ws/src
RUN git clone https://github.com/MIT-SPARK/Kimera-VIO-ROS.git
RUN wstool init
RUN wstool merge Kimera-VIO-ROS/install/kimera_vio_ros_https.rosinstall
RUN wstool update

RUN apt-get install -y autoconf libtool automake
RUN pwd
RUN /bin/bash -c "source /opt/ros/melodic/setup.bash ;\
                  cd /root/catkin_ws/src ;\
                  catkin build"


# Refresh workspace
#RUN source ~/catkin_ws/devel/setup.bash 


