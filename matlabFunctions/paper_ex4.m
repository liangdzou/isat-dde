 clear;

% inputs (4-tuple)
DDES = @(x) -x*x*x;
LINEAR = 0;
INIT = 200;
DELTA = 0.001;

% parameters
DEG = 1;

% target (variables are x1, ..., xn)
TARGET = [sym('x1>20'); sym('x1<-20')];

