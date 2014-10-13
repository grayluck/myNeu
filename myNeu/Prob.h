
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
	// init����Ӧ�ð�������train��ѵ������
	virtual void init() = 0;
};

#endif