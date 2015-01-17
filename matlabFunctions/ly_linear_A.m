function A = ly_linear_A(a0,a1)

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

end