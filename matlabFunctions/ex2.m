 clear;

% inputs (4-tuple)
DDES = @(x) [-x(1); -x(2)];
LINEAR = 1;
INIT = [8.; 8.];
DELTA = 1;

% parameters (3-tuple)
DEG = 2;
AL = -1000;
AU = 1000;

% target (variables are x1, ..., xn)
TARGET = [sym('x1>1'); sym('x1<-1')];

