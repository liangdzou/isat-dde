#include "matEngine.h"

int getInt(Engine *ep, char* varName) {
	mxArray *var = engGetVariable(ep, varName);
	if (var == NULL) {
		printf("%s is NULL.", varName);
		mxDestroyArray(var);
		return -1;
	}
	int ret = (int) *mxGetPr(var);
	mxDestroyArray(var);
	return ret;
}

double getDouble(Engine *ep, char* varName) {
	mxArray *var = engGetVariable(ep, varName);
	if (var == NULL) {
		printf("%s is NULL.", varName);
		mxDestroyArray(var);
		return -1;
	}
	double ret = *mxGetPr(var);
	mxDestroyArray(var);
	return ret;
}

char *getString(Engine *ep, char* varName) {
	mxArray *var = engGetVariable(ep, varName);
	if (var == NULL) {
		printf("%s is NULL.", varName);
		mxDestroyArray(var);
		return NULL;
	}
	int varLength = mxGetM(var) * mxGetN(var) + 1;
	char *ret = malloc(sizeof(char) * varLength);
	mxGetString(var, ret, varLength);
	mxDestroyArray(var);
	return toZeroDot(ret,strlen(ret));
}

char *toZeroDot(char *str, int nums) {
	char *newStr = malloc(sizeof(char) * (nums + 512));
	*newStr = '\0';
	bool needCheck = true;
	for (int i = 0; i < strlen(str); i++) {
		if (needCheck && str[i] == '.') {
			strcat(newStr, "0.");
		} else {
			sprintf(newStr, "%s%c", newStr, str[i]);
		}
		if ('0' <= str[i + 1] && str[i + 1] <= '9') {
			needCheck = false;
		} else {
			needCheck = true;
		}
	}
	free(str);
	return newStr;
}

