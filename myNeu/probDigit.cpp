
#include "probDigit.h"

const int maxn = 40;
const int maxCase = 10000;

vector<int[maxn * maxn]> dat;
vector<int> datAns;

int tmp[maxCase][maxn * maxn];
char s[maxn];

int ord[maxCase];

void ProbDigit::init()
{
	freopen("coltest_refined.txt", "r", stdin);
	int reso, ans;
	scanf("%d", &reso);
	Layer* inpLayer = new BPLayer(reso * reso);
	Layer* hidLayer = new BPLayer(25);
	Layer* outpLayer = new BPLayer(10);
	inpLayer->fullConn(hidLayer);
	hidLayer->fullConn(outpLayer);
	this->addLayer(inpLayer);
	this->addLayer(hidLayer);
	this->addLayer(outpLayer);
	dat.clear();
	int n = 0;
	while(scanf("%d", &ans) != EOF)
	{
		datAns.push_back(ans);
		ord[n] = n ++;
		for(int i = 0; i < reso; ++i)
		{
			scanf("%s", s);
			for(int j = 0; j < reso; ++j)
				tmp[i * reso + j] = (s[j] == '#');
			dat.push_back(tmp);
		}
	}
	for(int i = 0; i < n; ++i)
	{
		int a = rand() % n;
		int b = rand() % n;
		swap(ord[a], ord[b]);
	}
	for(int i = 0; i < n; ++i)
	{
		int p = ord[i];
		for(int j = 0; j < 10; ++j)
			outpLayer->node[j]->ans = (j == datAns[p]);
		for(int j = 0; j < reso * reso; ++j)
			inpLayer->node[j]->y = dat[p][j];
		train();
	}
}
