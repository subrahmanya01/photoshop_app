#include "rgb_matrix.h"
#include<iostream>
#include<iomanip>
#include<vector>

RGBMatrix::RGBMatrix() : Matrix(0, 0, 3)
{
}
RGBMatrix::RGBMatrix(size_t row, size_t col) : Matrix(row, col, 3,0)
{
}
RGBMatrix::RGBMatrix(size_t row, size_t col, size_t initvalue) : Matrix(row, col, 3, initvalue)
{
}
RGBMatrix::RGBMatrix(const RGBMatrix &m) : Matrix(m)
{
}
RGBMatrix::RGBMatrix(const Matrix &m) : Matrix(m)
{
}

void RGBMatrix::print() const
{
    std::vector<char> channel_indicator={'R','G','B'};
    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            std::cout << "[";
            for (int ch = 0; ch < channels; ch++)
                std::cout <<channel_indicator[ch]<<":"<<mat[r * m_cols * channels + c * channels + ch] << " ";
            std::cout << "] ";
        }
        std::cout << std::endl;
    }
}

std::ostream& operator<<(std::ostream& out,const RGBMatrix& m)
{
    std::vector<char> channel_indicator={'R','G','B'};
    for(int r=0;r<m.m_rows;r++)
    {
        for(int c=0;c<m.m_cols;c++)
        {
            out<<"[";
            for(int ch=0;ch<m.channels;ch++)
            out<<channel_indicator[ch]<<":"<<m.mat[r*m.m_cols*m.channels+c*m.channels+ch]<<" ";
            out<<"] ";
        }
        std::cout<<std::endl;
    }

    return out;
}

    RGBMatrix RGBMatrix:: add(int val)
    {
        RGBMatrix res(m_rows,m_cols);
        Matrix::add(res,val);
        return res;
    }
    RGBMatrix RGBMatrix:: substract(int val)
    {
        RGBMatrix res(m_rows,m_cols);
        Matrix::substract(res,val);
        return res;
    }
    RGBMatrix RGBMatrix:: multiply(int val)
    {
        RGBMatrix res(m_rows,m_cols);
        Matrix::multiply(res,val);
        return res;
    }
   
    RGBMatrix RGBMatrix:: operator+(const int &val)
    {
        return add(val);
    }
    RGBMatrix RGBMatrix:: operator-(const int &val)
    {
        return substract(val);
    }
    RGBMatrix RGBMatrix:: operator*(const int &val)
    {
        return multiply(val);
    }


void RGBMatrix:: fromOpencv(const cv::Mat &m)
{
    m_rows=m.rows;
    m_cols=m.cols;
    channels=3;
    mat.resize(m.total()*channels);
    
    for(size_t r=0;r<m_rows;r++)
    {
      for(size_t c=0;c<m_cols;c++)
      {
         auto val=m.at<cv::Vec3b>(r,c);
         at(r,c,0)=val[2];
         at(r,c,1)=val[1];
         at(r,c,2)=val[0];
      }
    }
}
cv::Mat RGBMatrix:: toOpencv()
{
    cv::Mat res(m_rows,m_cols,CV_8UC3);
    for(size_t r=0;r<m_rows;r++)
    {
      for(size_t c=0;c<m_cols;c++)
      {
        cv::Vec3b val={0,0,0};
        val[0]=at(r,c,2);
        val[1]=at(r,c,1);
        val[2]=at(r,c,0);
        res.at<cv::Vec3b>(r,c)=val;
      }
    }
    return res;

}
bool RGBMatrix::readImage(const std::string &path)
{
   cv::Mat colorimage=cv::imread(path,cv::IMREAD_COLOR);
   
   if(colorimage.empty())
   {
      std::cout<<"There is invalid image\n";
      return false;
      exit(0);
   }

   fromOpencv(colorimage);
   return true;

}
void RGBMatrix:: display()
{
   cv::imshow("image display",toOpencv());
   cv::waitKey(0);
}

void RGBMatrix::save_image()
{
   cv::imwrite("D:\\Projects\\OOPS Project\\output\\output.jpg",toOpencv());
}