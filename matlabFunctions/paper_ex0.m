 clear;

% inputs (4-tuple)
DDES = @(x) -x;
LINEAR = 1;
INIT = 1;
DELTA = 1;

% parameters
DEG = 2;

% template
a0 = sym('cb',[1, DEG+1]);
xi = sym('xi',[1,1]);
vars = [a0(:);xi];
TEMP = vars * transpose(vars);
TEMP = transpose(TEMP(:));

% target (variables are x1, ..., xn)
TARGET = [sym('x1>1'); sym('x1<-1')];

