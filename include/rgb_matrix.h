#ifndef RGB_MATRIX_H
#define RGB_MATRIX_H

#include "matrix.h"


class RGBMatrix: public Matrix
{

    public:
    RGBMatrix();
    RGBMatrix(size_t row,size_t col);
    RGBMatrix(size_t row,size_t col,size_t initvalue);
    RGBMatrix(const RGBMatrix &m);
    RGBMatrix(const Matrix &m);

    void fromOpencv(const cv::Mat &m);
    cv::Mat toOpencv();
    bool  readImage(const std::string &path);
    void display();

    
     //operations on matrix
    RGBMatrix add(int val);
    RGBMatrix substract(int val);
    RGBMatrix multiply(int val);

    RGBMatrix operator+(const int &val);
    RGBMatrix operator-(const int &val);
    RGBMatrix operator*(const int &val);

    void print() const;
    void save_image();
    RGBMatrix operator=(const Matrix &m)
    {
        RGBMatrix res(m);
        return res;
    }
    friend std::ostream& operator<<(std::ostream& out,const RGBMatrix& mat);
};
#endif