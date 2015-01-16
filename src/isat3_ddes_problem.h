/*
 * isat3_ddes_getRelation.h
 *
 *  Created on: Jul 8, 2014
 *      Author: liang
 */

#include "isat3/isat3.h"
#include "matEngine.h"

#include <string>
#include <iostream>

#ifndef ISAT3_DDES_GETRELATION_H_
#define ISAT3_DDES_GETRELATION_H_

class isat3_ddes_problem {

	unsigned row, column;
	isat3_node** vars_begin;
	isat3_node** vars_end;
	std::string init, trans, target;

	void vars_def();
	void vars_init();
	void trans_def();

public:
	isat3* is3;
	Engine* ep;

	isat3_ddes_problem(string script);
	~isat3_ddes_problem() {
		for (auto var = vars_begin; var != vars_end; ++var) {
			isat3_node_destroy(is3, *var);
		}
		isat3_deinit(is3);
		isat3_cleanup();
		engClose(ep);
	}

	isat3_node** get_vars_begin() {
		return vars_begin;
	}

	isat3_node** get_vars_end() {
		return vars_end;
	}

	void print();
};

#endif /* ISAT3_DDES_GETRELATION_H_ */
