clear;
format long;
options = optimoptions('intlinprog','TolCon',1e-9);

% inputs (4-tuple)
DDES = @(x) [2*x(1)+x(2)-5*x(3); 2*x(1)-12*x(2)-0.0002; 4*x(1)+2*x(2)-10*x(3)];
LINEAR = 0;
INIT = [0.3617;-0.1064;0.7234];
DELTA = 0.01;

% parameters (3-tuple)
DEG = 2;

% template
a0 = sym('cb',[3, DEG+1]);
xi = sym('xi',[3,1]);
vars = [a0(:);xi];
TEMP = vars * transpose(vars);
TEMP = transpose(TEMP(:));

% target (variables are x1, ..., xn)
TARGET = [sym('x3<=-0.2766')];

