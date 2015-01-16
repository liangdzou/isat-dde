/*
 * matEngine.h
 *
 *  Created on: Jul 8, 2014
 *      Author: liang
 */

#include<string>

using std::string;

#ifndef MATENGINE_H_
#define MATENGINE_H_

#include "engine.h"

extern int getInt(Engine *ep, string var);
extern double getDouble(Engine *ep, string var);
extern string getString(Engine *ep, string var);

extern void mat_engine_test();

#endif /* MATENGINE_H_ */
