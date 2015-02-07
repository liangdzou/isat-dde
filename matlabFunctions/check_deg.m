isLinear = 1;

if isLinear
    % % calculate A
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

    % % calculate As
    flag = 0;
    vars_num = size(xi,1);
    Xs = sym('X',[2^vars_num,1]);
    for i = 1 : 2^vars_num
        num = uint32(i-1);
        As(:,:,i) = A;
        Xs(i,1) = 1;
        for j = 1 : vars_num
            As(:,:,i) = subs(As(:,:,i),xi(j,1),rem(num,2)*DELTA);
            Xs(i,1) = Xs(i,1) * ((1-xi(j,1)/DELTA) + rem(num,2)*(2*xi(j,1)/DELTA-1));
            num = (num-1)/2;
        end
        % det((eye(6) - As(:,:,i))),
        if  vrho(eval(As(:,:,i))) >= 1
            flag = flag + 1;
        end
    end
    if (flag == 0)
        'The degree is OKEY',
    else
        'The degree is not enough.',
        flag,
    end
end