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

#ifndef ISAT3_DDES_PROBLEM_H_
#define ISAT3_DDES_PROBLEM_H_

static string path;

class isat3_ddes_problem {

	isat3_node **vars_begin, **vars_end;
	std::string declare, init, trans, target;

	void vars_def(int row, int column);
	void vars_init(int row, int column);
	void trans_def(int row, int column);

public:
	isat3* is3;
	Engine* ep;

	isat3_ddes_problem(string script);
	isat3_ddes_problem() = delete;
	isat3_ddes_problem(const isat3_ddes_problem&) = delete;
	isat3_ddes_problem& operator=(const isat3_ddes_problem&) = delete;
	~isat3_ddes_problem() {
		for (auto var_p = vars_begin; var_p != vars_end; ++var_p)
			isat3_node_destroy(is3, *var_p);
		delete[] vars_begin;
		isat3_deinit(is3);
		isat3_cleanup();
		engClose(ep);
	}

	void reset_vars();
	isat3_node** get_vars_begin() {
		return vars_begin;
	}

	isat3_node** get_vars_end() {
		return vars_end;
	}
	string get_decl() {
		return declare;
	}
	string get_init() {
		return init;
	}
	string get_trans() {
		return trans;
	}
	string get_target() {
		return target;
	}

	void print();
};

#endif /* ISAT3_DDES_GETRELATION_H_ */
