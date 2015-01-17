function [As,Xs] = ly_linear_As(A,xi,DELTA)

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
end

end