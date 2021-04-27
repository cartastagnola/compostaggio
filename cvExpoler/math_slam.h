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

v3
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

struct
mX
{
    Eigen::Matrix matX;
};

// Matrix need a dimension i think, I need something diferent like MatixXf, but I have to find the right map function
mX
MX(int rows, int columns, double * mat_data)
{
    mX result;
    //Eigen::MatrixXf mat;
    //Eigen::Map<Eigen::MatrixXf> mat(mat_data, rows, columns);
    Eigen::Map<Eigen::Matrix<double, rows, columns> > mat(mat_data, rows, columns);
    //Eigen::Map<MatrixXf<double,row,column> > mat(mat_data);
    result.matX = mat;
    return(matX);
}

//follow the make tutorial
//https://cs.colby.edu/maxwell/courses/tutorials/maketutor/

