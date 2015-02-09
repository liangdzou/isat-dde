function [ly,ly_str] = ly_poly(a0, a1, xi, xi1, DELTA, Wa, Wco, e, md)
vars = [a0(:);xi];
TEMP = vars * transpose(vars);
TEMP = transpose(TEMP(:));

% initialize Ivar
row = 2^(size(a0,1)*size(a0,2));
Ia0 = interval(zeros(row,size(a0,1)*size(a0,2)), ones(row,size(a0,1)*size(a0,2)));
for i = 1 : row
    for j = 1 : size(a0,1)*size(a0,2)
        if (floor(mod(i,(2^j))/(2^(j-1))))
            Ia0(i,j) = interval(e,Wa);
        else
            Ia0(i,j) = interval(-Wa,-e);
        end
    end
end
Ivar = [Ia0, DELTA * interval(zeros(row,size(a0,1)*2),ones(row,size(a0,1)*2))];
Aco = interval(zeros(row,size(TEMP,2)), zeros(row,size(TEMP,2)));
for i = 1 : row
    Aco(i,:) = Aco_cal(a0, a1, xi, xi1, TEMP, Ivar(i,:));
end

% mixed-integer linear programming
f = -ones(2*size(TEMP,2), 1);
lb = zeros(2*size(TEMP,2), 1);
ub = Wco*ones(2*size(TEMP,2),1);

Nums = 0;
flag = -1;
while (flag <= 0)

    % MILP
    A = [Aco.sup, -Aco.inf];
    b = ones(size(Aco,1),1) * -md;
    [x,~,flag] = linprog(f,A,b,[],[],lb,ub);
    
    % choose one variable from var0 (a0, xi0) and xi1 to bisect
    [mRow,I] = max(Ivar.sup-Ivar.inf);
    [~,j] = max(mRow);
    i = I(j);
    mid = (Ivar(i,j).sup+Ivar(i,j).inf)/2;
    Ivar = [Ivar;Ivar(i,:)];
    Ivar(size(Ivar,1),j) = interval(mid,Ivar(i,j).sup);
    Ivar(i,j) = interval(Ivar(i,j).inf, mid);
	Aco(i,:) = Aco_cal(a0, a1, xi, xi1, TEMP, Ivar(i,:));
	Aco(size(Ivar,1),:) = Aco_cal(a0, a1, xi, xi1, TEMP, Ivar(size(Ivar,1),:));
    
    Nums = Nums + 1;
end

ly = TEMP*(x(1:floor(size(x,1)/2),1) - x(floor(size(x,1)/2)+1:size(x,1),1));

if flag
    ly_str = char(ly);
else
    ly_str = '';
end


end



