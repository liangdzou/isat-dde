/*
 * isat3_ddes_getRelation.c
 *
 *  Created on: Jul 8, 2014
 *      Author: liang
 */

#include <string>
#include <vector>
#include <iostream>
#include "engine.h"

using std::string;
using std::vector;
using std::to_string;
using std::cout;
using std::endl;

#include "isat3_ddes_problem.h"
#include "matEngine.h"
#include "isat3_face.h"
#include "parameters.h"

isat3_ddes_problem::isat3_ddes_problem(string script) {

	if (!(ep = engOpen("\0")))
		cout << "Can't start MATLAB engine" << endl;
	engEvalString(ep, "addpath('./matlabFunctions');");
	engEvalString(ep, script.c_str());
	engEvalString(ep, "vars_num = size(INIT,1);");

	int row = getInt(ep, "vars_num");
	int column = getInt(ep, "DEG") + 1;
	if (row == 0 || column == 0) {
		printf("Get row or column failed. (in file isat3_ddes_problem.cpp)");
	}

	isat3_setup();
	is3 = isat3_init(NULL);
	vars_def(row, column);
	vars_init(row, column);
	trans_def(row, column);
	engEvalString(ep, "target_str = target(TARGET,expr0);");
	target = getString(ep, "target_str");

}

void isat3_ddes_problem::vars_def(int row, int column) {
	vars_begin = new isat3_node*[row * (column + 1) + 1];
	double delta = getDouble(ep, "DELTA");

	if (row == 1) {
		for (int i = 0; i < column; i++) {
			string var_str = "cb" + to_string(i + 1);
			vars_begin[i] = isat3_node_create_variable_float(is3,
					var_str.c_str(), BL, BU);
		}
		vars_begin[column] = isat3_node_create_variable_float(is3, "xi1", 0,
				delta);
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				string var_str = "cb" + to_string(i + 1) + "_"
						+ to_string(j + 1);
				vars_begin[i * (column + 1) + j] =
						isat3_node_create_variable_float(is3, var_str.c_str(),
								BL, BU);
			}
			string var_str = ("xi" + to_string(i + 1));
			vars_begin[i * (column + 1) + column] =
					isat3_node_create_variable_float(is3, var_str.c_str(), 0,
							delta);
		}
	}

	string var_str("t");
	vars_begin[row * (column + 1)] = isat3_node_create_variable_float(is3,
			var_str.c_str(), 0, delta);
	vars_end = vars_begin + row * (column + 1) + 1;
}

void isat3_ddes_problem::vars_init(int row, int column) {
	init = "";
	double init_val[row];
	for (int i = 0; i < row; i++) {
		string init_script = "init_i = INIT(" + to_string(i + 1) + ",1)";
		engEvalString(ep, init_script.c_str());
		init_val[i] = getDouble(ep, "init_i");
	}

	if (row == 1) {
		for (int i = 0; i < column - 1; i++) {
			init += "cb" + to_string(i + 1) + " = 0;\n";
		}
		init += "cb" + to_string(column) + " = " + to_string(init_val[0]);
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column - 1; j++) {
				init += "cb" + to_string(i + 1) + "_" + to_string(j + 1)
						+ " = 0;\n";
			}
			init += "cb" + to_string(i + 1) + "_" + to_string(column) + " = "
					+ to_string(init_val[i]);
		}
	}

}

void isat3_ddes_problem::trans_def(int row, int column) {
	trans = "";
	engEvalString(ep, "[a0,a1,expr0] = trans(DDES, INIT, DELTA, DEG);");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			string a0_i = "cb_i = char(a0(" + to_string(i + 1) + ","
					+ to_string(j + 1) + "))";
			string a1_i = "ca_i = char(a1(" + to_string(i + 1) + ","
					+ to_string(j + 1) + "))";
			engEvalString(ep, a0_i.c_str());
			engEvalString(ep, a1_i.c_str());
			string coefbf = getString(ep, "cb_i");
			string coefaf = getString(ep, "ca_i");
			trans += coefbf + "' = " + coefaf + ";";
		}
	}

}

void isat3_ddes_problem::print() {
	cout << this->init << "\n\n";
	cout << this->trans << "\n\n";
	cout << this->target << endl;
}

