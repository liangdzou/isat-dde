function poly = expr_from_coef_mat(a,t)

if size(a,1) == 0
    return;
end

vars_num = size(a,1);
deg = size(a,2) - 1;
poly = sym('poly',[vars_num,1]);

for i = 1 : vars_num
    poly(i,1) = a(i,1);
    for j = 1 : deg
        poly(i,1) = poly(i,1) + a(i,j+1)*t^(j);
    end
end

end