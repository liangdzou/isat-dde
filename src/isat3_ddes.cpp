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

using namespace std;

#include "isat3/isat3.h"

int main(int argc, char **argv) {

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
		else if (!strcmp(argv[i], "-bound"))
			para::bound = stol(argv[i + 1]);
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

	cout << string(80, '=') << endl << string(80, '=') << endl;
	cout << "Loading... (" << para::file << ".m)" << endl;
	if (para::file.empty()) {
		cout << "No problem file is specified. (in isat_ddes.cpp)";
		return 0;
	}
	clock_t sclock = clock();
	isat3_ddes_problem problem(para::file);
	clock_t eclock = clock();
	cout << "Problem is loaded." << endl << "It takes "
			<< static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
			<< " seconds." << endl << endl << endl;
#define NDebug2
#ifndef NDebug2
	problem.print();
#endif

	cout << string(80, '=') << endl << string(80, '=') << endl;
	cout << "Calculating Lyapunov function..." << endl;
	she_ly_computer ly_cal;
	sclock = clock();
	string ly = ly_cal.ly_computation(problem);
	eclock = clock();
	if (ly.empty())
		cout << "The discrete system is not stable."
				<< " (unbounded safety is given in the following.)" << endl;
	else
		cout << "Lyapunov function is calculated." << endl;
	cout << "It takes " << static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
			<< " seconds." << endl << endl << endl;
#define NDebug3
#ifndef NDebug3
	cout << ly << endl << endl;
#endif

	double c = 0;
	if (!ly.empty()) {
		cout << string(80, '=') << endl << string(80, '=') << endl;
		cout << "Calculating maximum c..." << endl;
		isat3_c_max_computer c_cal;
		sclock = clock();
		c = c_cal.c_max_computation(problem, ly);
		eclock = clock();
		cout << "Maximum c is calculated, and it is " << c << endl;
		cout << "It takes "
				<< static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
				<< " seconds." << endl << endl << endl;
	}
#define NDebug4
#ifndef NDebug4
	cout << c << endl << endl;
#endif

	cout << string(80, '=') << endl << string(80, '=') << endl;
	cout << "Checking safety..." << endl;
	sclock = clock();
	iSAT3_bmc(problem, ly + "<=" + to_string(c));
	eclock = clock();
	cout << "It takes " << static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
			<< " seconds." << endl;

	return EXIT_SUCCESS;
}

