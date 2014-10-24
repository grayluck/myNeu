
#include "func.h"
#include <iostream>

#include <cmath>

double Func::f(double x)
{
	std::cerr<<"[ERROR]使用了未定义的函数f(x)！\n";
	return 0;
}

double Func::df(double x)
{
	std::cerr<<"[ERROR]使用了未定义的函数df(x)！\n";
	return 0;
}

double Func::f(double std, double x)
{
	std::cerr<<"[ERROR]使用了未定义的函数f(std, x)！\n";
	return 0;
}

double Func::df(double std, double x)
{
	std::cerr<<"[ERROR]使用了未定义的函数df(std, x)！\n";
	return 0;
}

double Sigmoid::f(double x)
{
	return 1.0 / (1 + exp(-x));
}

double Sigmoid::df(double x)
{
	return f(x)*(1-f(x));
}

double LeastSquare::f(double std, double x)
{
	return 0.5 * (std - x) * (std - x);
	//return x - std;
}

double LeastSquare::df(double std, double x)
{
	return x - std;
}

/*
double Softmax::f(double std, double x)
{
	return -std * log(x);
}

double Softmax::df(double std, double x)
{}
*/

double Relu::f(double x)
{
	return x>0?x:0;
}

double Relu::df(double x)
{
	return x>0?1:0;
}
