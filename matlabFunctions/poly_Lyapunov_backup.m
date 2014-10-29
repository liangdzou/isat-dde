function [V,dm] = poly_Lyapunov_backup(coefBefore, coefAfter, xi, varNums, deg, coefBL, coefBU, delta)

if varNums == 1 
    funcStr = '@(cb1';
    for i = 2 : deg + 1
        funcStr = strcat(funcStr, ',cb', num2str(i));
    end
    funcStr = strcat(funcStr, ',xi1,xia1)');
else
    funcStr = '@(';
    for i = 1 : varNums
        for j = 1 : deg + 1
            funcStr = strcat(funcStr, 'cb', num2str(i), '_', num2str(j), ',');
        end
    end
    for i = 1 : varNums
        funcStr = strcat(funcStr, 'xi', num2str(i), ',');
    end
    for i = 1 : varNums - 1
        funcStr = strcat(funcStr, 'xia', num2str(i), ',');
    end
    funcStr = strcat(funcStr, 'xia', num2str(varNums), ')');
end

coefVector = [transpose(coefBefore);xi];
coefVector = coefVector(:);
varSize = size(coefVector,1);
P = sym('polyP',[varSize, varSize]);

xi1 = sym('xia',size(xi));
coefVector1 = [transpose(coefAfter);xi1];
coefVector1 = coefVector1(:);

% funcStr = strcat(funcStr, ' @(');        
% for i = 1 : varSize
%     for j = 1 : varSize
%         funcStr = strcat(funcStr, 'polyP', num2str(i), '_', num2str(j));
%         if i ~= varSize || j ~= varSize
%             funcStr = strcat(funcStr, ',');
%         end
%     end
% end
% funcStr = strcat(funcStr, ')');
    
% V = eval([funcStr, vectorize(transpose(coefVector)*P*coefVector)]);
% V1 = eval([funcStr, vectorize(transpose(coefVector1)*P*coefVector1)]);
expr1 = eval([funcStr, vectorize(transpose(coefVector1)*P*coefVector1 - transpose(coefVector)*P*coefVector)]);
expr = eval([funcStr, '[', vectElementsString(coefVector), ']']);

coefBLVect = ones(1, varNums*(deg+1)) * coefBL;
coefBUVect = ones(1, varNums*(deg+1)) * coefBU;
xiBLVect = zeros(1,2*varNums);
xiBUVect = ones(1,2*varNums) * delta;
BLVect = [coefBLVect, xiBLVect];
BUVect = [coefBUVect, xiBUVect];
varInter = interval(BLVect, BUVect);

predStr = 'expr(varInter(1)';
for i = 2 : varNums*(deg + 3)
    predStr = strcat(predStr, ', varInter(', num2str(i), ')');
end
predStr = strcat(predStr, ')');
pred = eval(predStr);

V = expr;
dm = pred;

end



