

#include "layer.h"
#include <cmath>

Layer::Layer()
{
	ita = 0;
}

/**
与另一层创建全联通关系
总是由靠前的层调用靠后的层
*/
void Layer::fullConn(Layer* layer)
{
	next = layer;
	layer->last = this;
	for(int i = 0; i < node.size(); ++i)
		node[i]->fullConn(layer);
}

// 第一层
BPLayer::BPLayer(int n)
{
	for(int i = 0; i < n; ++i)
		node.push_back(new Node(this));
}

// 均为求当前层的参数
void BPLayer::forward()
{
	for(int i = 0; i < node.size(); ++i)
	{
		double u = 0;
		Node* p = node[i];
		for(int j = 0; j < p->in.size(); ++j)
		{
			Edge* e = p->in[j];
			u += e->w * e->st->y;
		}
		p->y = func->f(u);
		p->u = u;
	}
}

void BPLayer::backward()
{
	for(int i = 0; i < node.size(); ++i)
	{
		double u = 0;
		Node* p = node[i];
		for(int j = 0; j < p->out.size(); ++j)
		{
			Edge* e = p->out[j];
			Node* q = e->en;
			u += e->w * q->delta;
		}
		u *= func->df(p->u);
		p->delta = u;
		for(int j = 0; j < p->out.size(); ++j)
		{
			Edge* e = p->out[j];
			Node* st = e->st;
			Node* en = e->en;
			e->w += ita * en->delta * st->y;
		}
	}
}

SigBPLayer::SigBPLayer(int n):BPLayer(n)
{
	func = new Sigmoid();
	ita = 0.5;
}

double BPLayer::backwardOutput()
{
	double E = 0;
	for(int i = 0; i < node.size(); ++i)
	{
		double u = 0;
		Node* p = node[i];
		double e = (p->ans - p->y) * func->df(p->u);
		p->delta = e;
		E += e;
	}
	return E;
}

double Layer::getError()
{
	double res = 0;
	for(int i = 0; i < node.size(); ++i)
		res += 0.5 * (node[i]->ans - node[i]->y)*(node[i]->ans - node[i]->y);
	return res;
}

/////////////////////////
// Softmax
/////////////////////////

SoftmaxBPLayer::SoftmaxBPLayer(int n): BPLayer(n)
{
	ita = 0.05;
}

double SoftmaxBPLayer::backwardOutput()
{
	double E = 0;
	double sum = 0;
	for(int j = 0; j < node.size(); ++j)
		sum += exp(node[j]->u);
	double ss = sum * sum;
	for(int i = 0; i < node.size(); ++i)
	{
		double u = 0;
		Node* p = node[i];
		double e = 0;
		double pp = exp(p->u);
		e = p->ans - p->y;
		p->delta = e;
		E += -p->ans * log(p->y);
	}
	return E;
}

void SoftmaxBPLayer::forward()
{
	double sum = 0;
	for(int i = 0; i < node.size(); ++i)
	{
		double u = 0;
		Node* p = node[i];
		for(int j = 0; j < p->in.size(); ++j)
		{
			Edge* e = p->in[j];
			u += e->w * e->st->y;
		}
		p->u = u;
		sum += exp(u);
	}
	for(int i = 0; i < node.size(); ++i)
	{
		Node* p = node[i];
		p->y =  exp(p->u) / sum;
	}
}


/*
	Relu BPLayer
*/

ReluBPLayer::ReluBPLayer(int n): BPLayer(n)
{
	func = new Relu();
	ita = 0.005;
}
