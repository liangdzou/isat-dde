/*
 * isat3_ddes_solver.h
 *
 *  Created on: Jan 16, 2015
 *      Author: liang
 */

#ifndef ISAT3_DDES_SOLVER_H_
#define ISAT3_DDES_SOLVER_H_

#include <string>
using std::string;

#include "isat3_ddes_problem.h"

class ly_computer {
public:
	string ly_computation(isat3_ddes_problem);
};

class c_max_computer {
public:
	double c_max_computation(isat3_ddes_problem, string ly, string target);
};

class she_ly_computer: ly_computer {
	string ly_computation(isat3_ddes_problem);
};

class isat3_c_max_computer: c_max_computer {
	double c_max_computation(isat3_ddes_problem, string ly, string target);
};

#endif /* ISAT3_DDES_SOLVER_H_ */