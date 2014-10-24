
#ifndef _LAYER_H_
#define _LAYER_H_

class Layer;

#include "node.h"
#include <vector>
#include "func.h"

using namespace std;

class Layer
{
public:
	Layer();
	enum Typ{
		BP = 0, CNN = 1
	} typ;
	virtual void forward() = 0;
	virtual void backward() = 0;
	virtual double backwardOutput() = 0;
	Layer* last, *next;
	void fullConn(Layer* layer);
	vector<Node*> node;
	Func* func;
	double ita;
	double getError();
};

class BPLayer : public Layer
{
public:
	BPLayer(int n);
	virtual void forward();
	virtual void backward();
	virtual double backwardOutput();
};

class SigBPLayer : public BPLayer
{
public:
	SigBPLayer(int n);
};

class SoftmaxBPLayer : public BPLayer
{
public:
	SoftmaxBPLayer(int n);
	virtual double backwardOutput();
	virtual void forward();
};

class ReluBPLayer : public BPLayer
{
public:
	ReluBPLayer(int n);
};

#endif
