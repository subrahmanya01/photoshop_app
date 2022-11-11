#ifndef MATRIX_H

#define MATRIX_H

#include<vector>
#include<ostream>
#include<opencv2/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>

class Matrix
{
  protected:
  size_t m_rows;
  size_t m_cols;
  size_t channels;
  std::vector<int> mat;

  protected:
   //For the purpose of abstarction
   void add(Matrix &res,int val) const;
   void substract(Matrix &res,int val) const;
   void multiply(Matrix &res,int val) const;
   
  public:
  //constructors
  Matrix(): m_rows(0),m_cols(0),channels(0){}
  Matrix(size_t row,size_t col,size_t chan);
  Matrix(size_t row,size_t col,size_t chan,int initvalue);
  Matrix(const Matrix &m);

  //for getting the size of matrix
  size_t get_Rows() const {return m_rows;}
  size_t get_Cols() const {return m_cols;}
  size_t get_Channels() const {return channels;}

  //for getting and making changes to the matrix values
  int& at(size_t row,size_t col,size_t channels);

  void fromOpencv(const cv::Mat &m);
  cv::Mat toOpencv();
  bool  readImage(const std::string &path);
  void display();

//   //operations on matrix
  Matrix add(int val);
  Matrix substract(int val);
  Matrix multiply(int val);
  

  Matrix add(Matrix m);
  Matrix substract(Matrix m);
  Matrix multiply(Matrix m);

  Matrix operator+(const int &val);
  Matrix operator+(const Matrix &m);
  Matrix operator-(const int &val);
  Matrix operator-(const Matrix &m);
  Matrix operator*(const int &val);
  Matrix operator*(const Matrix &m);

  //for displaying matrix
  virtual void print();
  friend std::ostream& operator<<(std::ostream& out,const Matrix& mat);

  //operations
  void rotate_left();
  void horizontal_flip();
  void vertical_flip();
  void contrast(int val);
  void border(int border_width,std::vector<int> color);

};

#endif