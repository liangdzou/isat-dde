clear;

% inputs (4-tuple)
DDES = @(x) [-x(1) + 1/2*x(2); 1/2*x(1)-x(2) + 1/4*x(3); 1/4*x(2)-x(3)];
LINEAR = 1;
INIT = [sym('-125/11'); sym('-360/11'); sym('-90/11')];
DELTA = 0.01;

DEG = 1;

% target (variables are x1, ..., xn)
TARGET = sym('x2>2.2727');

