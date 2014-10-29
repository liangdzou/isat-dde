/*
 * isat3_solver.h
 *
 *  Created on: Jul 9, 2014
 *      Author: liang
 */

#ifndef ISAT3_SOLVER_H_
#define ISAT3_SOLVER_H_

#include "isat3/isat3.h"

bool iSAT3_expr(char **varNames, double *bl, double *bu, int varNums,
		char *exprStr);
void expr_test();
void printResult(struct isat3 *is3, i3_type_t result, struct isat3_node **vars,
		int varNum);

#endif /* ISAT3_SOLVER_H_ */
