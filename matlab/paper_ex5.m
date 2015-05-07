 clear;

% inputs (4-tuple)
DDES = @(x) [x(2); (x(2)+1.622)*(x(2)+1.622)/2500];
LINEAR = 0;
INIT = [sym('0');sym('0')];
DELTA = 0.128;

DEG = 1;

% target (variables are x1, ..., xn)
TARGET = [sym('x1<-0.05'); sym('x1>0.05')];

