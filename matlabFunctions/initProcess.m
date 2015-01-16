 clear;

% Inputs the DDEs:
% initial conditions (ics)
% DDEs (ddes)
% delay (delta)

% inputs 1
% init = [8., 8.];
% ddes = @(x) [-x(1); -x(2)];
% linear = true;
% delta = 1;

% inputs 2
init = 1;
ddes = @(x) -x;
linear = true;
delta = 1;

% maximum degree (deg)
% coefficiens bound (coBound)
deg = 2;
coefBoundL = -1000;
coefBoundU = 1000;

% Danger Target (Target)
DangerTarget = [sym('x1>1'); sym('x1<-1')];
