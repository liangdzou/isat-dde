 clear;

% inputs (4-tuple)
DDES = @(x) -x*x*x;
LINEAR = 0;
INIT = 200;
DELTA = 0.001;

% parameters
DEG = 21;

% target (variables are x1, ..., xn)
TARGET = [sym('x1>400'); sym('x1<-400')];

