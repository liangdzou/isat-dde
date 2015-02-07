 clear;

% inputs (4-tuple)
DDES = @(x) -x*x*x;
LINEAR = 0;
INIT = 10;
DELTA = 1;

% parameters
DEG = 1;

% target (variables are x1, ..., xn)
TARGET = [sym('x1>20'); sym('x1<-20')];

