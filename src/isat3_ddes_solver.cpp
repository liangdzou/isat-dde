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

string she_ly_computer::ly_computation(isat3_ddes_problem& problem) {
	string command = "[ly_str,md] = ly_computer(a0, a1, xi, DELTA, LINEAR, "
			+ to_string(para::get_a_w()) + ", " + to_string(para::get_co_w())
			+ ", " + to_string(para::get_e()) + ", " + to_string(para::get_md())
			+ ");";

	int linear = getInt(problem.ep, "LINEAR");
	if (!linear) {
		string exprStr("");
		isat3* is3 = problem.is3;
		for (auto it = problem.get_vars_begin(); it != problem.get_vars_end();
				++it) {
			if (!*it) {
				cout << "Some variable is NULL. (in isat3_ddes_solver.cpp)"
						<< endl;
			} else {
				string var_name = isat3_node_get_variable_name(is3, *it);
				if (var_name.find("cb") != string::npos)
					exprStr += "and (" + var_name + "<="
							+ to_string(para::get_e()) + ") and (" + var_name
							+ ">=" + to_string(-para::get_e()) + ")";
			}
		}
		exprStr = "(" + exprStr.substr(exprStr.find('(')) + ") and ("
				+ problem.get_target() + ");";
		isat3_node *term = isat3_node_create_from_string(problem.is3,
				exprStr.c_str());
		i3_type_t ret = isat3_solve_expr(problem.is3, term,
				para::get_expr_t_max());
		if (!linear && isat3_result_contains_solution(ret))
			cout << "Parameter \'e\' is too big,"
					<< " the result may not be accurate." << endl;
	}

	engEvalString(problem.ep, command.c_str());
	string ly_str = getString(problem.ep, "ly_str");
	return remove_devide(ly_str);
}

/* Find the largest c, s.t. "V(x,xi)<=c && !S(x)" is not satisfiable.*/
double isat3_c_max_computer::c_max_computation(isat3_ddes_problem& problem,
		const string& ly) {

	string exprStr;

	// TODO: solve this bug.
	cout << "strange test!!!" << endl;
	cout << (exprStr = "((" + ly + ")<=856) and (" + problem.get_target() + ");") << endl;
	iSAT3_expr(problem, exprStr, true);
	cout << (exprStr = "((" + ly + ")<=500) and (" + problem.get_target() + ");") << endl;
	iSAT3_expr(problem, exprStr, true);

	double c, c_L = para::get_c_min(), c_U = para::get_c_max();
	bool isfound = false;
	cout << "Computing maximum c:" << endl;
	for (int i = 0; c_U - c_L >= para::get_c_delta(); i++) {
		c = 0.5 * c_L + 0.5 * c_U;
		exprStr = "((" + ly + ")<=" + to_string(c) + ") and ("
				+ problem.get_target() + ");";
		cout << "Try c =" << c << ", c is between " << c_L << " and " << c_U
				<< endl << "  ";
		bool sat = iSAT3_expr(problem, exprStr, true);
		if (!sat) {
			isfound = true;
			c_L = c;
		} else {
			c_U = c;
		}
	}

	if (!isfound)
		cout << "c can not be found between " << para::get_c_min() << "and"
				<< para::get_c_max() << endl;

	return c_L;

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
