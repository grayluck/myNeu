
#include "easylogging.h"
#include "probDigit.h"

_INITIALIZE_EASYLOGGINGPP

Prob* prob;

int main()
{
	prob = new ProbDigit();
	prob->init();
	return 0;
}
