 clear;

% inputs (4-tuple)
DDES = @(x) -1/10*x*x*x;
LINEAR = 0;
INIT = 1;
DELTA = 1;

% parameters
DEG = 1;

% target (variables are x1, ..., xn)
TARGET = [sym('x1>1'); sym('x1<-1')];

