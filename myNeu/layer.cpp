

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

BPLayer::BPLayer()
{

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
	for(int i = 0; i < last->node.size(); ++i)
	{
		double u = 0;
		Node* p = last->node[i];
		for(int j = 0; j < p->out.size(); ++j)
		{
			Edge* e = p->out[j];
			Node* q = e->en;
			u += e->w * q->delta;
		}
		u *= last->func->df(p->u);
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


/////////////////////////////////////////////
/////////////////  CONV  ////////////////////
/////////////////////////////////////////////

Node* Layer::getValue(int x, int y, int channel, int i)
{
	return node[i * w * h * this->channel + channel * w * h + x * w + y];
}

Node* Layer::getLastValue(int x, int y, int channel, int i)
{
	return last->node[i * w * h * this->channel + channel * w * h + x * w + y];
}

int Layer::trans(int x, int y, int c, int i)
{
	return i * w * h * this->channel + channel * w * h + x * w + y;
}

bool Layer::pin(int x, int y)
{
	return x >=0 && y >=0 && x < h && y < w;
}

ConvLayer::ConvLayer(int w, int h, int channel, int n, int siz)
{
	this->w = w;
	this->h = h;
	this->channel = channel;
	this->siz = siz;
	this->filter = n;
	int m = w * h * channel * n;
	for(int i = 0; i <m; ++i)
		node.push_back(new Node(this));
	edge = new double[10];
}

ConvLayer::~ConvLayer()
{
	delete edge;
}

void ConvLayer::forward()
{
	int st = - siz / 2;
	int en = siz + st - 1;
	for(int i = 0; i < filter; ++i)
		for(int c = 0; c < channel; ++c)
			for(int x = 0; x < h; ++x)
				for(int y = 0; y < w; ++y)
				{
					Node* p = node[trans(x, y, c, i)];
					double sum = 0;
					for(int xx = st; xx <= en; ++xx)
						for(int yy = st; yy <= en; ++yy)
						{
							int px = x + xx;
							int py = y + yy;
							if(pin(px, py))
								sum += getLastValue(px, py, c, i)->y
									* edge[trans(xx + st, yy + st, c, i)];
						}
					p->u = sum;
					p->y = func->f(p->y);
				}
}

void ConvLayer::backward()
{

}

////////////////////////////////////////////
// Pooling Layer
PoolLayer::PoolLayer(int w, int h, int channel, int n, int siz, Mode mode)
{
	this->w = w;
	this->h = h;
	this->channel = channel;
	this->siz = siz;
	this->filter = n;
	this->mode = mode;
	int m = w * h * channel * n;
	for(int i = 0; i <m; ++i)
		node.push_back(new Node(this));
}

void PoolLayer::forward()
{
	int st = - siz / 2;
	int en = siz + st - 1;
	for(int i = 0; i < filter; ++i)
		for(int c = 0; c < channel; ++c)
			for(int x = 0; x < h; ++x)
				for(int y = 0; y < w; ++y)
				{
					Node* p = node[trans(x, y, c, i)];
					double sum = 0;
					int cnt = 0;
					for(int xx = st; xx <= en; ++xx)
						for(int yy = st; yy <= en; ++yy)
						{
							int px = x + xx;
							int py = y + yy;
							if(pin(px, py))
							{
								cnt ++;
								double y = getLastValue(px, py, c, i)->y;
								if(mode == MAX)
									sum = max(sum, y);
								else
									sum += y;
							}
						}
					p->u = (mode == MAX? sum : sum / cnt);
					p->y = func->f(p->y);
				}
}

void PoolLayer::backward()
{

}
