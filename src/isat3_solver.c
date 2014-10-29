#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "isat3/isat3.h"
#include "parameters.h"
#include "isat3_solver.h"

struct isat3_node **iSAT3_decl(struct isat3 *is3, char **varNames, double *bl,
		double *bu, int varNums) {
	struct isat3_node **variable = malloc(varNums * sizeof(void*));
	for (int i = 0; i < varNums; i++) {
		variable[i] = isat3_node_create_variable_float(is3, varNames[i], bl[i],
				bu[i]);
	}
	return variable;
}

bool iSAT3_expr(char **varNames, double *bl, double *bu, int varNums,
		char *exprStr) {
	struct isat3 *is3 = isat3_init(NULL);
	struct isat3_node **vars = iSAT3_decl(is3, varNames, bl, bu, varNums);
	struct isat3_node *expr = isat3_node_create_from_string(is3, exprStr);
	i3_type_t result = isat3_solve_expr(is3, expr, exprTimeSpan);

	bool ret = false;
	if (isat3_result_contains_solution(result)) {
//		printf("%s\n",exprStr);
//		printResult(is3, result, vars, varNums);
		ret = true;
	}

	for (int i = 0; i < varNums; i++) {
		isat3_node_destroy(is3, vars[i]);
	}
	free(vars);
	isat3_node_destroy(is3, expr);
	isat3_deinit(is3);
	return ret;
}

// TODO: test bmc algorithm
bool iSAT3_bmc(char **varNames, double *bl, double *bu, int varNums,
		char *initStr, char *transStr, char *targetStr) {
	struct isat3 *is3 = isat3_init(NULL);
	struct isat3_node **vars = iSAT3_decl(is3, varNames, bl, bu, varNums);
	struct isat3_node *init = isat3_node_create_from_string(is3, initStr);
	struct isat3_node *trans = isat3_node_create_from_string(is3, transStr);
	struct isat3_node *target = isat3_node_create_from_string(is3, targetStr);
	i3_type_t result = isat3_solve_bmc(is3, init, trans, target, 0, ISAT3_MAX_TFRAME,
			bmcTimeSpan);

	bool ret = false;
	if (isat3_result_contains_solution(result)) {
//		printResult(is3, result, vars, varNums);
		ret = true;
	}

	for (int i = 0; i < varNums; i++) {
		isat3_node_destroy(is3, vars[i]);
	}
	free(vars);
	isat3_node_destroy(is3, init);
	isat3_node_destroy(is3, trans);
	isat3_node_destroy(is3, target);
	isat3_deinit(is3);
	return ret;
}

void printResult(struct isat3 *is3, i3_type_t result, struct isat3_node **vars,
		int varNum) {
	i3_tframe_t tframe = isat3_get_tframe(is3);
	printf("%s (in tframe %d)\n", isat3_get_result_string(result), tframe);
	if (isat3_result_contains_solution(result)) {
		for (i3_tframe_t t = 0; t <= tframe; t++) {
			for (int i = 0; i < varNum; i++) {
				if (vars[i] != NULL) {
					printf("tframe %d: %s %s%1.40f, %1.40f%s\n", t,
							isat3_node_get_variable_name(is3, vars[i]),
							isat3_is_lower_bound_strict(is3, vars[i], t) ?
									"(" : "[",
							isat3_get_lower_bound(is3, vars[i], t),
							isat3_get_upper_bound(is3, vars[i], t),
							isat3_is_upper_bound_strict(is3, vars[i], t) ?
									")" : "]");
				}
			}
		}
	}
}

void expr_test() {
	int varNums = 4;
	char **varNames = malloc(sizeof(void *) * varNums);
	double *bl = malloc(sizeof(void *) * varNums);
	double *bu = malloc(sizeof(void *) * varNums);
	for (int i = 0; i < varNums; i++) {
		varNames[i] = malloc(sizeof(char) * 20);
		bl[i] = BL;
		bu[i] = BU;
		sprintf(varNames[i], "x%d", i + 1);
	}
	char *exprStr = "(x1^2 = x2^3 + x3^4 + x4^5);\n" "(x1 != 0) and "
			"(x2 != 0) and (x3 != 0) and (x4 != 0);";

	printf(iSAT3_expr(varNames, bl, bu, varNums, exprStr) ? "true" : "false");
}

