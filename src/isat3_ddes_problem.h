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

//	double vars_bl[], vars_bu[];
	unsigned row, column;
	isat3_node* vars[];
	std::string init, trans, target;

	void vars_def();
	void vars_init();
	void trans_def();

public:
	isat3* is3 = isat3_init(NULL);
	Engine *ep;

	isat3_ddes_problem();
	~isat3_ddes_problem() {
		for (size_t i = 0; i < row * (column + 1) + 1; i++) {
			isat3_node_destroy(is3, vars[i]);
		}
		isat3_deinit(is3);
		isat3_cleanup();
		engClose(ep);
	}
	void print();
};

#endif /* ISAT3_DDES_GETRELATION_H_ */
