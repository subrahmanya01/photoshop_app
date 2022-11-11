#include "bw_matrix.h"
#include<iostream>
#include<iomanip>
#include<vector>

BWMatrix::BWMatrix() : Matrix(0, 0, 1)
{
}
BWMatrix::BWMatrix(size_t row, size_t col) : Matrix(row, col, 1)
{
}
BWMatrix::BWMatrix(size_t row, size_t col, size_t initvalue) : Matrix(row, col, 1, initvalue)
{
}
BWMatrix::BWMatrix(const BWMatrix &m) : Matrix(m)
{
}

void BWMatrix::print() const
{
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            std::cout << "[";
            for (int ch = 0; ch < channels; ch++)
                {
                    std::cout <<mat[r * m_cols * channels + c * channels + ch];
                }
            std::cout <<"] ";
        }
        std::cout << std::endl;
    }
}

std::ostream& operator<<(std::ostream& out,const BWMatrix& m)
{
    
    for(int r=0;r<m.m_rows;r++)
    {
        for(int c=0;c<m.m_cols;c++)
        {
            out<<"[";
            for(int ch=0;ch<m.channels;ch++)
            out<<m.mat[r*m.m_cols*m.channels+c*m.channels+ch]<<" ";
            out<<"] ";
        }
        std::cout<<std::endl;
    }

    return out;
}

BWMatrix BWMatrix:: add(int val)
    {
        BWMatrix res(m_rows,m_cols);
        Matrix::add(res,val);
        return res;
    }
    BWMatrix BWMatrix:: substract(int val)
    {
        BWMatrix res(m_rows,m_cols);
        Matrix::substract(res,val);
        return res;
    }
    BWMatrix BWMatrix:: multiply(int val)
    {
        BWMatrix res(m_rows,m_cols);
        Matrix::multiply(res,val);
        return res;
    }
   
    BWMatrix BWMatrix:: operator+(const int &val)
    {
        return add(val);
    }
    BWMatrix BWMatrix:: operator-(const int &val)
    {
        return substract(val);
    }
    BWMatrix BWMatrix:: operator*(const int &val)
    {
        return multiply(val);
    }


void BWMatrix:: fromOpencv(const cv::Mat &m)
{
    m_rows=m.rows;
    m_cols=m.cols;
    channels=1;
    mat.resize(m.total());
    
    for(size_t r=0;r<m_rows;r++)
    {
      for(size_t c=0;c<m_cols;c++)
      {
         at(r,c,0)=m.at<uchar>(r,c);
      }
    }
}
cv::Mat BWMatrix:: toOpencv()
{
    cv::Mat res(m_rows,m_cols,CV_8UC1);
    for(size_t r=0;r<m_rows;r++)
    {
      for(size_t c=0;c<m_cols;c++)
      {
         res.at<uchar>(r,c)=at(r,c,0);
      }
    }
    return res;

}
bool BWMatrix::readImage(const std::string &path)
{
   cv::Mat bwimage=cv::imread(path,cv::IMREAD_GRAYSCALE);
   
   if(bwimage.empty())
   {
      std::cout<<"There is invalid image\n";
      return false;
      exit(0);
   }
   
   fromOpencv(bwimage);
   return true;
}
void BWMatrix:: display()
{
   cv::imshow("image display",toOpencv());
   cv::waitKey(0);
}

void BWMatrix::save_image()
{
   cv::imwrite("D:\\Projects\\OOPS Project\\output\\output.jpg",toOpencv());
}