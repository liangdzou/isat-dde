#include <iostream>
#include <string>
#include <math.h>
#include "engine.h"

#include "isat3_face.h"
#include "matEngine.h"
#include "isat3_ddes_problem.h"
#include "isat3_ddes_solver.h"

using std::string;
using std::to_string;
using std::cout;
using std::endl;

int main(int argc, char **argv) {
	isat3_setup();

// unit test
#define NDebug1
#ifndef NDebug1
	mat_engine_test();
	isat3_face_test();
#endif

	isat3_ddes_problem problem("ex1");
	cout << "Problem is loaded." << endl;
#define NDebug2
#ifndef NDebug2
	problem.print();
#endif

	she_ly_computer ly_cal;
	string ly = ly_cal.ly_computation(problem);
	cout << "Lyapunov function is calculated." << endl;
#define NDebug3
#ifndef NDebug3
	cout << ly << endl << endl;
#endif

	isat3_c_max_computer c_cal;
	double c = c_cal.c_max_computation(problem, ly);
	cout << "Maximum step is calculated, and it is " << c << endl;
#define NDebug4
#ifndef NDebug4
	cout << c << endl << endl;
#endif

	iSAT3_bmc(problem.is3, problem.get_vars_begin(), problem.get_vars_end(),
			problem.get_init(), problem.get_trans(), problem.get_target() + ";", true,
			0, ceil(c));

	return EXIT_SUCCESS;
}

