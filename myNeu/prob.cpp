
#include "Prob.h"
#include "testCase.h"

#include "easylogging.h"


Prob::Prob()
{
	//endFunc = new MSE();
	target = 0.97;
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

void Prob::setValue(Testcase& p)
{
	for(int j = 0; j < p.inp.size(); ++j)
		layer[0]->node[j]->y = p.inp[j];
	Layer* l = layer.back();
	for(int j = 0; j < p.ans.size(); ++j)
		l->node[j]->ans = p.ans[j];
}

void Prob::doTrain(vector<Testcase>& dat, double target)
{
	LOG(INFO)<<"training..."<<endl;
	int n = dat.size(), corr;
	int* ord = new int[n];
	for(int i = 0; i < n; ++i)
		ord[i] = i;
	do
	{
		for(int i = 0; i < n; ++i)
			swap(ord[rand() % n], ord[rand() % n]);
		for(int i = 0; i < n; ++i)
		//while(1)
		{
			setValue(dat[ord[i]]);
			double E = 1e100;
			int cnt = 0;
			Layer* p;
			for(int i = 1;i < layer.size(); ++i)
			{
				p = layer[i];
				p->forward();
			}
			p = layer.back();
			E = p->backwardOutput();
			//cnt = (cnt + 1) % 1000;
			//if(cnt== 0)		LOG(DEBUG)<<E<<endl;
			for(int i = layer.size() - 2; i >=0; --i)
				layer[i]->backward();
		}
		for(int i = 0; i < n; ++i)
			swap(ord[rand() % n], ord[rand() % n]);
		corr = 0;
		for(int i = 0; i < n; ++i)
		{
			Testcase& p = dat[ord[i]];
			doTest(p);
			double maxx = 0;
			int maxno = 0;
			for(int j = 0; j < p.ans.size(); ++j)
				if(layer.back()->node[j]->y > maxx)
					maxx = layer.back()->node[j]->y, maxno = j;
			if(maxno == p.hint)
				corr ++;
		}
		LOG(INFO)<<(double)corr / n<<endl;
		outp();
	//}while((double)corr / n < 0.97);
	//}while(1);
	}while((double)corr / n < target);
	delete ord;
}

double Prob::doTest(Testcase& dat)
{
	setValue(dat);
	Layer* p;
	for(int i = 1;i < layer.size(); ++i)
	{
		p = layer[i];
		p->forward();
	}
	p = layer.back();
	return 0;
}

void Prob::outp()
{
	FILE* fo = fopen("metric.txt", "w");
	for(int i = 0; i < layer.size(); ++i)
	{
		for(int j = 0; j < layer[i]->node.size(); ++j)
		{
			Node* node = layer[i]->node[j];
			for(int k = 0; k < node->out.size(); ++k)
				fprintf(fo, "%lf ", node->out[k]->w);
		}
		fprintf(fo, "\n");
	}
	fclose(fo);
}

void Prob::load()
{
	FILE* fi = fopen("metric.txt", "r");
	for(int i = 0; i < layer.size(); ++i)
	{
		for(int j = 0; j < layer[i]->node.size(); ++j)
		{
			Node* node = layer[i]->node[j];
			for(int k = 0; k < node->out.size(); ++k)
				fscanf(fi, "%lf", &(node->out[k]->w));
		}
	}
	fclose(fi);
}
