#include<iostream>
#include<cmath>

using std::cout;

#include "matEngine.h"

int getInt(Engine *ep, string var) {
	mxArray *mval = engGetVariable(ep, var.c_str());
	if (mval == NULL) {
		cout << var << "is NULL. (in matEngine.cpp)";
		mxDestroyArray(mval);
		return NAN;
	}
	int val = (int) *mxGetPr(mval);
	mxDestroyArray(mval);
	return val;
}

double getDouble(Engine *ep, string var) {
	mxArray *mval = engGetVariable(ep, var.c_str());
	if (mval == NULL) {
		cout << var << "is NULL. (in matEngine.cpp)";
		mxDestroyArray(mval);
		return NAN;
	}
	double val = *mxGetPr(mval);
	mxDestroyArray(mval);
	return val;
}

string getString(Engine *ep, string var) {
	mxArray *mval = engGetVariable(ep, var.c_str());
	if (mval == NULL) {
		cout << var << "is NULL. (in matEngine.cpp)";
		mxDestroyArray(mval);
		return NULL;
	}
	int varLength = mxGetM(mval) * mxGetN(mval);
	char *str = static_cast<char *>(malloc(sizeof(char) * (varLength + 1)));
	mxGetString(mval, str, varLength + 1);
	string val = toZeroDot(str);
	mxDestroyArray(mval);
	free(str);
	return val;
}

string toZeroDot(string str) {
	string newStr = "";
	bool needCheck = true;
	for (size_t i = 0; i < str.size(); i++) {
		if (needCheck && str[i] == '.') {
			newStr += "0.";
		} else {
			newStr += newStr + str[i];
		}
		if ('0' <= str[i + 1] && str[i + 1] <= '9') {
			needCheck = false;
		} else {
			needCheck = true;
		}
	}
	return newStr;
}

