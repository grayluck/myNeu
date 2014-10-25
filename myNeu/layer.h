
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
	virtual void forward() = 0;
	virtual void backward() = 0;
	virtual double backwardOutput() = 0;
	Layer* last, *next;
	void fullConn(Layer* layer);
	vector<Node*> node;
	Func* func;
	double ita;
	double getError();
	
	// for conv layer (not a good OOP designe...)
	int w, h, channel, siz, filter;
	Node* getValue(int x, int y, int channel, int i = 0);
	Node* getLastValue(int x, int y, int channel, int i = 0);
	bool pin(int x, int y);
	int trans(int x, int y, int c, int i);

};

class BPLayer : public Layer
{
public:
	BPLayer();
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

class ConvLayer : public BPLayer
{
public:
	ConvLayer(int w, int h, int channel, int n, int siz);
	~ConvLayer();
	virtual void forward();
	virtual void backward();
	double* edge;
};

class PoolLayer : public BPLayer
{
public:
	// mode = 0 max; 1 avg
	
	enum Mode{
		MAX = 0, AVG = 1
	} mode;
	PoolLayer(int w, int h, int channel, int n, int siz, Mode mode);
	virtual void forward();
	virtual void backward();
};

#endif
