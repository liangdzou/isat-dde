function [V,dm,exitflag] = poly_Lyapunov(coefBefore, coefAfter, xi, varNums, deg, coefBL, coefBU, delta, upsilon)

%calculate an0, an1, xi0, xi1, ep, Ico


% calculate coefBFMat
coefBLVect = ones(1, varNums*(deg+1)) * coefBL;
coefBUVect = ones(1, varNums*(deg+1)) * coefBU;
xiBLVect = zeros(1,varNums);
xiBUVect = ones(1,varNums) * delta;
BLVect = [coefBLVect, xiBLVect];
BUVect = [coefBUVect, xiBUVect];
varInter = interval(BLVect, BUVect);
coefBFMat = transpose(varInter) * varInter;

% calculate coefAFMat
xi1 = sym('xia', varNums);
coefParameters = [transpose(coefBefore); xi; xi1];
coefParameters= coefParameters(:);
coefAFVector = [transpose(coefAfter); xi1];
coefAFVector = coefAFVector(:);
coefAF = eval(['@(', strrep(strrep(vectElementsString(coefParameters),'[',''),']',''), ') [', vectElementsString(coefAFVector), ']']);
varAFParameters = [varInter, interval(xiBLVect, xiBUVect)];
coefAFStr = 'coefAF(varAFParameters(1)';
for i = 2 : varNums*(deg + 3)
    coefAFStr = strcat(coefAFStr, ', varAFParameters(', num2str(i), ')');
end
coefAFStr = strcat(coefAFStr, ')');
coefAFInter = eval(coefAFStr);
coefAFMat = transpose(coefAFInter)*coefAFInter;

% calculate coefMat, and call poly_lp
coefMat = coefBFMat - coefAFMat;

% calculate bigc


set(0,'RecursionLimit',10000);

coefMatBL = coefMat.inf;
coefMatBU = coefMat.sup;
coefVectBL = transpose(coefMatBL(:));
coefVectBU = transpose(coefMatBU(:));

% linear programming
f = [zeros(2*size(coefVectBL,2), 1); -1];
A = [-coefVectBL, coefVectBU, 1];
b = 0;
lb = zeros(2*size(coefVectBL,2) + 1, 1);
ub = coefBU * ones(2*size(coefVectBL,2) + 1, 1);
[x,fval,exitflag] = linprog(f,A,b,[],[],lb,ub);

times = 0;
while (fval >= 0 || max(A*x) > 0 || exitflag <= 0)
    [maxRow,maxIndeices] = max(coefVectBU - coefVectBL);
    [val,j] = max(maxRow);
    i = maxIndeices(j);
    
    times = times + 1;
    if mod(times, 10) == 0
        times = times;
    end
    
    if val > upsilon
        rowSize = size(coefVectBL,1);
        coefVectBL = [coefVectBL; coefVectBL(i,:)];
        coefVectBU = [coefVectBU; coefVectBU(i,:)];
        valMid = (coefVectBL(i,j) + coefVectBU(i,j))/2;
        coefVectBU(i,j) = valMid;
        coefVectBL(rowSize + 1,j) = valMid;
        A = [- coefVectBL, coefVectBU, ones(rowSize + 1,1)];
        b = zeros(rowSize + 1,1);
        [x,fval,exitflag] = linprog(f,A,b,[],[],lb,ub);
    else
        break;
    end
end

dm = -fval;
V = 'not implemented';

end



