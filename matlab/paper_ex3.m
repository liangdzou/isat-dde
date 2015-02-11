clear;

% inputs (4-tuple)
DDES = @(x) [-3*x(1)+6*x(2)+5*x(3); 2*x(1)-12*x(2); x(1)+6*x(2)-5*x(3)];
LINEAR = 1;
INIT = [sym('10');sym('0');sym('0')];
DELTA = 0.01;

DEG = 1;

% target (variables are x1, ..., xn)
TARGET = sym('x1 -x2 - x3 < 5');

