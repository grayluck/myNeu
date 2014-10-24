
#include "easylogging.h"
#include "probDigit.h"

#include "boost/program_options.hpp"

namespace po = boost::program_options;

_INITIALIZE_EASYLOGGINGPP

Prob* prob;

int main(int argc, char* argv[])
{
	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("compression", po::value<int>(), "set compression level")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);    

	/*
	if (vm.count("compression")) {
		cout << "Compression level was set to " 
		<< vm["compression"].as<int>() << ".\n";
	} else {
		cout << "Compression level was not set.\n";
	}
	*/

	prob = new ProbDigit();
	// sigmoid
	// prob->target = 0.97;
	// softmax
	// prob->target = 1 - 1e-7;
	// relu
	//prob->target = 0.9875;
	/*
	prob->target = 1;
	prob->init();
	*/
	prob->load();
	prob->test();
	return 0;
}
