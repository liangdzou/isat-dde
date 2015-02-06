function [ly,ly_str,dm] = ly_linear(a0, a1, xi, DELTA)

% % calculate A
row= size(a0,1);
column = size(a0,2);
A = sym('A',[row*column, row*column]);
for i = 1 : row
    for j = 1 : column
        for k = 1 : row
            for l = 1 : column
                rowA = (i-1)*column + j;
                columnA = (k-1)*column + l;
                A(rowA,columnA) = subs(a1(i,j),a0(k,l),1) - subs(a1(i,j),a0(k,l),0);
            end
        end
    end
end

% % calculate As
vars_num = size(xi,1);
Xs = sym('X',[2^vars_num,1]);
for i = 1 : 2^vars_num
    num = uint32(i-1);
    As(:,:,i) = A;
    Xs(i,1) = 1;
    for j = 1 : vars_num
        As(:,:,i) = subs(As(:,:,i),xi(j,1),rem(num,2)*DELTA);
        Xs(i,1) = Xs(i,1) * ((1-xi(j,1)/DELTA) + rem(num,2)*(2*xi(j,1)/DELTA-1));
        num = (num-1)/2;
    end
end

% % stability
As_num = size(As,3);

setlmis([]);

A_size = size(As(:,:,1),1);
for i = 1 : As_num
    S(i)=lmivar(1,[A_size 1]);
    G(i)=lmivar(2,[A_size A_size]);
end

Im = diag(ones(A_size,1));
for i = 1 : As_num
    for j = 1 : As_num
        Prop((i-1)*As_num+j) = newlmi;
        lmiterm([-((i-1)*As_num+j) 1 1 G(i)],Im,Im,'s');
        lmiterm([-((i-1)*As_num+j) 1 1 S(i)],-1,1);
        lmiterm([-((i-1)*As_num+j) 1 2 G(i)'],1,double(As(:,:,i))');
        lmiterm([-((i-1)*As_num+j) 2 2 S(j)],1,1);
    end
end

lmis=getlmis;
[tmin,xfeas] = feasp(lmis);

if (tmin >= 0);
    ly=0;
    ly_str = '';
    dm = -1;
    return; 
end

% % calculate ly_str
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
ly_str = char(ly);

% get minimum decrease function 'minDecrease'
% x is a combine of variables xi, xi1 and coefVector
% the deminsion of xi, xi1 and coefVector are size(coefBefore,1), size(coefBefore,1), and size(P,1)
xiInFun = @(x) getSubVector(x,1,size(a0,1));
xi1InFun = @(x) getSubVector(x,size(a0,1)+1,2*size(a0,1));
a0InFun = @(x) getSubVector(x,2*size(a0,1)+1,2*size(a0,1)+size(P,1));
lambdaInFun = @(x) getSubVector(x,2*size(a0,1)+size(P,1),2*size(a0,1)+size(P,1) + 1);
P0 = @(x) subs(P,xi,xiInFun(x));
P1 = @(x) getMatAverage(PSolutions,xi1InFun(x));
A0 = @(x) subs(A,xi,xiInFun(x));
minDecrease = @(x) double(transpose(a0InFun(x))*(P0(x)-transpose(A0(x))*P1(x)*A0(x))*a0InFun(x));

% find the minimum value for 'minDecrease'
b = ones(2*size(a0,1),1);
A = diag(b);
A = [A;-A];
A = [A zeros(4*size(a0,1),size(P,1))];
b = [b;zeros(2*size(a0,1),1)];
x0 = ones(2*size(a0,1)+size(P,1),1);
[xx,dm] = fmincon(minDecrease,x0,A,b);
dm =0.1;

end
