/*
 * isat3_solver.h
 *
 *  Created on: Jul 9, 2014
 *      Author: liang
 */

#ifndef ISAT3_FACE_H_
#define ISAT3_FACE_H_

#include "isat3/isat3.h"
#include "isat3_ddes_problem.h"

#include <string>

bool iSAT3_expr(isat3_ddes_problem& problem, const std::string& exprStr, bool print = true);
bool iSAT3_bmc(isat3_ddes_problem& problem, const std::string& termStr, bool print = true);
void isat3_result_print(isat3_ddes_problem& problem, i3_type_t result);
extern void isat3_face_test();

#endif /* ISAT3_SOLVER_H_ */
