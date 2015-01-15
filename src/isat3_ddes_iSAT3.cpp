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

#include "isat3_ddes_iSAT3.h"
#include "matEngine.h"
#include "isat3/isat3.h"
#include "parameters.h"

int row, column, size;

void setSize(Engine *ep) {
	row = getMInt(ep, "varNums");
	column = getMInt(ep, "deg") + 1;
	if (row == 0 || column == 0) {
		printf("Get row or column failed. (in file isat3_ddes_iSAT3.cpp)");
	}
	size = row * (column + 1) + 1;
}

int setDecl(Engine* ep, string vars[], double* bl, double* bu) {
	setSize(ep);

	double delta = getDouble(ep, "delta");

	if (row == 1) {
		for (int i = 0; i < column; i++) {
			vars[i] = ("cb" + to_string(i + 1));
			bl[i] = BL, bu[i] = BU;
		}
		vars[column] = "xi1";
		bl[column] = 0, bu[column] = delta;
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				vars[i * (column + 1) + j] = "cb" + to_string(i + 1) + "_"
						+ to_string(j + 1);
				bl[i * (column + 1) + j] = BL, bu[i * (j + 1)] = BU;
			}
			vars[i * (column + 1) + column] = ("xi" + to_string(i + 1));
			bl[i * (column + 1) + column] = 0;
			bu[i * (column + 1) + column] = delta;
		}
	}

	vars[row * (column + 1)] = "t";
	bl[row * (column + 1)] = 0, bu[row * (column + 1)] = delta;

	return size;
}

string getInit(Engine *ep) {
	string init = "";
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

	return init;
}

string getTrans(Engine *ep) {
	string relation = "";
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
			relation += coefbf + "' = " + coefaf + ";\n";
		}
	}

	return relation;
}

string getDangerTarget(Engine *ep) {
	return getString(ep, "charTarget");
}

using std::cout;
using std::endl;

void iSAT3StrTest(Engine *ep) {
	setSize(ep);

	string vars[size];
	double bl[size], bu[size];
	setDecl(ep, vars, bl, bu);
	for (int i = 0; i < size; i++)
		cout << vars[i] << ": [" << bl[i] << ", " << bu[i] << "]" << endl;

	cout << getInit(ep) << "\n" << getTrans(ep) << "\n" << getDangerTarget(ep)
			<< endl;
}

