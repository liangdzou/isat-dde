/*
 * isat3_ddes_solver.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: liang
 */

#include <string>
#include <iostream>
using std::to_string;
using std::cout;
using std::endl;

#include "isat3_ddes_solver.h"
#include "isat3/isat3.h"
#include "isat3_face.h"
#include "matEngine.h"
#include "parameters.h"

string she_ly_computer::ly_computation(isat3_ddes_problem problem) {
	return getString(problem.ep, "charV");
}

/* Find the largest c, s.t. "V(x,xi)<=c && !S(x)" is not satisfiable.*/
double isat3_c_max_computer::c_max_computation(isat3_ddes_problem problem,
		string ly, string target) {

	string exprStr;
	double c, c_L = c_min, c_U = c_max;
	bool isfound = false;
	for (int i = 0; c_U - c_L >= c_delta; i++) {
		c = (c_L + c_U) / 2;
		exprStr = ly + "<=" + to_string(c) + "and (" + target + ")";
		isat3_node* expr = isat3_node_create_from_string(problem.is3,
				exprStr.c_str());
		bool sat = isat3_solve_expr(problem.is3, expr, expr_t_max);
		if (!sat) {
			isfound = true;
			c_L = c;
		} else {
			c_U = c;
		}
	}

	if (!isfound)
		cout << "c can not be found between " << c_min << "and" << c_max
				<< endl;

	return c_L;

}
