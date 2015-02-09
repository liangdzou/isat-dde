
init_str= '';
for i = 1 : size(INIT,1)
    if exist('ILEN', 'var')
        init_str= strcat(init_str, char(a0(i,1)), '>=', char(INIT(i,1)), ';');
        init_str= strcat(init_str, char(a0(i,1)), '<=', char(INIT(i,1)), '+', char(ILEN(i,1)), ';');
    else
        init_str= strcat(init_str, char(a0(i,1)), '=', char(INIT(i,1)), ';');    
    end
end

for i = 2 : size(a0,2)
    for j = 1:size(a0,1)
        init_str = strcat(init_str, char(a0(j,i)), '=0;');
    end
end
