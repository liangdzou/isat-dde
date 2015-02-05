clear;

% inputs (4-tuple)
DDES = @(x) [-x(1) + 0.5*x(2)+0.00005; 0.5*x(1)-x(2) + 0.25*x(3)-0.00005; 0.25*x(2)-x(3)-0.000025];
LINEAR = 0;
INIT = [-11.3636; -32.7272; -8.1818];
DELTA = 0.01;

% parameters (3-tuple)
DEG = 1;

% target (variables are x1, ..., xn)
TARGET = [sym('x2>2.2727')];

