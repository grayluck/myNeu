
#include "func.h"
#include <iostream>

#include <cmath>

double Func::f(double x)
{
	std::cerr<<"[ERROR]使用了未定义的函数f！\n";
	return 0;
}

double Func::df(double x)
{
	std::cerr<<"[ERROR]使用了未定义的函数df！\n";
	return 0;
}

double Func::err(double std, double x)
{
	std::cerr<<"[ERROR]使用了未定义的函数err！\n";
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

double MSE::err(double std, double x)
{
	return 0.5 * (std - x) * (std - x);
}
