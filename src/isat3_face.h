/*
 * isat3_solver.h
 *
 *  Created on: Jul 9, 2014
 *      Author: liang
 */

#ifndef ISAT3_SOLVER_H_
#define ISAT3_SOLVER_H_

#include "isat3/isat3.h"

#include <string>
using std::string;

extern bool iSAT3_expr(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end,
		string exprStr, bool print);
extern bool iSAT3_bmc(isat3* is3, isat3_node** vars_begin, isat3_node** vars_end,
		string initStr, string transStr, string targetStr, bool print);
extern void expr_test();


#endif /* ISAT3_SOLVER_H_ */
