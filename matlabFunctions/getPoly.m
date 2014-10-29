function poly = getPoly(coefs,t)

if size(coefs,1) == 0
    return;
end

varNums = size(coefs,1);
deg = size(coefs,2) - 1;
poly = sym('poly',[varNums,1]);
for i = 1 : varNums
    poly(i,1) = coefs(i,1);
    for j = 1 : deg
        poly(i,1) = poly(i,1) + coefs(i,j+1)*t^(j);
    end
end


end