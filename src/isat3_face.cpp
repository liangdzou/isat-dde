#include "isat3_face.h"

#include <string>
#include <iostream>

#include "parameters.h"

using std::string;
using std::cout;
using std::endl;

void isat3_result_print(isat3* is3, i3_type_t result, isat3_node** vars_begin,
		isat3_node** vars_end);

bool iSAT3_expr(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end,
		string exprStr, bool print) {
	isat3_node* expr = isat3_node_create_from_string(is3, exprStr.c_str());
	i3_type_t result = isat3_solve_expr(is3, expr, expr_t_max);
	isat3_node_destroy(is3, expr);
	if (print) {
		if (!isat3_result_contains_solution(result))
			cout << "NO SOLUTION." << endl;
		else {
			cout << "POSSIBLE SOLUTION:" << endl;
			isat3_result_print(is3, result, vars_begin, vars_end);
		}
	}
	return isat3_result_contains_solution(result);
}

bool iSAT3_bmc(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end,
		string initStr, string transStr, string targetStr, bool print,
		i3_tframe_t min_t = 0, i3_tframe_t max_t = ISAT3_MAX_TFRAME) {
	isat3_node *init = isat3_node_create_from_string(is3, initStr.c_str());
	isat3_node *trans = isat3_node_create_from_string(is3, transStr.c_str());
	isat3_node *target = isat3_node_create_from_string(is3, targetStr.c_str());
	i3_type_t result = isat3_solve_bmc(is3, init, trans, target, min_t, max_t,
			bmc_t_max);
	isat3_node_destroy(is3, init);
	isat3_node_destroy(is3, trans);
	isat3_node_destroy(is3, target);
	if (print) {
		if (!isat3_result_contains_solution(result))
			cout << "SAFE." << endl;
		else {
			cout << "POSSIBLE SOLUTION:" << endl;
			isat3_result_print(is3, result, vars_begin, vars_end);
		}
	}
	return isat3_result_contains_solution(result);
}

void isat3_result_print(isat3* is3, i3_type_t result, isat3_node** vars_begin,
		isat3_node** vars_end) {
	i3_tframe_t tframe = isat3_get_tframe(is3);
	if (isat3_result_contains_solution(result)) {
		cout << isat3_get_result_string(result) << " (in tframe " << tframe
				<< ")" << endl;
		for (i3_tframe_t t = 0; t <= tframe; t++) {
			cout << "tframe" << t << ":" << endl;
			for (auto vars_p = vars_begin; vars_p != vars_end; ++vars_p) {
				if (*vars_p != NULL) {
					cout << "  " << isat3_node_get_variable_name(is3, *vars_p)
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

// Unit TEST
void expr_test(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end);
void bmc_test(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end);

using std::begin;
using std::end;

void isat3_face_test() {
	isat3* is3 = isat3_init(NULL);

	const size_t size = 4;
	isat3_node* vars[size];

	for (size_t i = 0; i < size; i++) {
		string varStr = "x" + std::to_string(i + 1);
		vars[i] = isat3_node_create_variable_float(is3, varStr.c_str(), BL, BU);
	}

	// start test
	expr_test(is3, std::begin(vars), std::end(vars));
	bmc_test(is3, std::begin(vars), std::end(vars));

	for (size_t i = 0; i < size; i++) {
		isat3_node_destroy(is3, vars[i]);
	}
	isat3_deinit(is3);
	isat3_cleanup();

}

void expr_test(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end) {
	iSAT3_expr(is3, vars_begin, vars_end,
			"(x1^2 < x2^3 + x3^4 + x4^5) and (x1 = 1) and (x2 = -1) and (x3 = 1) and (x4 != 0);",
			true);
}

void bmc_test(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end) {
	iSAT3_bmc(is3, vars_begin, vars_end, "x1=0; x2=0; x3=0; x4=0;",
			"x1' = x1+1;", "x1>9;", true);
}

