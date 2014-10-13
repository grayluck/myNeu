
#ifndef _PROB_H_
#define _PROB_H_

#include <vector>
#include "layer.h"

using namespace std;

class Prob
{
public:
	Func* endFunc;
	vector<Layer*> layer;
	void addLayer(Layer* layer);
	Prob();
	void run();
	void train();
	// init函数应该包括调用train的训练代码
	virtual void init() = 0;
};

#endif