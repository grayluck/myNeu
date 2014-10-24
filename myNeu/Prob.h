
#ifndef _PROB_H_
#define _PROB_H_

#include <vector>
#include "layer.h"
#include "testCase.h"

using namespace std;

class Prob
{
public:
	// 训练目标
	double target;
	Func* endFunc;
	vector<Layer*> layer;
	void addLayer(Layer* layer);
	Prob();
	void run();
	void doTrain(vector<Testcase>& dat, double target = 0.97);
	double doTest(Testcase& dat);
	// init函数应该包括调用train的训练代码
	virtual void init() = 0;
	// 将训练好的网络参数写入到metric.txt中
	void outp();
	// 从metric.txt中读取已经训练好的网络参数
	void load();
	// 测试
	virtual double test() = 0;
	void setValue(Testcase& p);
};

#endif