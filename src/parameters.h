/*
 * parameters.h
 *
 *  Created on: Jul 7, 2014
 *      Author: liang
 */

#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

#ifndef PARAMETERS_H_
#define PARAMETERS_H_

class para {
	friend int main(int argc, char **argv);
	static string file;

	static double a_w;
	static double co_w;
	static double e;
	static double md;

	static long expr_t_max;
	static long bmc_t_max;

	static double c_min;
	static double c_max;
	static double c_delta;

	static long bound;
	static bool stable;

	static string ly;
public:
	static string get_file() {
		return file;
	}
	static double get_a_w() {
		return a_w;
	}
	static double get_co_w() {
		return co_w;
	}
	static double get_e() {
		return e;
	}
	static double get_md() {
		return md;
	}
	static double get_expr_t_max() {
		return expr_t_max;
	}
	static double get_bmc_t_max() {
		return bmc_t_max;
	}
	static double get_c_min() {
		return c_min;
	}
	static double get_c_max() {
		return c_max;
	}
	static double get_c_delta() {
		return c_delta;
	}
	static long get_bound() {
		return bound;
	}
	static void print() {
		cout << "file:\t" << file << endl;
		cout << "a_w:\t" << a_w << endl;
		cout << "co_w:\t" << co_w << endl;
		cout << "e:\t" << e << endl;
		cout << "md:\t" << md << endl;
		cout << "expr_t_max:\t" << expr_t_max << endl;
		cout << "bmc_t_max:\t" << bmc_t_max << endl;
		cout << "c_min:\t" << c_min << endl;
		cout << "c_max:\t" << c_max << endl;
		cout << "c_delta:\t" << c_delta << endl;
		cout << "bound:\t" << bound << endl;
		cout << "stable:\t" << stable << endl;
		cout << "LY:\t" << ly << endl;
	}
};

#endif /* PARAMETERS_H_ */
