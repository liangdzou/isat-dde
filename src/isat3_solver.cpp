#include <string>

#include "parameters.h"
#include "isat3_solver.h"

using std::string;

struct isat3_node** iSAT3_decl(struct isat3* is3, string vars[], double bl[],
		double bu[], size_t size) {
	struct isat3_node* variable[vars->size()];
	for (int i = 0; i < size; i++) {
		variable[i] = isat3_node_create_variable_float(is3, vars[i].c_str(),
				bl[i], bu[i]);
	}
	return variable;
}

bool iSAT3_expr(string varsStr[], double bl[], double bu[], string exprStr) {
	struct isat3* is3 = isat3_init(NULL);
	size_t size = std::min(varsStr->size(),
			std::min(sizeof(bl) / sizeof(double), sizeof(bu) / sizeof(double)));
	struct isat3_node** vars = iSAT3_decl(is3, varsStr, bl, bu, size);
	struct isat3_node* expr = isat3_node_create_from_string(is3,
			exprStr.c_str());
	i3_type_t result = isat3_solve_expr(is3, expr, exprTimeSpan);

	bool ret = false;
	if (isat3_result_contains_solution(result)) {
		ret = true;
	}

	for (int i = 0; i < size; i++) {
		isat3_node_destroy(is3, vars[i]);
	}
	free(vars);
	isat3_node_destroy(is3, expr);
	isat3_deinit(is3);
	return ret;
}

// TODO: test bmc algorithm
bool iSAT3_bmc(string varsStr[], double bl[], double bu[], char *initStr,
		char *transStr, char *targetStr) {
	struct isat3 *is3 = isat3_init(NULL);
	size_t size = std::min(varsStr->size(),
			std::min(sizeof(bl) / sizeof(double), sizeof(bu) / sizeof(double)));
	struct isat3_node **vars = iSAT3_decl(is3, varsStr, bl, bu, size);
	struct isat3_node *init = isat3_node_create_from_string(is3, initStr);
	struct isat3_node *trans = isat3_node_create_from_string(is3, transStr);
	struct isat3_node *target = isat3_node_create_from_string(is3, targetStr);
	i3_type_t result = isat3_solve_bmc(is3, init, trans, target, 0,
	ISAT3_MAX_TFRAME, bmcTimeSpan);

	bool ret = false;
	if (isat3_result_contains_solution(result)) {
		ret = true;
	}

	for (int i = 0; i < size; i++) {
		isat3_node_destroy(is3, vars[i]);
	}
	free(vars);
	isat3_node_destroy(is3, init);
	isat3_node_destroy(is3, trans);
	isat3_node_destroy(is3, target);
	isat3_deinit(is3);
	return ret;
}

void printResult(struct isat3* is3, i3_type_t result, struct isat3_node** vars,
		int varNum) {
	i3_tframe_t tframe = isat3_get_tframe(is3);
	printf("%s (in tframe %d)\n", isat3_get_result_string(result), tframe);
	if (isat3_result_contains_solution(result)) {
		for (i3_tframe_t t = 0; t <= tframe; t++) {
			for (int i = 0; i < varNum; i++) {
				if (vars[i] != NULL) {
					std::cout << "tframe" << t
							<< isat3_node_get_variable_name(is3, vars[i])
							<< (isat3_is_lower_bound_strict(is3, vars[i], t) ?
									"(" : "[")
							<< isat3_get_lower_bound(is3, vars[i], t)
							<< isat3_get_upper_bound(is3, vars[i], t)
							<< (isat3_is_upper_bound_strict(is3, vars[i], t) ?
									")" : "]") << std::endl;
//					printf("tframe %d: %s %s%1.40f, %1.40f%s\n", t,
//							isat3_node_get_variable_name(is3, vars[i]),
//							isat3_is_lower_bound_strict(is3, vars[i], t) ?
//									"(" : "[",
//							isat3_get_lower_bound(is3, vars[i], t),
//							isat3_get_upper_bound(is3, vars[i], t),
//							isat3_is_upper_bound_strict(is3, vars[i], t) ?
//									")" : "]");
				}
			}
		}
	}
}

// TEST
void expr_test() {
	int size = 4;
	string varsStr[size];
	double bl[4], bu[size];
	for (int i = 0; i < size; i++) {
		varsStr[i] = "x" + std::to_string(i + 1);
		bl[i] = BL;
		bu[i] = BU;
	}
	string exprStr = "(x1^2 = x2^3 + x3^4 + x4^5);\n" "(x1 != 0) and "
			"(x2 != 0) and (x3 != 0) and (x4 != 0);";

	printf(iSAT3_expr(varsStr, bl, bu, exprStr) ? "true" : "false");
}

