#include "parameters.h"
#include <string>
using std::string;

string para::file("");

double para::a_w = 1000.0;
double para::co_w = 1000;
double para::e = 0.01;
double para::md = 0.01;

long para::expr_t_max = 6000000000;
long para::bmc_t_max = 6000000000;

double para::c_min = -1000;
double para::c_max = 1000;
double para::c_delta = 0.1;

long para::bound = 100;
bool para::stable = true;
