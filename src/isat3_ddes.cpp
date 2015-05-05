#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include "engine.h"
#include <fstream>

#include "isat3_face.h"
#include "matEngine.h"
#include "isat3_ddes_problem.h"
#include "isat3_ddes_solver.h"
#include "parameters.h"

using namespace std;

#include "isat3/isat3.h"

int main(int argc, char **argv) {
	isat3_ddes_problem::path = getenv("ISATDDEHOME");

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
		else if (!strcmp(argv[i], "-stable")) {
			para::stable = strcasecmp(argv[i + 1], "false");
		}
	}
#define NDebug0
#ifndef NDebug0
	para::print();
#endif

	isat3_setup();

// unit test
#define NDebug1
#ifndef NDebug1
//	mat_engine_test();
	isat3_face_test();
#endif

	cout << string(80, '=') << endl << string(80, '=') << endl;
	cout << "Loading... (" << para::file << ")" << endl;
	if (para::file.empty()) {
		cout << "No problem file is specified. (in isat_ddes.cpp)";
		return 0;
	}
	clock_t sclock = clock();
	auto t_start = time(NULL);
	isat3_ddes_problem problem(para::file);
	clock_t eclock = clock();
	auto t_end = time(NULL);
	cout << "Problem is loaded." << endl << "It takes "
//			<< static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC << " or "
			<< difftime(t_end, t_start) << " seconds." << endl << endl << endl;
#define NDebug2
#ifndef NDebug2
	problem.print();
#endif

	string ly;
	if (para::stable) {
		cout << string(80, '=') << endl << string(80, '=') << endl;
		cout << "Calculating Lyapunov function..." << endl;
		she_ly_computer ly_cal;
		sclock = clock();
		t_start = time(NULL);
		ly = ly_cal.ly_computation(problem);
		eclock = clock();
		t_end = time(NULL);
		if (ly.empty())
			cout << "The discrete system is not stable."
					<< " (unbounded safety is given in the following.)" << endl;
		else
			cout << "Lyapunov function is calculated." << endl;
		cout << "It takes "
//				<< static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC << " or "
				<< difftime(t_end, t_start) << " seconds." << endl << endl
				<< endl;
	}
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
		t_start = time(NULL);
		c = c_cal.c_max_computation(problem, ly);
		eclock = clock();
		t_end = time(NULL);
		cout << "Maximum c is calculated, and it is " << c << endl;
		cout << "It takes "
				<< static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
//				<< " or " << difftime(t_end, t_start) << " seconds."
				<< endl << endl << endl;
	}
	double dm = 0;
	if (!ly.empty()) {
		cout << string(80, '=') << endl << string(80, '=') << endl;
		cout << "Calculating minimum reduction..." << endl;
		sclock = clock();
		t_start = time(NULL);
		dm = dm_calc(problem, c);
//		cout << dm << endl;
		eclock = clock();
		t_end = time(NULL);
		cout << "It takes "
//				<< static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
//				<< " or "
				<< difftime(t_end, t_start) << " seconds."
				<< endl << endl << endl;
	}


#define NDebug4
#ifndef NDebug4
	cout << c << endl << endl;
#endif

	cout << string(80, '=') << endl << string(80, '=') << endl;
	cout << "Checking safety..." << endl;
	if (ly.empty()) {
		string isat3_problem = "DECL\n" + problem.get_decl() + "\nINIT\n"
				+ problem.get_init() + "\nTRANS\n" + problem.get_trans()
				+ "\nTARGET\n" + problem.get_target() + ";";
		ofstream out("temp.hys", ofstream::out);
		out << isat3_problem;
		out.flush();
		sclock = clock();
		t_start = time(NULL);
		string exe_str = isat3_ddes_problem::path + "/bin/isat3 -I -v -v temp.hys";
		system(exe_str.c_str());
		eclock = clock();
		t_end = time(NULL);
	} else {
		sclock = clock();
		t_start = time(NULL);
		iSAT3_bmc(problem, ly + "<=" + to_string(c));
		eclock = clock();
		t_end = time(NULL);
	}
	cout << "It takes " << static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
//			<< " or " << difftime(t_end, t_start)
			<< " seconds."
			<< endl;

	return EXIT_SUCCESS;
}

