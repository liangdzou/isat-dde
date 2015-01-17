function [ly,dm] = ly_linear(tmin,xfeas,lmis,S,a0,xi,A,Xs)

% terminate if it is not stable
if (tmin >= 0);
    ly = -1;
    dm = -1;
    return; 
end

As_num = size(Xs,1);
% solution of S^(-1), store in PSolutions
% PSolutions = sym('PS',[size(dec2mat(lmis,xfeas,S(1)),1),size(dec2mat(lmis,xfeas,S(1)),2),matrixNums]);
for i = 1 : As_num
    PSolutions(:,:,i) = inv(dec2mat(lmis,xfeas,S(i)));
end

% output Lyapunov function 'V'
P = getMatAverage(PSolutions,Xs);
a0_vec= transpose(a0);
a0_vec = a0_vec(:);
ly = transpose(a0_vec)*P*a0_vec;

% get minimum decrease function 'minDecrease'
% x is a combine of variables xi, xi1 and coefVector
% the deminsion of xi, xi1 and coefVector are size(coefBefore,1), size(coefBefore,1), and size(P,1)
xiInFun = @(x) getSubVector(x,1,size(a0,1));
xi1InFun = @(x) getSubVector(x,size(a0,1)+1,2*size(a0,1));
coefInFun = @(x) getSubVector(x,2*size(a0,1)+1,2*size(a0,1)+size(P,1));
P0 = @(x) subs(P,xi,xiInFun(x));
P1 = @(x) getMatAverage(PSolutions,xi1InFun(x));
A0 = @(x) subs(A,xi,xiInFun(x));
minDecrease = @(x) double(transpose(coefInFun(x))*(P0(x)-transpose(A0(x))*P1(x)*A0(x))*coefInFun(x));

% find the minimum value for 'minDecrease'
b = ones(2*size(a0,1),1);
A = diag(b);
A = [A;-A];
A = [A zeros(4*size(a0,1),size(P,1))];
b = [b;zeros(2*size(a0,1),1)];
x0 = ones(2*size(a0,1)+size(P,1),1);
[xx,dm] = fmincon(minDecrease,x0,A,b);

end
