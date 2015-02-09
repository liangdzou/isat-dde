function dm = ly_dm(a0, A, xi, P, PSolutions, cmax)

% % get minimum decrease function 'minDecrease'
% % x is a combine of variables xi, xi1 and coefVector
% % the deminsion of xi, xi1 and coefVector are size(coefBefore,1), size(coefBefore,1), and size(P,1)
lmd = sym('lambda');
xiInFun = @(x) getSubVector(x,1,size(a0,1));
xi1InFun = @(x) getSubVector(x,size(a0,1)+1,2*size(a0,1));
a0InFun = @(x) getSubVector(x,2*size(a0,1)+1,2*size(a0,1)+size(P,1));
lambdaInFun = @(x) getSubVector(x,2*size(a0,1)+size(P,1)+1,2*size(a0,1)+size(P,1) + 1);
P0 = @(x) subs(P,xi,xiInFun(x));
P1 = @(x) getMatAverage(PSolutions,xi1InFun(x));
A0 = @(x) subs(A,xi,xiInFun(x));
lambda = @(x) subs(lmd,lmd,lambdaInFun(x));
minDecrease = @(x) double(lambda(x)*cmax+...
    (1-lambda(x))*transpose(a0InFun(x))*P0(x)*a0InFun(x)-...
    transpose(a0InFun(x))*(transpose(A0(x))*P1(x)*A0(x))*a0InFun(x));

% find the minimum value for 'minDecrease'
b = ones(2*size(a0,1),1);
A = diag(b);
A = [A;-A];
A = [A, zeros(4*size(a0,1),size(P,1)+1)];
A = [A;zeros(1,size(A,2)-1),-1];
b = [b;zeros(2*size(a0,1)+1,1)];
x0 = ones(2*size(a0,1)+size(P,1)+1,1);
[xx,dm] = fmincon(minDecrease,x0,A,b);

end