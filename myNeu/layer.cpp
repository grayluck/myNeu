

#include "layer.h"

Func* Layer::defaultFunc = new Sigmoid();

Layer::Layer()
{
	func = defaultFunc;
}

/**
����һ�㴴��ȫ��ͨ��ϵ
�����ɿ�ǰ�Ĳ���ÿ���Ĳ�
*/
void Layer::fullConn(Layer* layer)
{
	next = layer;
	layer->last = this;
	for(int i = 0; i < node.size(); ++i)
		node[i]->fullConn(layer);
}

// ��һ��
BPLayer::BPLayer(int n)
{
	for(int i = 0; i < n; ++i)
		node.push_back(new Node(this));
}

// ��Ϊ��ǰ��Ĳ���
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
		u *= func->df(p->y);
		p->delta = u;
		for(int j = 0; j < p->in.size(); ++j)
		{
			Edge* e = p->in[j];
			e->w += p->delta * e->st->y;
		}
	}
}
