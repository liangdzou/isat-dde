function [coefMatirces,matricesXi] = ly_linear_getCoefMatrices(coefMatrix,xi,delta)

varNums = size(xi,1);
% coefMatirces = sym('As',[2^varNums,size(coefMatrix,1),size(coefMatrix,2)]);
% matricesXi = zeros(2^varNums,size(coefMatrix,1),size(coefMatrix,2));
matricesXi = sym('Xi',[2^varNums,1]);
for i = 1 : 2^varNums
    num = uint32(i-1);
    coefMatirces(:,:,i) = coefMatrix;
    matricesXi(i,1) = 1;
    for j = 1 : varNums
        coefMatirces(:,:,i) = subs(coefMatirces(:,:,i),xi(j,1),rem(num,2)*delta);
        matricesXi(i,1) = matricesXi(i,1) * ((1-xi(j,1)/delta) + rem(num,2)*(2*xi(j,1)/delta-1));
        num = (num-1)/2;
    end
end

end