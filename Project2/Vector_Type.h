#pragma once
#include<iostream>
#include<memory>
#include<algorithm>
using std::unique_ptr;
class VECTOR
{
private:
	int length;
	unique_ptr<double[]> data_;
public:
	VECTOR(int len)
	{
		if(len<=0)
		{
			throw std::invalid_argument("向量长度必须为正整数");
		}
		length=len;
		data_=std::make_unique<double[]>(length);
	}
	VECTOR(const VECTOR& other)
	{
		length=other.length;
		data_=std::make_unique<double[]>(length);
		for(int i=0;i<length;i++)
		{
			data_[i]=other.data_[i];
		}
	}
	double& operator[](int i)
	{
		if(i<0||i>=length)
		{
			throw std::out_of_range("向量索引越界");
		}
		return data_[i];
	}
	double operator[](int i) const
	{
		if(i<0||i>=length)
		{
			throw std::out_of_range("向量索引越界");
		}
		return data_[i];
	}
	VECTOR operator+(const VECTOR& other) const
	{
		if(length!=other.length)
		{
			throw std::invalid_argument("向量长度不匹配，无法相加");
		}
		VECTOR result(length);
		for(int i=0;i<length;i++)
		{
			result.data_[i]=data_[i]+other.data_[i];
		}
		return result;
	}
	VECTOR operator-(const VECTOR& other) const
	{
		if(length!=other.length)
		{
			throw std::invalid_argument("向量长度不匹配，无法相减");
		}
		VECTOR result(length);
		for(int i=0;i<length;i++)
		{
			result.data_[i]=data_[i]-other.data_[i];
		}
		return result;
	}
	VECTOR operator*(double scalar) const
	{
		VECTOR result(length);
		for(int i=0;i<length;i++)
		{
			result.data_[i]=data_[i]*scalar;
		}
		return result;
	}
	VECTOR operator/(double scalar) const
	{
		if(scalar==0)
		{
			throw std::invalid_argument("除数不能为零");
		}
		VECTOR result(length);
		for(int i=0;i<length;i++)
		{
			result.data_[i]=data_[i]/scalar;
		}
		return result;
	}
	double operator*(const VECTOR& other) const
	{
		if(length!=other.length)
		{
			throw std::invalid_argument("向量长度不匹配，无法点乘");
		}
		double result=0.00;
		for(int i=0;i<length;i++)
		{
			result+=data_[i]*other.data_[i];
		}
		return result;
	}
	void sort(bool ascending=true)
	{
		if(length<=1)
		{
			return ;
		}
		if(ascending)
		{
			std::sort(data_.get(),data_.get()+length);
		}
		else
		{
			std::sort(data_.get(),data_.get()+length,std::greater<double>());
		}
	}
};