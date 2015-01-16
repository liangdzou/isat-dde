function [tmin,xfeas,lmis,S] = ly_linear_Stability(coefMatrices)

matrixNums = size(coefMatrices,3);
% specifying LMIs
setlmis([]);
% S = sym('S',[1, matrixNums]);
% G = sym('G',[1, matrixNums]);
sgSize = size(coefMatrices(:,:,1),1);
for i = 1 : matrixNums
    S(i)=lmivar(1,[sgSize 1]);
    G(i)=lmivar(2,[sgSize sgSize]);
end
% Prop = sym('Prop',[1, matrixNums]);
for i = 1 : matrixNums
    for j = 1 : matrixNums
        Prop((i-1)*matrixNums+j) = newlmi;
        lmiterm([-Prop((i-1)*matrixNums+j) 1 1 G(i)],1,1,'s');
        lmiterm([-Prop((i-1)*matrixNums+j) 1 1 S(i)],-1,1);
        lmiterm([-Prop((i-1)*matrixNums+j) 1 2 G(i)'],1,double(coefMatrices(:,:,i))');
        lmiterm([-Prop((i-1)*matrixNums+j) 2 2 S(j)],1,1);
    end
end
lmis=getlmis;

% solving LMIs
[tmin,xfeas] = feasp(lmis);

end