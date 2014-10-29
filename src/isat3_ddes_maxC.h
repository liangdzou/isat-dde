/*
 * isat3_ddes_min_c.h
 *
 *  Created on: Jul 7, 2014
 *      Author: liang
 */

#ifndef ISAT3_DDES_MIN_C_H_
#define ISAT3_DDES_MIN_C_H_

#define  BUFSIZE 256

double linear_maxC(Engine *ep);
double poly_maxC(Engine *ep);

extern double getDouble(Engine *ep, char* varName);
extern char *getString(Engine *ep, char* varName);

extern void expr_test();

#endif /* ISAT3_DDES_LINEAR_H_ */
