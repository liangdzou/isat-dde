#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "engine.h"

#include "isat3_ddes.h"
#include "isat3_ddes_maxC.h"
#include "isat3/isat3.h"
#include "isat3_ddes_iSAT3.h"

bool isLinear(Engine *ep) {
	mxArray *result = engGetVariable(ep, "isLinear");
	if (result == NULL) {
		printf("Variable isLinear is not specified.\n"
				"  (It is polynomial by default.)");
		mxDestroyArray(result);
		return false;
	} else {
		bool *ret = (bool*) mxGetPr(result);
		mxDestroyArray(result);
		return *ret;
	}
}

int main(int argc, char **argv) {
	Engine *ep;
	isat3_setup();

	if (!(ep = engOpen("\0"))) {
		printf("Can't start MATLAB engine\n" "\nCan't start MATLAB engine\n");
		return EXIT_FAILURE;
	}

	engEvalString(ep, "addpath('./matlabFunctions');");
	engEvalString(ep, "impl();");

	// get maximum c
	double c_max = 1;
	if (isLinear(ep)) {
		c_max = linear_maxC(ep);
	} else {
		c_max = poly_maxC(ep);
	}
	printf("c_max = %f", c_max);

	char **varNames = NULL;
	double *bl = NULL, *bu = NULL;
	int varNums = setDecl(ep, &varNames, &bl, &bu);
	char *initStr, *transStr, *dangerTarget;
	initStr = getInit(ep);
	transStr = getTrans(ep);
	dangerTarget = getDangerTarget(ep);
	char *V = getString(ep, "charV");
	char *target = malloc(
			sizeof(char) * (strlen(dangerTarget) + strlen(V) + 128));
	sprintf(target, "%s<%f or (%s);", V, c_max, dangerTarget);

//	printf("%s\n\n%s\n\n%s", initStr, transStr, dangerTarget);

	bool result = iSAT3_bmc(varNames, bl, bu, varNums, initStr, transStr,
			target);
	if (!result)
		printf("The time span is not enough to give a precise result!");
	else {
		sprintf(target, "%s<%f and !(%s);", V, c_max, dangerTarget);
		result = iSAT3_bmc(varNames, bl, bu, varNums, initStr, transStr,
				target);
		printf(result? "It is safe.":"It is not safe.");
	}

//	bool result = iSAT3_bmc(varNames, bl, bu, varNums, initStr, transStr,
//			safePropStr);
//	printf("%d", result);

	free(target);
	engClose(ep);
	isat3_cleanup();
	return EXIT_SUCCESS;
}
