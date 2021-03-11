FROM ubuntu:18.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update && \
    apt-get upgrade -y

RUN apt-get install -y software-properties-common apt-utils
RUN apt-get install -y vim build-essential cmake make
RUN apt-get install -y octave i2c-tools
RUN apt-get install -y git libqt4-dev

ENV DIRPATH /root
WORKDIR $DIRPATH

RUN git clone https://github.com/RPi-Distro/RTIMULib.git && \
    cd RTIMULib && \
    mkdir build && cd build && \
    cmake ../RTIMULib && \
    make -j4 && \
    make install && \
    ldconfig

# script to test the IMU
RUN git clone https://github.com/cartastagnola/compostaggio.git
RUN cd compostaggio && mkdir build && cd build && \
    cmake .. && \
    make
    
#RUN apt-get install -y sense-hat octave i2c-tools
