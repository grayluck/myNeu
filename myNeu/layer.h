
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
	static Func* defaultFunc;
	Layer();
	enum Typ{
		BP = 0, CNN = 1
	} typ;
	virtual void forward() = 0;
	virtual void backward() = 0;
	Layer* last, *next;
	void fullConn(Layer* layer);
	vector<Node*> node;
	Func* func;
};

class BPLayer : public Layer
{
public:
	BPLayer(int n);
	void forward();
	void backward();
};

#endif
