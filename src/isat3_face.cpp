#include "isat3_face.h"

#include <array>
#include <string>
#include <iostream>

#include "parameters.h"
#include "isat3_ddes_problem.h"

using namespace std;

void isat3_result_print(isat3_ddes_problem& problem, i3_type_t result);
void isat3_result_print_last(isat3_ddes_problem& problem, i3_type_t result);

bool iSAT3_expr(isat3_ddes_problem& problem, const string& exprStr,
		bool print) {
	isat3* is3 = problem.is3;
	isat3_node* expr = isat3_node_create_from_string(is3, exprStr.c_str());
	i3_type_t result = isat3_solve_expr(is3, expr, para::get_expr_t_max());
	isat3_node_destroy(is3, expr);
	if (print) {
		if (!isat3_result_contains_solution(result))
			cout << "NO SOLUTION." << endl;
		else {
			cout << isat3_get_result_string(result) << endl;
			isat3_result_print_last(problem, result);
		}
	}
	return isat3_result_contains_solution(result);
}

bool iSAT3_bmc(isat3_ddes_problem& problem, const string& termStr, bool print) {
	isat3* is3 = problem.is3;
	auto vars_begin = problem.get_vars_begin();
	auto vars_end = problem.get_vars_end();
	string target_str = problem.get_target() + ";";

//	if (termStr[0] == '<') {
//		problem.reset_vars();
//		cout << "Decl:" << problem.get_decl() << endl;
//		cout << "Init:" << problem.get_init() << endl;
//		cout << "Trans:" << problem.get_trans() << endl;
//		cout << "Target:" << target_str << endl;
//		isat3_node *init = isat3_node_create_from_string(is3,
//				problem.get_init().c_str());
//		isat3_node *trans = isat3_node_create_from_string(is3,
//				problem.get_trans().c_str());
//		target_str = "2<1;";
//		isat3_node *target = isat3_node_create_from_string(is3,
//				target_str.c_str());
//		i3_type_t result = isat3_solve_bmc(is3, init, trans, target, 0,
//				para::get_bound(), para::get_bmc_t_max());
//		if (!isat3_result_contains_solution(result)) {
//			cout << "SAFE within first " << to_string(para::get_bound())
//					<< "* DELTA seconds." << endl;
//			isat3_node_destroy(is3, target);
//			return true;
//		} else {
//			i3_tframe_t tframe = isat3_get_tframe(is3);
//			cout << "UNSAFE.  [target is reachable with in the given intervals]"
//					<< " (in tframe " << tframe << ")" << endl;
//			cout << "Target:" << target_str << endl;
//			isat3_result_print(problem, result);
//			return false;
//		}
//	}

	isat3_node *init = isat3_node_create_from_string(is3,
			problem.get_init().c_str());
	isat3_node *trans = isat3_node_create_from_string(is3,
			problem.get_trans().c_str());
	string target_term_str = "(" + problem.get_target() + ") or (" + termStr
			+ ");";
	isat3_node *target_term = isat3_node_create_from_string(is3,
			target_term_str.c_str());
	i3_type_t result = isat3_solve_bmc(is3, init, trans, target_term, 0,
	ISAT3_MAX_TFRAME, para::get_bmc_t_max());

#define NDebug_BMC
#ifndef NDebug_BMC
	if (print) {
		cout << "Last frame of termination, tframe" << isat3_get_tframe(is3) << ":" << endl;
		isat3_result_print_last(problem, result);
	}
#endif

	isat3* is3_local = isat3_init(NULL);
	isat3_node* vars[vars_end - vars_begin];
	i3_tframe_t tframe = isat3_get_tframe(is3);
	for (size_t i = 0; vars_begin + i < vars_end; ++i) {
		if (vars_begin[i] == NULL) {
			cout << "Some variable is NULL. (in isat3_face.cpp)" << endl;
		}
		vars[i] = isat3_node_create_variable_float(is3_local,
				isat3_node_get_variable_name(is3, vars_begin[i]),
				isat3_get_lower_bound(is3, vars_begin[i], tframe),
				isat3_get_upper_bound(is3, vars_begin[i], tframe));
	}
	string term_str = termStr + ";";
	isat3_node *target = isat3_node_create_from_string(is3_local,
			target_str.c_str());
	isat3_node *term = isat3_node_create_from_string(is3_local,
			term_str.c_str());
	i3_type_t no_ret = isat3_solve_expr(is3_local, target,
			para::get_expr_t_max());
//	i3_type_t yes_ret = isat3_solve_expr(is3_local, term,
//			para::get_expr_t_max());
	for (size_t i = 0; vars_begin + i < vars_end; ++i)
		isat3_node_destroy(is3_local, vars[i]);
	isat3_node_destroy(is3_local, target);
	isat3_node_destroy(is3_local, term);
	isat3_deinit(is3_local);

	if (isat3_result_contains_solution(no_ret)) {
		cout << "UNSAFE.  [target is reachable with all values"
				<< " in the given intervals]" << " (in tframe " << tframe << ")"
				<< endl;
		isat3_result_print(problem, result);
	} else {
		cout << "SAFE." << endl;
	}

	isat3_node_destroy(is3, init);
	isat3_node_destroy(is3, trans);
	isat3_node_destroy(is3, target_term);
	return !isat3_result_contains_solution(no_ret);
}

void isat3_result_print(isat3_ddes_problem& problem, i3_type_t result) {
	isat3* is3 = problem.is3;
	auto vars_begin = problem.get_vars_begin();
	auto vars_end = problem.get_vars_end();
	i3_tframe_t tframe = isat3_get_tframe(is3);
	if (isat3_result_contains_solution(result)) {
		for (i3_tframe_t t = 0; t <= tframe; t++) {
			cout << "  tframe" << t << ":" << endl;
			for (auto vars_p = vars_begin; vars_p != vars_end; ++vars_p) {
				if (*vars_p != NULL) {
					cout << "    " << isat3_node_get_variable_name(is3, *vars_p)
							<< (isat3_is_lower_bound_strict(is3, *vars_p, t) ?
									"(" : "[")
							<< isat3_get_lower_bound(is3, *vars_p, t) << ", "
							<< isat3_get_upper_bound(is3, *vars_p, t)
							<< (isat3_is_upper_bound_strict(is3, *vars_p, t) ?
									")" : "]") << endl;
				}
			}
		}
	}
}

void isat3_result_print_last(isat3_ddes_problem& problem, i3_type_t result) {
	isat3* is3 = problem.is3;
	auto vars_begin = problem.get_vars_begin();
	auto vars_end = problem.get_vars_end();
	i3_tframe_t tframe = isat3_get_tframe(is3);
	if (isat3_result_contains_solution(result)) {
		for (auto vars_p = vars_begin; vars_p != vars_end; ++vars_p) {
			if (*vars_p != NULL) {
				cout << "  " << isat3_node_get_variable_name(is3, *vars_p)
						<< (isat3_is_lower_bound_strict(is3, *vars_p, tframe) ?
								"(" : "[")
						<< isat3_get_lower_bound(is3, *vars_p, tframe) << ", "
						<< isat3_get_upper_bound(is3, *vars_p, tframe)
						<< (isat3_is_upper_bound_strict(is3, *vars_p, tframe) ?
								")" : "]") << endl;
			}
		}
	}
}

// Unit TEST
void expr_test(isat3_ddes_problem& problem);
void bmc_test(isat3_ddes_problem& problem);

using std::begin;
using std::end;

void isat3_face_test() {
	isat3_ddes_problem problem(para::get_file());
	expr_test(problem);
	bmc_test(problem);
}

void expr_test(isat3_ddes_problem& problem) {
	iSAT3_expr(problem,
//			"(cb1^2 < cb2^3 + cb3^4) and (cb1 = 1) and (cb2 = -1) and (cb3 = 1);",
			"(2<1);", true);
}

void bmc_test(isat3_ddes_problem& problem) {
	iSAT3_bmc(problem, "1<909", true);
}

