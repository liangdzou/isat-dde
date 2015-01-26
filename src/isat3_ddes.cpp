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
void test() {
	isat3_setup();
	isat3* is3 = isat3_init(NULL);

	isat3_node* vars1 = isat3_node_create_variable_float(is3, "cb1", -1000,
			1000);
	isat3_node* vars2 = isat3_node_create_variable_float(is3, "cb2", -1000,
			1000);
	isat3_node* vars3 = isat3_node_create_variable_float(is3, "cb3", -1000,
			1000);
	isat3_node* vars4 = isat3_node_create_variable_float(is3, "xi1", 0, 1);
	isat3_node* vars5 = isat3_node_create_variable_float(is3, "t", 0, 1);

	isat3_node *expr =
			isat3_node_create_from_string(is3,
					"((cb2*(cb1*((12577326308623*xi1)*2.775558*0.00000000000000001 + 295380547826987*1.110223*0.0000000000000001) + cb3*((630836335524057*xi1)*6.938894*0.000000000000000001 + 3195453300455285*1.387779*0.00000000000000001) - cb2*((2182413043713*xi1)*1.387779*0.00000000000000001 - 3629688555776053*1.387779*0.00000000000000001)) + cb1*(cb2*((12577326308623*xi1)*2.775558*0.00000000000000001 + 295380547826987*1.110223*0.0000000000000001) + cb3*((1103083635343171*xi1)*6.938894*0.000000000000000001 + 4776800182714127*6.938894*0.000000000000000001) + cb1*((58151926213275*xi1)*6.938894*0.000000000000000001 + 7553983136787341*6.938894*0.000000000000000001)) + cb3*(cb3*((678570451744761*xi1)*1.387779*0.00000000000000001 + 5585128566629689*1.387779*0.00000000000000001) + cb1*((1103083635343171*xi1)*6.938894*0.000000000000000001 + 4776800182714127*6.938894*0.000000000000000001) + cb2*((630836335524057*xi1)*6.938894*0.000000000000000001 + 3195453300455285*1.387779*0.00000000000000001)))"
							"<=500) and (((1 < cb1 + cb2*t + cb3*t^2)) or((cb1 + cb2*t + cb3*t^2 < -1)));");
	i3_type_t result = isat3_solve_expr(is3, expr, para::get_expr_t_max());
	if (!isat3_result_contains_solution(result))
		cout << "NO SOLUTION." << endl;
	else {
		cout << isat3_get_result_string(result) << endl;
		cout << "  ";
		cout << isat3_node_get_variable_name(is3, vars1)
				<< (isat3_is_lower_bound_strict(is3, vars1, 0) ? "(" : "[")
				<< isat3_get_lower_bound(is3, vars1, 0) << ", "
				<< isat3_get_upper_bound(is3, vars1, 0)
				<< (isat3_is_upper_bound_strict(is3, vars1, 0) ? ")" : "]")
				<< endl;
		cout << "  ";
		cout << isat3_node_get_variable_name(is3, vars2)
				<< (isat3_is_lower_bound_strict(is3, vars2, 0) ? "(" : "[")
				<< isat3_get_lower_bound(is3, vars2, 0) << ", "
				<< isat3_get_upper_bound(is3, vars2, 0)
				<< (isat3_is_upper_bound_strict(is3, vars2, 0) ? ")" : "]")
				<< endl;
		cout << "  ";
		cout << isat3_node_get_variable_name(is3, vars3)
				<< (isat3_is_lower_bound_strict(is3, vars3, 0) ? "(" : "[")
				<< isat3_get_lower_bound(is3, vars3, 0) << ", "
				<< isat3_get_upper_bound(is3, vars3, 0)
				<< (isat3_is_upper_bound_strict(is3, vars3, 0) ? ")" : "]")
				<< endl;
		cout << "  ";
		cout << isat3_node_get_variable_name(is3, vars4)
				<< (isat3_is_lower_bound_strict(is3, vars4, 0) ? "(" : "[")
				<< isat3_get_lower_bound(is3, vars4, 0) << ", "
				<< isat3_get_upper_bound(is3, vars4, 0)
				<< (isat3_is_upper_bound_strict(is3, vars4, 0) ? ")" : "]")
				<< endl;
		cout << "  ";
		cout << isat3_node_get_variable_name(is3, vars5)
				<< (isat3_is_lower_bound_strict(is3, vars5, 0) ? "(" : "[")
				<< isat3_get_lower_bound(is3, vars5, 0) << ", "
				<< isat3_get_upper_bound(is3, vars5, 0)
				<< (isat3_is_upper_bound_strict(is3, vars5, 0) ? ")" : "]")
				<< endl;
	}

	isat3_node_destroy(is3, vars1);
	isat3_node_destroy(is3, vars2);
	isat3_node_destroy(is3, vars3);
	isat3_node_destroy(is3, vars4);
	isat3_node_destroy(is3, vars5);
	isat3_deinit(is3);

}

int main(int argc, char **argv) {
	test();

//	clock_t sclock = clock();
//
//	for (int i = 0; i < argc - 1; ++i) {
//		if (!strcmp(argv[i], "-file"))
//			para::file = argv[i + 1];
//		else if (!strcmp(argv[i], "-a_w"))
//			para::a_w = stod(argv[i + 1]);
//		else if (!strcmp(argv[i], "-co_w"))
//			para::co_w = stod(argv[i + 1]);
//		else if (!strcmp(argv[i], "-e"))
//			para::e = stod(argv[i + 1]);
//		else if (!strcmp(argv[i], "-md"))
//			para::md = stod(argv[i + 1]);
//		else if (!strcmp(argv[i], "-expr_t_max"))
//			para::expr_t_max = stol(argv[i + 1]);
//		else if (!strcmp(argv[i], "-bmc_t_max"))
//			para::bmc_t_max = stol(argv[i + 1]);
//		else if (!strcmp(argv[i], "-c_min"))
//			para::c_min = stod(argv[i + 1]);
//		else if (!strcmp(argv[i], "-c_max"))
//			para::c_max = stod(argv[i + 1]);
//		else if (!strcmp(argv[i], "-c_delta"))
//			para::c_delta = stod(argv[i + 1]);
//	}
//#define NDebug0
//#ifndef NDebug0
//	para::print();
//#endif
//
//	isat3_setup();
//
//// unit test
//#define NDebug1
//#ifndef NDebug1
//	mat_engine_test();
//	isat3_face_test();
//#endif
//
//	if (para::file.empty()) {
//		cout << "No problem file is specified. (in isat_ddes.cpp)";
//		return 0;
//	}
//	isat3_ddes_problem problem(para::file);
//	cout << "Problem is loaded." << endl << endl;
//#define NDebug2
//#ifndef NDebug2
//	problem.print();
//#endif
//
//	she_ly_computer ly_cal;
//	string ly = ly_cal.ly_computation(problem);
//	if (ly.empty())
//		cout << "The discrete system is not stable."
//				<< " (unbounded safety is given in the following.)" << endl << endl;
//	else
//		cout << "Lyapunov function is calculated." << endl << endl;
//#define NDebug3
//#ifndef NDebug3
//	cout << ly << endl << endl;
//#endif
//
//	isat3_c_max_computer c_cal;
//	double c = 0;
//	if (!ly.empty()) {
//		c = c_cal.c_max_computation(problem, ly);
//		cout << "Maximum c is calculated, and it is " << c << endl << endl;
//	}
//#define NDebug4
//#ifndef NDebug4
//	cout << c << endl << endl;
//#endif
//
//	iSAT3_bmc(problem, ly + "<=" + to_string(c));
//
//	clock_t eclock = clock();
//	cout << endl << "It takes "
//			<< static_cast<double>(eclock - sclock) / CLOCKS_PER_SEC
//			<< " seconds." << endl;

	return EXIT_SUCCESS;
}

