#include <iostream>
#include <cmath>

// eigen
#include <Eigen/Dense>
#include <Eigen/SVD>


// mat stuffs

struct
v3
{
    Eigen::Vector3d vec;
};

struct
m3
{
    Eigen::Matrix3d mat;
};

inline v3
V3(double x, double y, double z)
{
    v3 result;
    Eigen::Vector3d vec(x,y,z);
    result.vec = vec;
    return(result);
}

double
Dot(v3 A, v3 B)
{
    double result;
    result = A.vec.transpose() * B.vec;
    return(result);
}

//follow the make tutorial
//https://cs.colby.edu/maxwell/courses/tutorials/maketutor/

