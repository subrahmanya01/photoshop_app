#include "matrix.h"
#include<iostream>
#include<iomanip>
#include<exception>
#include<valarray>

Matrix::Matrix(size_t row,size_t col,size_t chan)
{
    m_cols=col;
    m_rows=row;
    channels=chan;
    for(int i=0;i<m_cols*m_rows*channels;i++)
    {
        mat.push_back(0);
    }
}

Matrix::Matrix(size_t row,size_t col,size_t chan,int initvalue)
{
    m_rows=row;
    m_cols=col;
    channels=chan;
    for(int i=0;i<row*col*chan;i++)
    mat.push_back(initvalue);
}

Matrix::Matrix(const Matrix &m): m_rows(m.m_rows), m_cols(m.m_cols) ,channels(m.channels)
{
    for(int i=0;i<m_cols*m_rows*channels;i++)
    mat.push_back(0);
    for(int i=0;i<m_cols*m_rows*channels;i++)
    mat[i]=m.mat[i];
}

void Matrix::print()
{
    for(int r=0;r<m_rows;r++)
    {
        for(int c=0;c<m_cols;c++)
        {
            std::cout<<"[";
            for(int ch=0;ch<channels;ch++)
            std::cout<<mat[r*m_cols*channels+c*channels+ch]<<" ";
            std::cout<<"] ";
        }
        std::cout<<std::endl;
    }

}

 int& Matrix:: at(size_t row,size_t col,size_t chan)
  { 
        return mat[row*m_cols*channels+col*channels+chan];
  
  }

  void Matrix::add(Matrix &res,int val) const
  {
    for(int i=0;i<mat.size();i++)
     res.mat[i]=mat[i]+val;
  }
  void Matrix::substract(Matrix &res,int val) const
  {
    for(int i=0;i<mat.size();i++)
     res.mat[i]=mat[i]-val;
  }
  void Matrix::multiply(Matrix &res,int val) const
  {
    for(int i=0;i<mat.size();i++)
     res.mat[i]=mat[i]*val;
  }
  Matrix Matrix::add(int val)
  {
    Matrix res(m_rows,m_cols,channels,0);
    add(res,val);
     return res;
  }
  Matrix Matrix::substract(int val)
  {
    Matrix res(m_rows,m_cols,channels,0);
    substract(res,val);
    return res;
  }
  Matrix Matrix::multiply(int val)
  {
    Matrix res(m_rows,m_cols,channels,0);
    multiply(res,val);
     return res;
  }

  Matrix Matrix:: add(Matrix m)
  {
    Matrix res(m_rows,m_cols,channels,0);
    try
    {
       if((m_cols!=m.m_cols) || (m_rows!=m.m_rows)||(channels!=m.channels))
       {
        throw "Invalid matrix size";
       }
       for(int i=0;i<mat.size();i++)
       {
          res.mat[i]=m.mat[i]+mat[i];
       }
    }
    catch(const char* str)
    {
      std::cout<<str<<std::endl;
      exit(0);
    }
    return res;
  }
  Matrix Matrix:: substract(Matrix m)
  {
    Matrix res(m_rows,m_cols,channels,0);
    try
    {
       
       if((m_cols!=m.m_cols) || (m_rows!=m.m_rows)||(channels!=m.channels))
       throw "Invalid matrix size";
       
       
       for(int i=0;i<mat.size();i++)
       {
          res.mat[i]=mat[i]-m.mat[i];
       }
       

    }
    catch(const char* str)
    {
      
      std::cout<<str<<std::endl;
      exit(0);
    }
    return res;
  }
  Matrix Matrix:: multiply(Matrix m)
  {
    Matrix res(m_rows,m_cols,channels,0);
     try
     {
        if(m_cols !=m.m_rows || channels!=m.channels)
        throw "Matrix multiplication not possible due to invalid dimension\n";

        for(int ch=0;ch<channels;ch++)
        {
        for(int i=0;i<m_rows;i++)
        {
            for(int j=0;j<m.m_cols;j++)
            {
                for(int k=0;k<m_cols;k++)
                {
                    res.at(i,j,ch)+=mat[i*m_cols*channels+j*channels+ch]*m.at(k,j,ch);
                }
            }
        }
        }

     }
     catch(const char* str)
     { 
        std::cout<<str;
        exit(0);
     }
    return res;

  }

 Matrix Matrix:: operator+(const int &val)
 {
    return add(val);
 }
 Matrix Matrix:: operator+(const Matrix &m)
 {
    return add(m);
 }
 Matrix Matrix:: operator-(const int &val)
 {
    return substract(val);
 }
 Matrix Matrix:: operator-(const Matrix &m)
 {
    return substract(m);
 }
 Matrix Matrix:: operator*(const int &val)
 {
    return multiply(val);
 }
 Matrix Matrix:: operator*(const Matrix &m)
 {
    return multiply(m);
 }

std::ostream& operator<<(std::ostream& out,const Matrix &m)
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

void Matrix::rotate_left()
{
   Matrix mt(m_cols,m_rows,channels,0);
   for(int c=m_cols-1;c>=0;c--)
   {
      for(int r=0;r<m_rows;r++)
      {     
         for(int ch=0;ch<channels;ch++) 
            mt.at(m_cols-c-1,r,ch)=at(r,c,ch);
      }
   }
   std::swap(m_cols,m_rows);
   this->mat=mt.mat;

}
void Matrix::horizontal_flip()
{
   for(int r=0;r<m_rows;r++)
   {
      for(int c=0;c<m_cols/2;c++)
      {
         for(int ch=0;ch<channels;ch++)
         {
               std::swap(at(r,c,ch),at(r,m_cols-c-1,ch));
         }
      }
   }
}
void Matrix::vertical_flip()
{
   for(int r=0;r<m_rows/2;r++)
   {
      for(int c=0;c<m_cols;c++)
      {
         for(int ch=0;ch<channels;ch++)
         {
               std::swap(at(r,c,ch),at(m_rows-r-1,c,ch));
         }
      }
   }
}

void Matrix::contrast(int val)
{
   for(int r=0;r<m_rows;r++)
   {
      for(int c=0;c<m_cols;c++)
      {
         if(at(r,c,0)+val >255)
          at(r,c,0)=255;
         else if(at(r,c,0)+val<0)
          at(r,c,0)=0;
         else{
            at(r,c,0)+=val;
         }
      }
   }
}

void Matrix::border(int border_width,std::vector<int> color)
{
   Matrix mt(m_rows+2*border_width,m_cols+2*border_width,channels,0);
   for(int r=0;r<mt.get_Rows();r++)
   {
      for(int c=0;c<mt.get_Cols();c++)
      {
         // std::cout<<r<<" "<<c<<std::endl;
         if(r<border_width ||r>=m_rows+border_width ||c<border_width ||c>=m_cols+border_width)
         {
            mt.at(r,c,0)=color[0];
            mt.at(r,c,1)=color[1];
            mt.at(r,c,2)=color[2];
         }
         else
         {
            mt.at(r,c,0)=at(r-border_width,c-border_width,0);
            mt.at(r,c,1)=at(r-border_width,c-border_width,1);
            mt.at(r,c,2)=at(r-border_width,c-border_width,2);
         }
      }
   }
   m_cols=mt.get_Cols();
   m_rows=mt.get_Rows();
   mat=mt.mat;
}