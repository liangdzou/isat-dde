 clear;

% inputs (4-tuple)
DDES = @(x) -x;
LINEAR = 1;
INIT = sym('1');
DELTA = 1;

DEG = 2;

% target (variables are x1, ..., xn)
TARGET = [sym('x1>1'); sym('x1<-1')];

