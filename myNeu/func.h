
#ifndef _FUNC_H_
#define _FUNC_H_

class Func
{
public:
	virtual double f(double x);
	virtual double df(double x);
	virtual double err(double std, double x);
};

class Sigmoid : public Func
{
public:
	double f(double x);
	double df(double x);
};

class MSE : public Func
{
public:
	double err(double std, double x);
};

#endif
