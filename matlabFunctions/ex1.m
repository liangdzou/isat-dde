 clear;

% inputs (4-tuple)
DDES = @(x) -x;
LINEAR = 1;
INIT = 1;
DELTA = 1;

% parameters (3-tuple)
DEG = 2;
AL = -1000;
AU = 1000;

% target (variables are x1, ..., xn)
TARGET = [sym('x1>1'); sym('x1<-1')];

