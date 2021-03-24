////////////////////////////////////////////////////////////////////////////
//
//  This file is part of RTIMULib
//
//  Copyright (c) 2014-2015, richards-tech, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
//  Software, and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include "RTIMULib.h"
#include <fstream>
#include <iostream>

int main()
{
    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;

    //  Using RTIMULib here allows it to use the .ini file generated by RTIMULibDemo.
    //  Or, you can create the .ini in some other directory by using:
    //      RTIMUSettings *settings = new RTIMUSettings("<directory path>", "RTIMULib");
    //  where <directory path> is the path to where the .ini file is to be loaded/saved

    RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

    RTIMU *imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("No IMU found\n");
        exit(1);
    }

    //  This is an opportunity to manually override any settings before the call IMUInit

    //  set up IMU

    imu->IMUInit();

    //  this is a convenient place to change fusion parameters

    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);

    //  set up for rate timer

    rateTimer = displayTimer = RTMath::currentUSecsSinceEpoch();

    // output logging data
    FILE * pLogAcc;
    pLogAcc = fopen("pLogAcc.txt", "a");
    fprintf(pLogAcc, "init\n");
    fclose (pLogAcc);
    FILE * pLogGyro;
    pLogGyro = fopen("pLogGyro.txt", "a");
    fprintf(pLogGyro, "init\n");
    fclose (pLogGyro);
    FILE * pLogComp;
    pLogComp = fopen("pLogComp.txt", "a");
    fprintf(pLogComp, "init\n");
    fclose (pLogComp);
    FILE * pLogTot;
    pLogTot = fopen("pLogTot.txt", "a");
    fprintf(pLogTot, "init\n");
    fclose (pLogTot);

    //  now just process data

    while (1) {
        //  poll at the rate recommended by the IMU

        usleep(imu->IMUGetPollInterval() * 1000);

        while (imu->IMURead()) {
            RTIMU_DATA imuData = imu->getIMUData();
            sampleCount++;

            now = RTMath::currentUSecsSinceEpoch();

            //  display 10 times per second

            if ((now - displayTimer) > 100000) {
		    ////////////// logging /////////////////
		    printf("Sample rate %d: %s\r", sampleRate, RTMath::displayDegrees("", imuData.fusionPose));
		    printf("RAW data?\n");

		    pLogTot = fopen("pLogTot.txt", "a");
		    // acceleration
		    pLogAcc = fopen("pLogAcc.txt", "a");
		    fprintf(pLogAcc, "accel x; %f, y: %f, z: %f \n", imuData.accel.x(), imuData.accel.y(), imuData.accel.z());
		    fprintf(pLogTot, "accel x; %f, y: %f, z: %f   ", imuData.accel.x(), imuData.accel.y(), imuData.accel.z());
		    printf("accel x; %f, y: %f, z: %f \n", imuData.accel.x(), imuData.accel.y(), imuData.accel.z());
		    fclose (pLogAcc);
		   
		    // compass
		    pLogGyro = fopen("pLogComp.txt", "a");
		    fprintf(pLogComp, "compass x; %f, y: %f, z: %f \n", imuData.compass.x(), imuData.compass.y(), imuData.compass.z());
		    fprintf(pLogTot, "compass x; %f, y: %f, z: %f   ", imuData.compass.x(), imuData.compass.y(), imuData.compass.z());
		    printf("compass x; %f, y: %f, z: %f \n", imuData.compass.x(), imuData.compass.y(), imuData.compass.z());
		    fclose(pLogComp);

		    // gyro
		    pLogGyro = fopen("pLogGyro.txt", "a");
		    fprintf(pLogGyro, "gyro x; %f, y: %f, z: %f \n", imuData.gyro.x(), imuData.gyro.y(), imuData.gyro.z());
		    fprintf(pLogTot, "gyro x; %f, y: %f, z: %f   ", imuData.gyro.x(), imuData.gyro.y(), imuData.gyro.z());
		    printf("gyro x; %f, y: %f, z: %f \n", imuData.gyro.x(), imuData.gyro.y(), imuData.gyro.z());
		    fclose(pLogGyro);
		    

		    fflush(stdout);
		    displayTimer = now;
            }

            //  update rate every second

            if ((now - rateTimer) > 1000000) {
                sampleRate = sampleCount;
                sampleCount = 0;
                rateTimer = now;
            }
        }
    }
    
}

