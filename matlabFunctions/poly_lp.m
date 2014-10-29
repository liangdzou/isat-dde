function [dm,exitflag] = poly_lp(coefMat, upsilon, B)

coefMatBL = coefMat.inf;
coefMatBU = coefMat.sup;
coefVectBL = transpose(coefMatBL(:));
coefVectBU = transpose(coefMatBU(:));

f = [zeros(2*size(coefVectBL,2), 1); -1];
A = [-coefVectBL, coefVectBU, 1];
b = 0;
lb = zeros(2*size(coefVectBL,2) + 1, 1);
ub = B * ones(2*size(coefVectBL,2) + 1, 1);
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


% exitflag = -1;
% elements = 1;
% dm = -1;
% while (size(coefVectBL,1) ~= 0 && exitflag <= 0)
%     f = [zeros(2*size(coefVectBL(1,:),2), 1); -1];
%     A = [- coefVectBL(1,:), coefVectBU(1,:), 1];
%     b = 0;
%     lb = zeros(2*size(coefVectBL(1,:),2) + 1, 1);
% %    ub = B^4 * ones(2*size(coefVectBL(1,:),2) + 1, 1);
%     [x,fval,exitflag] = linprog(f,A,b,[],[],lb);
%     dm = -fval;
% 
%     [val,i] = max(coefVectBU(1,:) - coefVectBL(1,:));
%     if val>upsilon
%         valMid = (coefVectBL(1,i) + coefVectBU(1,i))/2;
%         vectorBU1 = coefVectBU(1,:);
%         vectorBU1(i) = valMid;
%         vectorBL2 = coefVectBL(1,:);
%         vectorBL2(i) = valMid;
%         coefVectBL(elements+1,:) = coefVectBL(1,:);
%         coefVectBU(elements+1,:) = vectorBU1;
%         coefVectBL(elements+2,:) = vectorBL2;
%         coefVectBU(elements+2,:) = coefVectBL(1,:);
%         coefVectBL(1,:) = [];
%         coefVectBU(1,:) = [];
%         elements = elements + 1;
%     end
% end

end