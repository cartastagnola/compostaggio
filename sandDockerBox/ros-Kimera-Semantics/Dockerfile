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
                    autoconf libtool automake \
                    cmake build-essential zip pkg-config autoconf \
                    tmux vim-gtk3 \
                    libboost-all-dev \
                    libjpeg-dev libpng-dev libtiff-dev \
                    libvtk6-dev libgtk-3-dev \
                    libatlas-base-dev gfortran \
                    libparmetis-dev \
                    python-wstool python-catkin-tools

RUN apt-get install -y autoconf libtool automake mesa-utils wget

# Dependencies for glvnd and X11 and nvidia stuffs
RUN apt-get update \
  && apt-get install -y -qq --no-install-recommends \
    libglvnd0 \
    libgl1 \
    libglx0 \
    libegl1 \
    libxext6 \
    libx11-6 \
  && rm -rf /var/lib/apt/lists/*# Env vars for the nvidia-container-runtime.
ENV NVIDIA_VISIBLE_DEVICES all
ENV NVIDIA_DRIVER_CAPABILITIES graphics,utility,compute

# option GSTAM
RUN apt-get install -y libtbb-dev

ENV DIRPATH /root
WORKDIR $DIRPATH

# Kimera semantics OS wrapper Installation
# Setup catkin workspace
RUN mkdir -p $DIRPATH/catkin_ws/src && \
        cd $DIRPATH/catkin_ws/  && \
        catkin init && \
        catkin config --extend /opt/ros/melodic && \
        catkin config --cmake-args -DCMAKE_BUILD_TYPE=Release && \
        catkin config --merge-devel 

# Add workspace to bashrc for automatic sourcing of workspace.
RUN echo 'source $DIRPATH/catkin_ws/devel/setup.bash' >> ~/.bashrc

# Clone repo
WORKDIR $DIRPATH/catkin_ws/src
RUN git clone https://github.com/MIT-SPARK/Kimera-Semantics.git
RUN wstool init
RUN wstool merge Kimera-Semantics/install/kimera_semantics_https.rosinstall
RUN wstool update

RUN /bin/bash -c "source /opt/ros/melodic/setup.bash ;\
                  cd /root/catkin_ws/src ;\
                  catkin build kimera_semantics_ros"

ARG CACHEBUST=1 
WORKDIR $DIRPATH/catkin_ws/src/Kimera-Semantics/kimera_semantics_ros/rosbags
# import the ros bag to do the test
RUN wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate 'https://docs.google.com/uc?export=download&id=1SG8cfJ6JEfY2PGXcxDPAMYzCcGBEh4Qq' -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')&id=1SG8cfJ6JEfY2PGXcxDPAMYzCcGBEh4Qq" -O 'kimera_semantics_demo.bag' && rm -rf /tmp/cookies.txt

#### add kimera-VIO
WORKDIR $DIRPATH

# KimeraVIO ROS wrapper Installation
# Setup catkin workspace

# Clone repo
WORKDIR $DIRPATH/catkin_ws/src
RUN git clone https://github.com/MIT-SPARK/Kimera-VIO-ROS.git
RUN wstool merge -y Kimera-VIO-ROS/install/kimera_vio_ros_https.rosinstall
RUN wstool update

RUN /bin/bash -c "source /opt/ros/melodic/setup.bash ;\
                  cd /root/catkin_ws/src ;\
                  catkin build"

WORKDIR $DIRPATH
ADD ros-tmux.sh /$DIRPATH/ros-tmux.sh

# Refresh workspace
#RUN source ~/catkin_ws/devel/setup.bash 


