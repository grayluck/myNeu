
#ifndef _PROBDIGIT_H_
#define _PROBDIGIT_H_

#include "Prob.h"

class ProbDigit : public Prob
{
public:
	ProbDigit();
	void init();
	double test();
	void loadFile(char* filName);
};

#endif
