#ifndef BW_MATRIX_H
#define BW_MATRIX_H

#include "matrix.h"

class BWMatrix: public Matrix
{

    public:
    BWMatrix();
    BWMatrix(size_t row,size_t col);
    BWMatrix(size_t row,size_t col,size_t initvalue);
    BWMatrix(const BWMatrix &m);

    void fromOpencv(const cv::Mat &m);
    cv::Mat toOpencv();
    bool  readImage(const std::string &path);

    
    //operations on matrix
    BWMatrix add(int val);
    BWMatrix substract(int val);
    BWMatrix multiply(int val);

    BWMatrix operator+(const int &val);
    BWMatrix operator-(const int &val);
    BWMatrix operator*(const int &val);

    void print() const;
    void save_image(string imagePath);
    void display();
    friend std::ostream& operator<<(std::ostream& out,const BWMatrix& mat);
};
#endif