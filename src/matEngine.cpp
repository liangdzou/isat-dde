#include <iostream>
#include <cmath>
#include <sstream>

using std::cout;
using std::endl;

#include "matEngine.h"

int getInt(Engine *ep, string var) {
	mxArray *mval = engGetVariable(ep, var.c_str());
	if (mval == NULL) {
		cout << var << "is NULL. (in matEngine.cpp)";
		mxDestroyArray(mval);
		return 0;
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

string toZeroDot(string str);

string getString(Engine *ep, string var) {
	mxArray *mval = engGetVariable(ep, var.c_str());
	if (mval == NULL) {
		cout << var << "is NULL. (in matEngine.cpp)";
		mxDestroyArray(mval);
		return NULL;
	}
	size_t size = mxGetM(mval) * mxGetN(mval) + 1;
	char *str = new char[size];
	mxGetString(mval, str, size);
	string val = toZeroDot(str);
	mxDestroyArray(mval);
	delete[] (str);
	return val;
}

string toZeroDot(string str) {
	std::ostringstream ret;
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == '.' && (i == 0 || !isdigit(str[i - 1]))) {
			ret << "0.";
		} else {
			ret << str[i];
		}
	}
//	bool flag = true;
//	for (size_t i = 0; i < str.size(); i++) {
//		if (flag && str[i] == '.') {
//			ret << "0.";
//		} else {
//			ret << str[i];
//		}
//		if ('0' <= str[i + 1] && str[i + 1] <= '9') {
//			flag = false;
//		} else {
//			flag = true;
//		}
//	}
	return ret.str();
}

// UNIT test
void mat_engine_test() {
	Engine* ep;
	if (!(ep = engOpen("\0")))
		cout << "Can't start MATLAB engine" << endl;
	engEvalString(ep, "addpath('./matlabFunctions');");
	engEvalString(ep, "mat_test");
	cout << getInt(ep, "ival") << endl;
	cout << getDouble(ep, "dval") << endl;
	cout << getString(ep, "sval") << endl;
	engClose(ep);
}

