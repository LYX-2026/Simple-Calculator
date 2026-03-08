#pragma once
double ans=0.00;
#include<math.h>
class MATH
{
public:
	double f1_factorial(double x)
	{
		if(x==0||x==1)
			return 1;
		double result=1;
		for(int i=2;i<=x;i++)
		{
			result*=i;
		}
		return result;
	}
	double f2_nPr(int n,int r)
	{
		if(n<0||r<0||r>n)
			throw std::invalid_argument("n和r必须满足0<=r<=n");
		double result=1;
		for(int i=n;i>n-r;i--)
		{
			result*=i;
		}
		return result;
		//return f1_factorial(n)/f1_factorial(n-r);
	}
	double f3_nCr(int n,int r)
	{
		if(n<0||r<0||r>n)
			throw std::invalid_argument("n和r必须满足0<=r<=n");
		double result=1;
		for(int i=1;i<=r;i++)
		{
			result=result*(n-i+1)/i;
		}
		return result;
		//return f1_factorial(n)/(f1_factorial(r)*f1_factorial(n-r));
	}
	bool isprime(int n)
	{
		if(n<2)
		{
			throw std::invalid_argument("输入必须大于等于2");
		}
		else if(n==2)
		{
			return true;
		}
		else if((n&1)==0)
		{
			return false;
		}
		else
		{
			for(int i=3;(long long)i*i<=n;i+=2)
			{
				if(n%i==0)
				{
					return false;
				}
			}
			return true;
		}
	}
};