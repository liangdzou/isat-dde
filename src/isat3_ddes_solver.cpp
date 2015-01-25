/*
 * isat3_ddes_solver.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: liang
 */

#include <math.h>
#include <string>
#include <iostream>
using std::to_string;
using std::cout;
using std::endl;
using std::begin;
using std::end;

#include "isat3_ddes_solver.h"
#include "isat3_face.h"
#include "matEngine.h"
#include "parameters.h"

string she_ly_computer::ly_computation(const isat3_ddes_problem& problem) {
	engEvalString(problem.ep,
			"[ly_str,dm] = ly_computer(a0, a1, xi, DELTA, LINEAR);");
	string ly_str = getString(problem.ep, "ly_str");
	return remove_devide(ly_str);
}

string& remove_devide(string& str) {

	for (auto it = str.begin(); it != str.end();) {
		if (*it == '/') {
			auto it_start(it + 1);
			auto it_end(it_start);
			while (*it_end >= '0' && *it_end <= '9')
				++it_end;
			double val = pow(10, (it_end - it_start))
					/ stod(string(it_start, it_end));
			string substr = "*" + to_string(val) + "*0."
					+ string(it_end - it_start - 1, '0') + "1";
			string::size_type end_pos = it - str.begin() + substr.size();
			str.replace(it, it_end, substr);
			it = str.begin() + end_pos;
		} else {
			++it;
		}
	}
	return str;
}

/* Find the largest c, s.t. "V(x,xi)<=c && !S(x)" is not satisfiable.*/
double isat3_c_max_computer::c_max_computation(isat3_ddes_problem& problem,
		const string& ly) {

	string exprStr;
	double c, c_L = c_min, c_U = c_max;
	bool isfound = false;
	for (int i = 0; c_U - c_L >= c_delta; i++) {
		c = (c_L + c_U) / 2;
		exprStr = "((" + ly + ")<=" + to_string(c) + ") and (" + problem.get_target()
				+ ");";
		bool sat = iSAT3_expr(problem.is3, problem.get_vars_begin(),
				problem.get_vars_end(), exprStr, false);
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
