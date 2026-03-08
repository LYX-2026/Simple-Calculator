#pragma once
#include<iostream>
#include<math.h>
#include<map>
#include<string>
#include<stack>
#include<functional>
#include "Math_.h"
MATH M;
using namespace std;
const double PI=acos(-1);
const double E_=exp(1);
class ExpressionCalculator
{
private:
	map<string,function<double(double)>> functions;
	map<char,int> precedence;
public:
	ExpressionCalculator()
	{
		//定义运算符优先级
		precedence={{'+',1},{'-',1},{'*',2},{'/',2},{'%',2},{'^',3}};
		//定义数学函数
		functions["sin"]=[](double x){return sin(x);};
		functions["cos"]=[](double x){return cos(x);};
		functions["tan"]=[](double x){return tan(x);};
		functions["lg"]=[](double x)
		{
			if(x<=0)
				throw runtime_error("常用对数参数必须为正数");
			return log10(x);
		};
		functions["ln"]=[](double x)
		{
			if(x<=0)
				throw runtime_error("自然对数参数避暑为正数");
			return log(x);
		};
		functions["sqrt"]=[](double x)
		{
			if(x<0)
				throw runtime_error("平方根参数必须为正数");
			return sqrt(x);
		};
		functions["sinh"]=[](double x){return sinh(x);};
		functions["cosh"]=[](double x){return cosh(x);};
		functions["tanh"]=[](double x){return tanh(x);};
		functions["exp"]=[](double x){return exp(x);};
		functions["pi"]=[](double x){return x*PI;};
		functions["e"]=[](double x){return x*E_;};
		functions["ans"]=[](double x){return x*ans;};
		functions["asin"]=[](double x){return asin(x);};
		functions["acos"]=[](double x){return acos(x);};
		functions["atan"]=[](double x){return atan(x);};
		functions["factorial"]=[](double x)
		{
			if(x<0)
				throw runtime_error("阶乘参数必须大于等于0");
			return M.f1_factorial(x);
		};
		functions["asinh"]=[](double x){return asinh(x);};
		functions["acosh"]=[](double x){return acosh(x);};
		functions["atanh"]=[](double x){return atanh(x);};
		functions["abs"]=[](double x){return fabs(x);};
		functions["rd"]=[](double x){return x*(180/PI);};
		functions["dr"]=[](double x){return x*(PI/180);};
	}
	//去除字符串中的空格
	string removeSpaces(const string& expr)
	{
		string result;
		for(char c:expr)
		{
			if(!isspace((c)))
				result+=c;
		}
		return result;
	}
	double applyOperator(char op,double a,double b)
	{
		switch(op)
		{
		case '+':
			return a+b;
		case '-':
			return a-b;
		case '*':
			return a*b;
		case '/':
			if(b==0)
				throw runtime_error("除数不能为0");
			return a/b;
		case '^':
			return pow(a,b);
		case '%':
			return int(a)%int(b);
		default:
			throw runtime_error("未知运算符");
		}
	}
	//判断是否为函数名
	bool isFunction(const string& token,size_t& funcLength)
	{
		for(const auto& func:functions)
		{
			if(token.find(func.first)==0)
			{
				funcLength=func.first.length();
				return true;
			}
		}
		funcLength=0;
		return false;
	}
	// 主计算函数
	double calculate(const string& expression)
	{
		string expr=removeSpaces(expression);
		stack<double> values;
		stack<char> operators;
		for(size_t i=0;i<expr.length();i++)
		{
			// 处理数字
			if(isdigit(expr[i])||expr[i]=='.')
			{
				string numStr;
				while(i<expr.length()&&(isdigit(expr[i])||expr[i]=='.'))
				{
					numStr+=expr[i];
					i++;
				}
				i--; // 回退一个字符
				try
				{
					values.push(stod(numStr));
				}
				catch(const exception& e)
				{
					throw runtime_error("数字格式错误: "+numStr);
				}
			}
			// 处理函数
			else if(isalpha(expr[i]))
			{
				string funcName;
				size_t j=i;
				while(j<expr.length()&&isalpha(expr[j]))
				{
					funcName+=expr[j];
					j++;
				}
				size_t funcLength;
				if(isFunction(funcName,funcLength))
				{
					if(j>=expr.length()||expr[j]!='(')
					{
						throw runtime_error("函数后必须跟括号");
					}
					// 找到匹配的右括号
					int bracketCount=1;
					size_t k=j+1;
					while(k<expr.length()&&bracketCount>0)
					{
						if(expr[k]=='(') bracketCount++;
						else if(expr[k]==')') bracketCount--;
						k++;
					}
					if(bracketCount!=0)
					{
						throw runtime_error("括号不匹配");
					}
					string arg=expr.substr(j+1,k-j-2);
					double argValue=calculate(arg);
					double result=functions[funcName](argValue);
					values.push(result);
					i=k-1; // 跳过已处理的部分
				}
				else
				{
					throw runtime_error("未知函数: "+funcName);
				}
			}
			// 处理左括号
			else if(expr[i]=='(')
			{
				operators.push('(');
			}
			// 处理右括号
			else if(expr[i]==')')
			{
				while(!operators.empty()&&operators.top()!='(')
				{
					char op=operators.top();
					operators.pop();
					if(values.size()<2)
					{
						throw runtime_error("表达式语法错误");//表达式语法错误
					}
					double b=values.top();
					values.pop();
					double a=values.top();
					values.pop();
					values.push(applyOperator(op,a,b));
				}
				if(operators.empty())
				{
					throw runtime_error("括号不匹配");//括号不匹配
				}
				operators.pop(); // 弹出左括号
			}
			// 处理运算符
			else if(precedence.find(expr[i])!=precedence.end())
			{
				// 处理负号
				if(expr[i]=='-'&&(i==0||expr[i-1]=='('||precedence.find(expr[i-1])!=precedence.end()))
				{
					// 这是一个负号而不是减号
					values.push(0);
					operators.push('-');
				}
				else
				{
					while(!operators.empty()&&operators.top()!='('&&precedence[operators.top()]>=precedence[expr[i]])
					{
						char op=operators.top();
						operators.pop();
						if(values.size()<2)
						{
							throw runtime_error("表达式语法错误");//表达式语法错误
						}
						double b=values.top();
						values.pop();
						double a=values.top();
						values.pop();
						values.push(applyOperator(op,a,b));
					}
					operators.push(expr[i]);
				}
			}
			else
			{
				throw runtime_error("无效字符"+string(1,expr[i]));//无效字符
			}
		}
		// 处理剩余运算符
		while(!operators.empty())
		{
			char op=operators.top();
			operators.pop();
			if(values.size()<2)
			{
				throw runtime_error("表达式语法错误");//表达式语法错误
			}
			double b=values.top();
			values.pop();
			double a=values.top();
			values.pop();
			values.push(applyOperator(op,a,b));
		}
		if(values.size()!=1)
		{
			throw runtime_error("表达式不完整");
		}
		return values.top();
	}
	// 显示支持的函数列表
	void showSupportedFunctions()
	{
		cout<<"支持的函数: ";//支持的函数
		for(const auto& func:functions)
		{
			cout<<func.first<<" ";
		}
		cout<<endl;
	}
};