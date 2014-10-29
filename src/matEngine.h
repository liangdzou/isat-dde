/*
 * matEngine.h
 *
 *  Created on: Jul 8, 2014
 *      Author: liang
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "engine.h"

#define  BUFSIZE 256

#ifndef MATENGINE_H_
#define MATENGINE_H_

int getInt(Engine *ep, char* varName);
double getDouble(Engine *ep, char* varName);
char *getString(Engine *ep, char* varName);
char *toZeroDot(char *str, int nums);

#endif /* MATENGINE_H_ */
