function target_str = target(TARGET,expr0)

row = size(TARGET,1);
colomn = size(TARGET,2);

vars_num = size(expr0,1);
for i = 1 : vars_num
    TARGET = subs(TARGET,strcat('x',int2str(i)),expr0(i));
end

target_str= '';
for i = 1 : row
    target_str = strcat(target_str,'(');
    for j = 1 : colomn
        target_str = strcat(target_str,'(');
        target_str = strcat(target_str, char(TARGET(i,j)));
        if j == colomn
            target_str = strcat(target_str,')');
        else
           target_str = strcat(target_str,') and ');
        end        
    end
    if i == row
        target_str = strcat(target_str,')');
    else
        target_str = strcat(target_str,') or ');
    end
end

target_str = strcat(target_str,';');

end
