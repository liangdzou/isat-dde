function coefMatrix = linear_getCoefMatrix(coefBefore,coefAfter)

varNums = size(coefBefore,1);
deg = size(coefBefore,2)-1;
coefMatrix = sym('A',[varNums*(deg+1), varNums*(deg+1)]);
for i = 1 : varNums
    for j = 1 : deg +1
        rowA = (i-1)*(deg+1) + j;
        for k = 1 : varNums
            for l = 1 : deg +1
                columnA = (k-1)*(deg+1) + l;
                coefMatrix(rowA,columnA) = subs(coefAfter(i,j),coefBefore(k,l),1) - subs(coefAfter(i,j),coefBefore(k,l),0);
            end
        end
    end
end

end