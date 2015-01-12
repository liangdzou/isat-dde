/*
 * isat3_solver.h
 *
 *  Created on: Jul 9, 2014
 *      Author: liang
 */

#ifndef ISAT3_SOLVER_H_
#define ISAT3_SOLVER_H_

#include "isat3/isat3.h"

extern bool iSAT3_expr(string varsStr[], double bl[], double bu[],
		string exprStr);
extern bool iSAT3_bmc(string varsStr[], double bl[], double bu[], char *initStr,
		char *transStr, char *targetStr);
extern void expr_test();
extern void printResult(struct isat3* is3, i3_type_t result,
		struct isat3_node** vars, int varNum);

#endif /* ISAT3_SOLVER_H_ */
