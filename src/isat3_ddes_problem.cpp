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

#include "matEngine.h"

isat3_ddes_problem::isat3_ddes_problem() {

	if (!(ep = engOpen("\0")))
		cout << "Can't start MATLAB engine" << endl;
	engEvalString(ep, "addpath('./matlabFunctions');");
	engEvalString(ep, "impl();");

	row = getInt(ep, "varNums");
	column = getInt(ep, "deg") + 1;
	if (row == 0 || column == 0) {
		printf("Get row or column failed. (in file isat3_ddes_iSAT3.cpp)");
	}

	isat3_setup();
	is3 = isat3_init(NULL);
	vars_def();
	vars_init();
	trans_def();
	target = getString(ep, "charTarget");

}

void isat3_ddes_problem::vars_def() {
	double delta = getDouble(ep, "delta");

	if (row == 1) {
		for (int i = 0; i < column; i++) {
			string var_str = "cb" + to_string(i + 1);
			isat3_node_create_variable_float(is3, var_str.c_str(), BL, BU);
		}
		isat3_node_create_variable_float(is3, "xi1", 0, delta);
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				string var_str = "cb" + to_string(i + 1) + "_"
						+ to_string(j + 1);
				isat3_node_create_variable_float(is3, var_str.c_str(), BL, BU);
			}
			string var_str = ("xi" + to_string(i + 1));
			isat3_node_create_variable_float(is3, var_str.c_str(), 0, delta);
		}
	}

	string var_str("t");
	isat3_node_create_variable_float(is3, var_str.c_str(), 0, delta);

}

void isat3_ddes_problem::vars_init() {
	init = "";
	double iVal[row];
	for (int i = 0; i < row; i++) {
		string getiVarScript = "initVal = init(1," + to_string(i + 1) + ")";
		engEvalString(ep, getiVarScript.c_str());
		iVal[i] = getDouble(ep, "initVal");
	}

	if (row == 1) {
		for (int i = 0; i < column - 1; i++) {
			init += "cb" + to_string(i + 1) + " = 0;\n";
		}
		init += "cb" + to_string(column) + " = " + to_string(iVal[0]);
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column - 1; j++) {
				init += "cb" + to_string(i + 1) + "_" + to_string(j + 1)
						+ " = 0;\n";
			}
			init += "cb" + to_string(i + 1) + "_" + to_string(column) + " = "
					+ to_string(iVal[i]);
		}
	}

}

void isat3_ddes_problem::trans_def() {
	trans = "";
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			string getBF = "coefbf = char(coefBefore(" + to_string(i + 1) + ","
					+ to_string(j + 1) + "))";
			string getAF = "coefaf = char(coefAfter(" + to_string(i + 1) + ","
					+ to_string(j + 1) + "))";
			engEvalString(ep, getBF.c_str());
			engEvalString(ep, getAF.c_str());
			string coefbf = getString(ep, "coefbf");
			string coefaf = getString(ep, "coefaf");
			trans += coefbf + "' = " + coefaf + ";\n";
		}
	}

}

void isat3_ddes_problem::print() {
	cout << this->init << endl;
	cout << this->trans << endl;
	cout << this->target << endl;
}

