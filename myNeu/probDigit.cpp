
#include "probDigit.h"
#include "easylogging.h"
#include "testCase.h"

const int maxn = 30;
const int maxCase = 10000;

char s[maxn];

int ord[maxCase];
int reso, n;
vector<Testcase> testcase;

ProbDigit::ProbDigit():Prob()
{
	/*
	Layer* inpLayer = new SigBPLayer(29 * 29);
	Layer* hidLayer = new SigBPLayer(25);
	Layer* outpLayer = new SigBPLayer(10); 
	*/
	//Layer* outpLayer = new SoftmaxBPLayer(10);

	Layer* inpLayer = new ReluBPLayer(29 * 29);
	Layer* hidLayer = new ReluBPLayer(25);
	//Layer* outpLayer = new ReluBPLayer(10);
	Layer* outpLayer = new SoftmaxBPLayer(10);

	inpLayer->fullConn(hidLayer);
	hidLayer->fullConn(outpLayer);
	this->addLayer(inpLayer);
	this->addLayer(hidLayer);
	this->addLayer(outpLayer);
}

void ProbDigit::loadFile(char* filName)
{
	testcase.clear();
	freopen(filName, "r", stdin);
	int ans;
	scanf("%d", &reso);
	n = 0;
	while(scanf("%d", &ans) != EOF)
	{
		testcase.push_back(Testcase());
		Testcase& p = testcase.back();
		for(int i = 0; i < 10; ++i)
			p.ans.push_back(ans == i);
		p.hint = ans;
		ord[n] = n;
		for(int i = 0; i < reso; ++i)
		{
			scanf("%s", s);
			for(int j = 0; j < reso; ++j)
			{
				p.inp.push_back(s[j] == '#');
			}
		}
		n++;
	}
}

void ProbDigit::init()
{
	loadFile("digit/coltest_refined.txt");
	doTrain(testcase, target);
}

// 返回预测成功率
double ProbDigit::test()
{
	this->loadFile("digit/ourdig_refined.txt");
	LOG(INFO)<<"testing..."<<endl;
	FILE* fo = fopen("result.txt", "w");
	Layer* outpLayer = layer.back();
	Layer* inpLayer = layer[0];
	int corr = 0;
	for(int i = 0; i < n; ++i)
	{
		if(i % 1000 == 0)
			LOG(INFO)<<i<<endl;
		double E = doTest(testcase[i]);
		double maxx = 0;
		int maxno = 0;
		for(int j = 0; j < 10; ++j)
		{
			double deb = outpLayer->node[j]->y;
			if(maxx < deb)
				maxx = outpLayer->node[j]->y, maxno = j;
		}
		corr += (testcase[i].hint == maxno);
		fprintf(fo, "%d %d %lf\n", testcase[i].hint, maxno, E);
		for(int x = 0; x < reso; ++x)
		{
			for(int y = 0; y < reso; ++y)
				fprintf(fo, "%c", (testcase[i].inp[x * reso + y]?'#':'.'));
			fprintf(fo, "\n");
		}
	}
	fclose(fo);
	outp();
	LOG(INFO)<<(double)corr / n<<endl;
	return (double)corr / n;
}

