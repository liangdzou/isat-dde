/*
 * isat3_ddes_getRelation.h
 *
 *  Created on: Jul 8, 2014
 *      Author: liang
 */

#ifndef ISAT3_DDES_GETRELATION_H_
#define ISAT3_DDES_GETRELATION_H_

//char **getRelation(Engine *ep);
//void printToiSAT(char **);
void iSAT3StrTest(Engine *ep);

char *getStrFromStrArray(char **strArray);
void freeTable(char **strArray);

int setDecl(Engine *ep, char ***varNamesPointer, double **blPointer,
		double **buPointer);
char *getInit(Engine *ep);
char *getTrans(Engine *ep);
char *getDangerTarget(Engine *ep);

#endif /* ISAT3_DDES_GETRELATION_H_ */
