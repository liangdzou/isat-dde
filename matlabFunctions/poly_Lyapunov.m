function [V,dm,exitflag] = poly_Lyapunov(coefBefore, coefAfter, xi, varNums, deg, coefBL, coefBU, delta, upsilon)

coefBLVect = ones(1, varNums*(deg+1)) * coefBL;
coefBUVect = ones(1, varNums*(deg+1)) * coefBU;
xiBLVect = zeros(1,varNums);
xiBUVect = ones(1,varNums) * delta;
BLVect = [coefBLVect, xiBLVect];
BUVect = [coefBUVect, xiBUVect];
varInter = interval(BLVect, BUVect);
coefBFMat = transpose(varInter) * varInter;

xi1 = sym('xia', varNums);
coefParameters = [transpose(coefBefore); xi; xi1];
coefParameters= coefParameters(:);
coefAFVector = [transpose(coefAfter); xi1];
coefAFVector = coefAFVector(:);
coefAF = eval(['@(', vectElementsString(coefParameters), ') [', vectElementsString(coefAFVector), ']']);

varAFParameters = [varInter, interval(xiBLVect, xiBUVect)];
coefAFStr = 'coefAF(varAFParameters(1)';
for i = 2 : varNums*(deg + 3)
    coefAFStr = strcat(coefAFStr, ', varAFParameters(', num2str(i), ')');
end
coefAFStr = strcat(coefAFStr, ')');
coefAFInter = eval(coefAFStr);
coefAFMat = transpose(coefAFInter)*coefAFInter;

coefMat = coefBFMat - coefAFMat;

set(0,'RecursionLimit',10000);
[dm, exitflag] = poly_lp(coefMat, upsilon, coefBU);
V = 'not implemented';

end



