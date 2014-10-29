/*
 * isat3_ddes.h
 *
 *  Created on: Jul 7, 2014
 *      Author: liang
 */


#ifndef ISAT3_DDES_H_
#define ISAT3_DDES_H_

//extern char **getRelation(Engine *ep);
extern void printStrArray(char **);
extern void iSAT3StrTest(Engine *ep);
extern double linear_maxC(Engine *ep);
extern double poly_maxC(Engine *ep);
extern bool iSAT3_bmc(char **varNames, double *bl, double *bu, int varNums,
		char *initStr, char *transStr, char *targetStr);

#endif /* ISAT3_DDES_H_ */
