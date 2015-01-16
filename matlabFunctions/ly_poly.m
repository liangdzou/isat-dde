function [ly,md,flag] = ly_poly(a0, a1, xi, Wa, Wco, delta, e, md)

% calculate Ivar0
col = 2^(size(a0,1)*size(a0,2));
Ia0 = interval(zeros(size(a0,1)*size(a0,2), col), ones(size(a0,1)*size(a0,2), col));
for i = 1 : col
    for j = 1 : size(a0,1)*size(a0,2)
        if (floor(mod(i,(2^j))/(2^(j-1))))
            Ia0(j,i) = interval(0,Wa);
        else
            Ia0(j,i) = interval(-Wa,0);
        end
    end
end
Ivar0 = [Ia0; interval(zeros(size(a0,1),col), ones(size(a0,1),col)) * delta];
% calculate Ivar1
Ivar1 = Ivar0;
var0 = [a0(:);xi];
for i = 1 : col
    Ivar1(:,i) = upIvar(var0, a1, Ivar0(:,i), Ivar1(:,i));
end

% calculate IVvar
IVvar0 = interval(zeros(size(Ivar0,1)^2, col), ones(size(Ivar0,1)^2, col));
IVvar1 = IVvar0;
for i = 1 : col
    temp = Ivar0(:,i) * transpose(Ivar0(:,i));
    IVvar0(:,i) = temp(:);
    temp = Ivar1(:,i) * transpose(Ivar1(:,i));
    IVvar1(:,i) = temp(:);
end
IVvar = transpose(IVvar1 - IVvar0);
% calculate IVvarp
Mep = [ones(size(a0,1)*size(a0,2),1)* e; ones(size(a0,1),1) * delta] * transpose([ones(size(a0,1)*size(a0,2),1)* e; ones(size(a0,1),1) * delta]);
Mep = Mep(:);
Vep = IVvar0;
for i = 1 : col
    Vep(:,i) = Mep;
end
IVvarp = transpose(IVvar0 - Vep);
% calculate bigc
Ico = interval(ones(size(a0,1)*(size(a0,2)+1))*(-1), ones(size(a0,1)*(size(a0,2)+1)))* Wco;
IVco = Ico(:);
IVcop = interval(zeros(size(IVco,1),1), IVco.sup);
bigcI = (IVvar(1,:).sup*IVcop - IVvar(1,:).inf*IVcop);
bigc = bigcI.sup;
for i = 1 : col
    bigcI = (IVvar(i,:).sup*IVcop - IVvar(i,:).inf*IVcop);
    bigc = max(bigc, bigcI.sup);
    bigcI = (IVvarp(i,:).sup*IVcop - IVvarp(i,:).inf*IVcop);
    bigc = max(bigc, bigcI.sup);
end

% mixed-integer linear programming
f = [-ones(2*size(IVvar,2), 1); 0];
intcon = 2*size(IVvar,2) + 1;
lb = zeros(2*size(IVvar,2) + 1, 1);
ub = [Wco*ones(2*size(IVvar,2),1); 1];
flag = -1;

Nums = 0;
while (flag <= 0)
    % MILP
    BIGC = ones(size(IVvar,1),1) * bigc;
    MD = ones(size(IVvar,1),1) * md;
    A = [IVvar.sup, -IVvar.inf, -BIGC;
         IVvarp.sup, -IVvarp.inf, BIGC];
    b = [MD;BIGC];
    [x,fval,flag] = intlinprog(f,intcon,A,b,[],[],lb,ub);
    
    % choose one variable from var0 (a0, xi0) and xi1 to bisect
    [mRow,I] = max(Ivar0.sup-Ivar0.inf);
    [val1,j1] = max(mRow);
    i1 = I(j1);
    temp = Ivar1(size(a0,1)*size(a0,2)+1:size(Ivar1,1), :);
    [mRow,I] = max(temp.sup-temp.inf);
    [val2,j2] = max(mRow);
    i2 = size(a0,1)*size(a0,2) + I(j2);
    
    % bisect and update Ivar0 and Ivar1
    if (val1 <= val2)
        temp = Ivar1(i2,j2);
        Ivar1(:,size(Ivar1,2)+1) = Ivar1(:,j2);
        Ivar1(i2,j2) = interval(temp.inf, (temp.sup+temp.inf)/2);
        Ivar1(i2,size(Ivar1,2)) = interval((temp.sup+temp.inf)/2, temp.sup);
        Ivar0(:,size(Ivar1,2)) = Ivar0(:,j2);
        j = j2;
    else
        temp = Ivar0(i1,j1);
        Ivar0(:,size(Ivar0,2)+1) = Ivar0(:,j1);
        Ivar0(i1,j1) = interval(temp.inf, (temp.sup+temp.inf)/2);
        Ivar0(i1,size(Ivar0,2)) = interval((temp.sup+temp.inf)/2, temp.sup);
        Ivar1(:,j1) = upIvar(var0, a1, Ivar0(:,j1), Ivar1(:,j1));
        Ivar1(:,size(Ivar0,2)) = upIvar(var0, a1, Ivar0(:,size(Ivar0,2)), Ivar1(:,j1));
        j = j1;
    end
    
    % update IVvar
    temp = Ivar1(:,j) * transpose(Ivar1(:,j)) - Ivar0(:,j) * transpose(Ivar0(:,j));
    IVvar(j,:) = transpose(temp(:));
    temp = Ivar1(:,size(Ivar1,2)) * transpose(Ivar1(:,size(Ivar1,2))) - Ivar0(:,size(Ivar1,2)) * transpose(Ivar0(:,size(Ivar1,2)));
    IVvar(size(Ivar1,2),:) = transpose(temp(:));
    
    % update IVvarp
    IVvarp = transpose(IVvar0 - Vep);
    
    % print bisecting times
    if mod(Nums, 100) == 0
        Nums,
    end
end

Mvar = var0*transpose(var0);
ly = transpose(Mvar(:))*(x(1:floor(size(x,1)/2),1) - x(floor(size(x,1)/2)+1:size(x,1)-1,1));

end



