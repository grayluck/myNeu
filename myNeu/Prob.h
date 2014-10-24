
#ifndef _PROB_H_
#define _PROB_H_

#include <vector>
#include "layer.h"
#include "testCase.h"

using namespace std;

class Prob
{
public:
	// ѵ��Ŀ��
	double target;
	Func* endFunc;
	vector<Layer*> layer;
	void addLayer(Layer* layer);
	Prob();
	void run();
	void doTrain(vector<Testcase>& dat, double target = 0.97);
	double doTest(Testcase& dat);
	// init����Ӧ�ð�������train��ѵ������
	virtual void init() = 0;
	// ��ѵ���õ��������д�뵽metric.txt��
	void outp();
	// ��metric.txt�ж�ȡ�Ѿ�ѵ���õ��������
	void load();
	// ����
	virtual double test() = 0;
	void setValue(Testcase& p);
};

#endif