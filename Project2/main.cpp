#include<iostream>
#include "All_Hearder.h"
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#ifndef calculator
ExpressionCalculator calculator;
#endif
using namespace std;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	cout<<"Hello,World!"<<endl;
	string input_main;
	while(true)
	{
		cout<<"请输入表达式（输入exit退出）: ";//请输入表达式（输入exit退出）
		getline(cin,input_main);
		if(input_main=="exit")
		{
			break;
		}
		else if(input_main=="1")
		{
			cout<<"一般计算: \n请输入算式: \n";
			string expression;
			getline(cin,expression,'\n');
			if(expression=="exit")
				continue;
			else if(expression=="help")
				calculator.showSupportedFunctions();
			else
			{
				try
				{
					double result=calculator.calculate(expression);
					printf("= %.10g\n",result);
					ans=result;
				}
				catch(const exception& e)
				{
					cerr<<"错误: "<<e.what()<<endl;//计算错误
					continue;
				}
			}
		}
		else if(input_main=="2")
		{
			cout<<"特殊函数计算: \n请输入函数名称: \n";
			string input_1;
			getline(cin,input_1,'\n');
			if(input_1=="exit")
			{
				cout<<"退出特殊计算功能!"<<endl;
				continue;
			}
		}
	}
	return 0;
}