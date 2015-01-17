% solve the LII
function [ly_str,dm] = ly_computer(a0, a1, xi, DELTA)

if linear
    A = ly_linear_A(a0,a1);
    [As,Xs] = ly_linear_As(A,xi,DELTA);
    [tmin,xfeas,lmis,S] = ly_linear_Stability(As); % using LMIs
    [ly,dm] = ly_linear(tmin,xfeas,lmis,S,a0,A,Xs,xi); % using fmincon
    ly_str = char(ly);
else
    [ly,flag] = ly_poly(a0, a1, xi, Wa, Wco, delta, e, dm);
    if flag
        ly_str = char(ly);
    else
        ly_str = '';
    end
end


end