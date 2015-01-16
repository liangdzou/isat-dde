#include <iostream>
#include <string>
#include "engine.h"

#include "isat3/isat3.h"
#include "isat3_ddes_problem.h"
#include "isat3_face.h"
#include "matEngine.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;


int main(int argc, char **argv) {
	Engine *ep;
	isat3_setup();

	if (!(ep = engOpen("\0"))) {
		printf("Can't start MATLAB engine\n" "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}

	engEvalString(ep, "addpath('./matlabFunctions');");
	engEvalString(ep, "impl();");

	/*
	// get maximum c
	double c_max = 1;
	get_maxC(ep);

#ifndef NDebug
	printf("c_max = %f", c_max);
#endif

	string vars[size];
	double bl[size], bu[size];
	setDecl(ep, vars, bl, bu);
	string initStr = getInit(ep);
	string transStr = getTrans(ep);
	string danger = getDangerTarget(ep);
	string V = getString(ep, "charV");
	string target = V + "<" + to_string(c_max) + "or" + "(" + danger + ")";

#ifndef NDebug
	cout << initStr << "\n" << transStr << "\n" << danger << endl;
#endif

	bool result = iSAT3_bmc(vars, bl, bu, initStr, transStr, target);
	if (!result)
		printf("The time span is not enough to give a precise result!");
	else {
		string target = V + "<" + to_string(c_max) + "and !(" + danger + ")";
		result = iSAT3_bmc(vars, bl, bu, initStr, transStr, target);
		cout << (result ? "It is safe." : "It is not safe.");
	}
	*/

	engClose(ep);
	isat3_cleanup();
	return EXIT_SUCCESS;
}
