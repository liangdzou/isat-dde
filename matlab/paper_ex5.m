 clear;

% inputs (4-tuple)
DDES = @(x) [x(2)-1.622; x(2)*x(2)/2500];
LINEAR = 0;
INIT = [sym('-2');sym('1.622')];
DELTA = 0.128;

DEG = 1;

% target (variables are x1, ..., xn)
TARGET = [sym('x1<-2.05'); sym('x1>-1.95')];

