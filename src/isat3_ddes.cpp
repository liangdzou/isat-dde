#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include "engine.h"

#include "isat3_face.h"
#include "matEngine.h"
#include "isat3_ddes_problem.h"
#include "isat3_ddes_solver.h"
#include "parameters.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;
using std::stod;
using std::stol;

#include "isat3/isat3.h"

int main(int argc, char **argv) {
	clock_t sclock = clock();

	for (int i = 0; i < argc - 1; ++i) {
		if (!strcmp(argv[i], "-file"))
			para::file = argv[i + 1];
		else if (!strcmp(argv[i], "-a_w"))
			para::a_w = stod(argv[i + 1]);
		else if (!strcmp(argv[i], "-co_w"))
			para::co_w = stod(argv[i + 1]);
		else if (!strcmp(argv[i], "-e"))
			para::e = stod(argv[i + 1]);
		else if (!strcmp(argv[i], "-md"))
			para::md = stod(argv[i + 1]);
		else if (!strcmp(argv[i], "-expr_t_max"))
			para::expr_t_max = stol(argv[i + 1]);
		else if (!strcmp(argv[i], "-bmc_t_max"))
			para::bmc_t_max = stol(argv[i + 1]);
		else if (!strcmp(argv[i], "-c_min"))
			para::c_min = stod(argv[i + 1]);
		else if (!strcmp(argv[i], "-c_max"))
			para::c_max = stod(argv[i + 1]);
		else if (!strcmp(argv[i], "-c_delta"))
			para::c_delta = stod(argv[i + 1]);
	}
#define NDebug0
#ifndef NDebug0
	para::print();
#endif

	isat3_setup();

// unit test
#define NDebug1
#ifndef NDebug1
	mat_engine_test();
	isat3_face_test();
#endif

	if (para::file.empty()) {
		cout << "No problem file is specified. (in isat_ddes.cpp)";
		return 0;
	}
	isat3_ddes_problem problem(para::file);
	cout << "Problem is loaded." << endl << endl;
#define NDebug2
#ifndef NDebug2
	problem.print();
#endif

	she_ly_computer ly_cal;
	string ly = ly_cal.ly_computation(problem);
	if (ly.empty())
		cout << "The discrete system is not stable."
				<< " (unbounded safety is given in the following.)" << endl << endl;
	else
		cout << "Lyapunov function is calculated." << endl << endl;
#define NDebug3
#ifndef NDebug3
	cout << ly << endl << endl;
#endif

	isat3_c_max_computer c_cal;
	double c = 0;
	if (!ly.empty()) {
		c = c_cal.c_max_computation(problem, ly);
		cout << "Maximum c is calculated, and it is " << c << endl << endl;
	}
#define NDebug4
#ifndef NDebug4
	cout << c << endl << endl;
#endif

	iSAT3_bmc(problem, ly + "<=" + to_string(c));

	clock_t eclock = clock();
	cout << endl << "It takes "
			<< static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
			<< " seconds." << endl;

	return EXIT_SUCCESS;
}

