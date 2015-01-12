/*
 * isat3_ddes_getRelation.c
 *
 *  Created on: Jul 8, 2014
 *      Author: liang
 */

#include <string>
#include <vector>
#include "engine.h"

using std::string;
using std::vector;
using std::to_string;

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
		printf("Get row or column failed. (in file isat3_ddes_iSAT3.cpp)");
	}
}

int setDecl(Engine* ep, vector<string> &varsStr, vector<double> &bl,
		vector<double> &bu) {
	setSize(ep);

	varsStr.clear(), bl.clear(), bu.clear();
	double delta = getDouble(ep, "delta");
	int size = row * (column + 1) + 1;

	if (row == 1) {
		for (int i = 0; i < column; i++) {
			varsStr.push_back("cb" + to_string(i + 1));
			bl.push_back(BL), bu.push_back(BU);
		}
		varsStr.push_back("xi1");
		bl.push_back(0), bu.push_back(delta);
	} else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column - 1; j++) {
				varsStr.push_back(
						"cb" + to_string(i + 1) + "_" + to_string(j + 1));
				bl.push_back(BL), bu.push_back(BU);
			}
			varsStr.push_back("xi" + to_string(i + 1));
			bl.push_back(0), bu.push_back(delta);
		}
	}

	varsStr.push_back("t");
	bl.push_back(0), bu.push_back(delta);

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


//char *getStrFromStrArray(char **strArray) {
//	int size = 0;
//	for (int i = 0; strArray[i]; i++) {
//		size += strlen(strArray[i]);
//	}
//	char *initStr = (char *) malloc(sizeof(char) * size + 1);
//	initStr[0] = '\0';
//	for (int i = 0; strArray[i]; i++) {
//		sprintf(initStr, "%s%s", initStr, strArray[i]);
//	}
//	printf("\n");
////	freeTable(strArray);
//
//	return initStr;
//}
//
//
//int getLength(char **strArray) {
//	int len = 0;
//	while (*strArray) {
//		len += strlen(*strArray);
//		strArray++;
//	}
//	return len;
//}
//
//void printStrArray(char **strArray) {
//	while (*strArray) {
//		printf("%s", *strArray);
//		strArray++;
//	}
//	printf("\n");
//}

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

