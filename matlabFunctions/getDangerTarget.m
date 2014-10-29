function charS = getDangerTarget(prop,xTemp)

row = size(prop,1);
colomn = size(prop,2);

varNums = size(xTemp,1);
for i = 1 : varNums
    prop = subs(prop,strcat('x',int2str(i)),xTemp(i));
end

charS = '';
for i = 1 : row
    charS = strcat(charS,'(');
    for j = 1 : colomn
        charS = strcat(charS,'(');
        charS = strcat(charS, char(prop(i,j)));
        if j == colomn
            charS = strcat(charS,')');
        else
           charS = strcat(charS,') and ');
        end        
    end
    if i == row
        charS = strcat(charS,')');
    else
        charS = strcat(charS,') or ');
    end
end

% charS = strcat(charS,';');

end
