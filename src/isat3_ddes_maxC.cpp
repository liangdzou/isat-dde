#include <iostream>
#include <vector>
#include <string>
#include "engine.h"

#include "isat3_ddes_maxC.h"
#include "parameters.h"
#include "matEngine.h"
#include "isat3_solver.h"

using std::vector;
using std::string;
using std::to_string;
using std::cout;
using std::endl;

// Find the largest c, s.t. "V(x,xi)<=c && !S(x)" is not satisfiable.
double get_maxC(Engine *ep) {

	string V = getString(ep, "charV");
	string target = getString(ep, "charTarget");

	// settings for iSAT3
	int row = getMInt(ep, "varNums");
	int colomn = getMInt(ep, "deg") + 1;
	double delta = getDouble(ep, "delta");
	if (row == -1 || colomn == -1 || delta <= 0) {
		printf("get row, colomn, or delta failed.");
	}
	int size = row * (colomn + 1) + 1;
	string vars[size];
	double bl[size], bu[size];

	if (row == 1) {
		for (int i = 0; i < colomn; i++) {
			vars[i] = "cb" + to_string(i+1);
			bl[i] = BL, bu[i] = BU;
		}
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < colomn; j++) {
				vars[i * colomn + j] = "cb" + to_string(i+1) + "_" + to_string(j+1);
				bl[i * colomn + j] = BL, bu[i * colomn + j] = BU;
			}
		}
	}

	for (int i = 0; i < row; i++) {
		vars[row * colomn + i] = "xi" + to_string(i+1);
		bl[row * colomn + i] = 0, bu[row * colomn + i] = delta;
	}
	vars[row * (colomn + 1)] = "t";
	bl[row * (colomn + 1)] = 0, bu[row * (colomn + 1)] = delta;

	string expr;
	double c = 0;
	double c_L = cMin;
	double c_U = cMax;
	bool isfound = false;
	for (int i = 0; c_U - c_L >= cDelta; i++) {
		c = (c_L + c_U) / 2;
		expr = V + "<=" + to_string(c) + "and" + target;
		bool sat = iSAT3_expr(vars, bl, bu, expr);
		if (!sat) {
			isfound = true;
			c_L = c;
		} else {
			c_U = c;
		}
	}

	if (!isfound)
		cout << "c can not be found between " << cMin << "and" << cMax << endl;

	return c_L;
}

