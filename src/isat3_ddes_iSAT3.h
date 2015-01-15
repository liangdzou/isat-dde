/*
 * isat3_ddes_getRelation.h
 *
 *  Created on: Jul 8, 2014
 *      Author: liang
 */

#ifndef ISAT3_DDES_GETRELATION_H_
#define ISAT3_DDES_GETRELATION_H_

#include <string>
using std::string;

extern int size;

extern int setDecl(Engine* ep, string vars[], double bl[], double bu[]);
extern string getInit(Engine *ep);
extern string getTrans(Engine *ep);
extern string getDangerTarget(Engine *ep);
extern void iSAT3StrTest(Engine *ep);

#endif /* ISAT3_DDES_GETRELATION_H_ */
