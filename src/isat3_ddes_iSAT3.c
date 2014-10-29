/*
 * isat3_ddes_getRelation.c
 *
 *  Created on: Jul 8, 2014
 *      Author: liang
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "engine.h"

#include "isat3_ddes_iSAT3.h"
#include "matEngine.h"
#include "isat3/isat3.h"
#include "parameters.h"

int row = -1;
int column = -1;

void setSize(Engine *ep) {
	row = getInt(ep, "varNums");
	column = getInt(ep, "deg") + 1;
	if (row == -1 || column == -1) {
		printf("get row or column failed.");
	}
}

int setDecl(Engine *ep, char ***varNamesPointer, double **blPointer, double **buPointer) {
	setSize(ep);

	int varNums = row * (column + 1) + 1;
	char ** varNames = malloc(sizeof(void *) * varNums);
	double *bl = malloc(sizeof(double) * varNums);
	double *bu = malloc(sizeof(double) * varNums);

	double delta = getDouble(ep, "delta");

	if (row == 1) {
		for (int i = 0; i < column; i++) {
			varNames[i] = malloc(sizeof(char) * 256);
			sprintf(varNames[i], "cb%d", i + 1);
			bl[i] = BL;
			bu[i] = BU;
		}
		varNames[column] = malloc(sizeof(char) * 256);
		sprintf(varNames[column], "xi1");
		bl[column] = 0;
		bu[column] = delta;
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column - 1; j++) {
				varNames[i * column + j] = malloc(sizeof(char) * 256);
				sprintf(varNames[i * column + j], "cb%d_%d", i + 1, j + 1);
				bl[i * column + j] = BL;
				bu[i * column + j] = BU;
			}
			varNames[row * column + i] = malloc(sizeof(char) * 256);
			sprintf(varNames[row * column + i], "xi%d", i + 1);
			bl[row * column + i] = 0;
			bu[row * column + i] = delta;
		}
	}

	varNames[row * (column + 1)] = malloc(sizeof(char) * 256);
	sprintf(varNames[row * (column + 1)], "t");
	bl[row * (column + 1)] = 0;
	bu[row * (column + 1)] = delta;

	*varNamesPointer = varNames;
	*blPointer = bl;
	*buPointer = bu;

	return varNums;
}

char *getInit(Engine *ep) {
	char **init = malloc(sizeof(char*) * (row * column + 1));
	double initVal[row];
	for (int i = 0; i < row; i++) {
		char getInitVal[256];
		sprintf(getInitVal, "initVal = init(1,%d)", i + 1);
		engEvalString(ep, getInitVal);
		initVal[i] = getDouble(ep, "initVal");
	}

	if (row == 1) {
		for (int i = 0; i < column - 1; i++) {
			init[i] = malloc(sizeof(char) * 256);
			sprintf(init[i], "cb%d = 0;\n", i + 1);
		}
		init[column - 1] = malloc(sizeof(char) * 256);
		sprintf(init[column - 1], "cb%d = %f;\n", column, initVal[0]);
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column - 1; j++) {
				init[i * column + j] = malloc(sizeof(char) * 256);
				sprintf(init[i * column + j], "cb%d_%d = 0;\n", i + 1, j + 1);
			}
			init[i * column + column - 1] = malloc(sizeof(char) * 256);
			sprintf(init[i * column + column - 1], "cb%d_%d = %f;\n", i + 1,
					column, initVal[i]);
		}
	}

	init[row * column] = NULL;
	return getStrFromStrArray(init);
}

char *getTrans(Engine *ep) {
	char **relation = malloc(sizeof(char*) * (row * column + 1));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			char getBF[256], getAF[256];
			sprintf(getBF, "coefbf = char(coefBefore(%d,%d))", i + 1, j + 1);
			sprintf(getAF, "coefaf = char(coefAfter(%d,%d))", i + 1, j + 1);
			engEvalString(ep, getBF);
			engEvalString(ep, getAF);
			char *coefbf = getString(ep, "coefbf");
			char *coefaf = getString(ep, "coefaf");
			relation[i * column + j] = malloc(
					sizeof(char) * (strlen(coefbf) + strlen(coefaf) + 10));
			sprintf(relation[i * column + j], "%s' = %s;\n", coefbf, coefaf);
		}
	}

	relation[row * column] = NULL;
	return getStrFromStrArray(relation);
}

char *getDangerTarget(Engine *ep) {
	return getString(ep, "charTarget");
}

char *getStrFromStrArray(char **strArray) {
	int size = 0;
	for (int i = 0; strArray[i]; i++) {
		size += strlen(strArray[i]);
	}
	char *initStr = (char *)malloc(sizeof(char) * size + 1);
	initStr[0] = '\0';
	for (int i = 0; strArray[i]; i++) {
		sprintf(initStr, "%s%s", initStr, strArray[i]);
	}
	printf("\n");
//	freeTable(strArray);

	return initStr;
}

int getLength(char **strArray) {
	int len = 0;
	while (*strArray) {
		len += strlen(*strArray);
		strArray++;
	}
	return len;
}

void printStrArray(char **strArray) {
	while (*strArray) {
		printf("%s", *strArray);
		strArray++;
	}
	printf("\n");
}

void strArrayCopy(char *SA1, char **SA2) {
	while (*SA2) {
		sprintf(SA1, "%s%s", SA1, *SA2);
		SA2++;
	}
}

void freeTable(char **strArray) {
	for (int i = 0; strArray[i]; i++) {
		free(strArray[i]);
	}
	free(strArray);
}

void iSAT3StrTest(Engine *ep) {
	setSize(ep);

	char **varNames = NULL;
	double *bl = NULL, *bu = NULL;
	int varNums = setDecl(ep, &varNames, &bl, &bu);
	for (int i = 0; i < varNums; i++) {
		printf("%s: [%f,%f]\n", varNames[i], bl[i], bu[i]);
	}
	freeTable(varNames);
	free(bl);
	free(bu);

	char *init = getInit(ep);
	char *rel = getTrans(ep);
	char *safeProp = getDangerTarget(ep);

	printf("%s\n%s\n%s\n", init, rel, safeProp);

	free(init);
	free(rel);
	free(safeProp);
//	free(isat3BMCText);

}

