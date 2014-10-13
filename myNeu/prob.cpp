
#include "Prob.h"

#include "easylogging.h"


Prob::Prob()
{
	endFunc = new MSE();
}

void Prob::addLayer(Layer* layer)
{
	/*
	if(this->layer.size() > 0)
		layer->last = this->layer[this->layer.size() - 1];
	*/
	this->layer.push_back(layer);
}

void Prob::run()
{

}

void Prob::train()
{
	while(1)
	{
		Layer* p;
		for(int i = 1;i < layer.size(); ++i)
		{
			p = layer[i];
			p->forward();
		}
		p = layer.back();
		double E = 0;
		for(int i = 0; i < p->node.size(); ++i)
		{
			Node* node = p->node[i];
			double e = this->endFunc->err(node->ans, node->y);
			node->delta = e;
			E += e;
		}
		LOG(DEBUG)<<E<<endl;
		for(int i = layer.size() - 2; i >=0; --i)
		{
			layer[i]->backward();
		}
	}
}
