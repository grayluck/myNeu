
#ifndef _FUNC_H_
#define _FUNC_H_

class Func
{
public:
	virtual double f(double x);
	virtual double df(double x);
	virtual double f(double std, double x);
	virtual double df(double std, double x);
};

class Sigmoid : public Func
{
public:
	double f(double x);
	double df(double x);
};

class LeastSquare : public Func
{
public:
	double f(double std, double x);
	double df(double std, double x);
};

class Relu : public Func
{
public:
	double f(double x);
	double df(double x);
};

#endif
