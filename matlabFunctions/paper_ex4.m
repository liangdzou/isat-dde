 clear;

% inputs (4-tuple)
DDES = @(x) -x*x*x;
LINEAR = 0;
INIT = sym('3');
ILEN = sym('3');
DELTA = 1;

DEG = 5;

% target (variables are x1, ..., xn)
TARGET = [sym('x1>3000'); sym('x1<-3000')];

