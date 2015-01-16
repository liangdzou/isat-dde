#include "isat3_face.h"

#include <string>
#include <iostream>

#include "parameters.h"

using std::string;

bool iSAT3_expr(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end,
		string exprStr, bool print) {
	isat3_node* expr = isat3_node_create_from_string(is3, exprStr.c_str());
	i3_type_t result = isat3_solve_expr(is3, expr, expr_t_max);
	isat3_node_destroy(is3, expr);
	if (print)
		isat3_result_print(is3, result, vars_begin, vars_end);
	return isat3_result_contains_solution(result);
}

// TODO: test bmc algorithm
bool iSAT3_bmc(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end,
		string initStr, string transStr, string targetStr, bool print) {
	isat3_node *init = isat3_node_create_from_string(is3, initStr.c_str());
	isat3_node *trans = isat3_node_create_from_string(is3, transStr.c_str());
	isat3_node *target = isat3_node_create_from_string(is3, targetStr.c_str());
	i3_type_t result = isat3_solve_bmc(is3, init, trans, target, 0,
	ISAT3_MAX_TFRAME, bmc_t_max);
	isat3_node_destroy(is3, init);
	isat3_node_destroy(is3, trans);
	isat3_node_destroy(is3, target);
	if (print)
		isat3_result_print(is3, result, vars_begin, vars_end);
	return isat3_result_contains_solution(result);
}

void isat3_result_print(isat3* is3, i3_type_t result, isat3_node** vars_begin,
		isat3_node** vars_end) {
	i3_tframe_t tframe = isat3_get_tframe(is3);
	printf("%s (in tframe %d)\n", isat3_get_result_string(result), tframe);
	if (isat3_result_contains_solution(result)) {
		for (i3_tframe_t t = 0; t <= tframe; t++) {
			for (auto vars_p = vars_begin; vars_p != vars_end; ++vars_p) {
				if (*vars_p != NULL) {
					std::cout << "tframe" << t
							<< isat3_node_get_variable_name(is3, *vars_p)
							<< (isat3_is_lower_bound_strict(is3, *vars_p, t) ?
									"(" : "[")
							<< isat3_get_lower_bound(is3, *vars_p, t)
							<< isat3_get_upper_bound(is3, *vars_p, t)
							<< (isat3_is_upper_bound_strict(is3, *vars_p, t) ?
									")" : "]") << std::endl;
				}
			}
		}
	}
}

// Unit TEST
using std::cout;
using std::endl;

void expr_test(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end);

void unit_test() {
	isat3_setup();
	isat3* is3 = isat3_init(NULL);

	const size_t size = 4;
	isat3_node* vars[size];

	for (size_t i = 0; i < size; i++) {
		string varStr = "x" + std::to_string(i + 1);
		vars[i] = isat3_node_create_variable_float(is3, varStr.c_str(), BL, BU);
	}

	// start test
	expr_test(is3, std::begin(vars), std::end(vars));

	for (size_t i = 0; i < size; i++) {
		isat3_node_destroy(is3, vars[i]);
	}
	isat3_deinit(is3);
	isat3_cleanup();

}

void expr_test(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end) {
	string exprStr = "(x1^2 = x2^3 + x3^4 + x4^5);\n" "(x1 != 0) and "
			"(x2 != 0) and (x3 != 0) and (x4 != 0);";
	cout << (iSAT3_expr(is3, vars_begin, vars_end, exprStr, true) ? "true" : "false") << endl;
}

