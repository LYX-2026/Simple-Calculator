#pragma once
#include<iostream>
#include<memory>
using std::unique_ptr;
class MATRIX
{
private:
	int row;
	int col;
	unique_ptr<double[]> data_;
public:
	MATRIX(int r,int c)
	{
		if(r<=0||c<=0)
		{
			throw std::invalid_argument("矩阵的行数和列数必须为正整数");
		}
		row=r;
		col=c;
		data_=std::make_unique<double[]>(row*col);
	}
	MATRIX(const MATRIX& other)
	{
		row=other.row;
		col=other.col;
		data_=std::make_unique<double[]>(row*col);
		for(int i=0;i<row*col;i++)
		{
			data_[i]=other.data_[i];
		}
	}
	double& operator()(int i,int j)
	{
		if(i<0||i>=row||j<0||j>=col)
		{
			throw std::out_of_range("矩阵索引越界");
		}
		return data_[i*col+j];
	}
	double operator()(int i,int j) const
	{
		if(i<0||i>=row||j<0||j>=col)
		{
			throw std::out_of_range("矩阵索引越界");
		}
		return data_[i*col+j];
	}
	MATRIX operator+(const MATRIX& other) const
	{
		if(row!=other.row||col!=other.col)
		{
			throw std::invalid_argument("矩阵维度不匹配，无法相加");
		}
		MATRIX result(row,col);
		for(int i=0;i<row*col;i++)
		{
			result.data_[i]=data_[i]+other.data_[i];
		}
		return result;
	}
	MATRIX operator-(const MATRIX& other) const
	{
		if(row!=other.row||col!=other.col)
		{
			throw std::invalid_argument("矩阵维度不匹配，无法相减");
		}
		MATRIX result(row,col);
		for(int i=0;i<row*col;i++)
		{
			result.data_[i]=data_[i]-other.data_[i];
		}
		return result;
	}
	MATRIX operator*(const MATRIX& other) const
	{
		if(col!=other.row)
		{
			throw std::invalid_argument("矩阵维度不匹配，无法相乘");
		}
		MATRIX result(row,other.col);
		for(int i=0;i<row;i++)
		{
			for(int j=0;j<other.col;j++)
			{
				double sum=0;
				for(int k=0;k<col;k++)
				{
					sum+=(*this)(i,k)*other(k,j);
				}
				result(i,j)=sum;
			}
		}
		return result;
	}
	MATRIX operator*(const double scalar) const
	{
		MATRIX result(row,col);
		for(int i=0;i<row*col;i++)
		{
			result.data_[i]=data_[i]*scalar;
		}
		return result;
	}
};