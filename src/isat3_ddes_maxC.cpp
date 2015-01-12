#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "engine.h"

#include "isat3_ddes_maxC.h"
#include "parameters.h"
#include "matEngine.h"
#include "isat3_solver.h"

// Find the largest c, s.t. "V(x,xi)<=c && !S(x)" is not satisfiable.
double get_maxC(Engine *ep, char *V, char*target) {

	// settings for iSAT3
	int row = getInt(ep, "varNums");
	int colomn = getInt(ep, "deg") + 1;
	double delta = getDouble(ep, "delta");
	if (row == -1 || colomn == -1 || delta <= 0) {
		printf("get row, colomn, or delta failed.");
	}
	int varNums = row * (colomn + 1) + 1;
	char **varNames = malloc(sizeof(void*) * varNums);
	double *bl = malloc(sizeof(void*) * varNums);
	double *bu = malloc(sizeof(void*) * varNums);

	if (row == 1) {
		for (int i = 0; i < colomn; i++) {
			varNames[i] = mxCalloc(256, sizeof(char));
			sprintf(varNames[i], "cb%d", i + 1);
			bl[i] = BL;
			bu[i] = BU;
		}
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < colomn; j++) {
				varNames[i * colomn + j] = mxCalloc(256, sizeof(char));
				sprintf(varNames[i * colomn + j], "cb%d_%d", i + 1, j + 1);
				bl[i * colomn + j] = BL;
				bu[i * colomn + j] = BU;
			}
		}
	}
	for (int i = 0; i < row; i++) {
		varNames[row * colomn + i] = mxCalloc(256, sizeof(char));
		sprintf(varNames[row * colomn + i], "xi%d", i + 1);
		bl[row * colomn + i] = 0;
		bu[row * colomn + i] = delta;
	}
	varNames[row * (colomn + 1)] = "t";
	bl[row * (colomn + 1)] = 0;
	bu[row * (colomn + 1)] = delta;
	char *expr = malloc(sizeof(char) * (strlen(V) + strlen(target) + 128));

	double c = 0;
	double c_L = cMin;
	double c_U = cMax;
	bool isfound = false;
	for (int i = 0; c_U - c_L >= cDelta; i++) {
		c = (c_L + c_U) / 2;
		sprintf(expr, "%s <= %f and (%s);", V, c, target);
		bool sat = iSAT3_expr(varNames, bl, bu, varNums, expr);
		if (!sat) {
			isfound = true;
			c_L = c;
		} else {
			c_U = c;
		}
	}

	if (!isfound)
		printf("c can not be found between %f and %f", cMin, cMax);

	return c_L;
}

double linear_maxC(Engine *ep) {
	char *V = getString(ep, "charV");
	char *target = getString(ep, "charTarget");
	double c = get_maxC(ep, V, target);
	return c;
}

// TODO: polynomial Lyapunov function
double poly_maxC(Engine *ep) {
	char *V = getString(ep, "charV");
	char *S = getString(ep, "charTarget");
	int c = get_maxC(ep, V, S);
	return c;
}

