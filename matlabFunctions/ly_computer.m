% solve the LII
function [ly_str,dm] = ly_computer(coefMat, upsilon, B)

if linear
    coefMatrix = ly_linear_getCoefMatrix(coefBefore,coefAfter);
    [coefMatrices,matricesXi] = linear_getCoefMatrices(coefMatrix,xi,delta);
    [tmin,xfeas,lmis,S] = ly_linear_Stability(coefMatrices); % using LMIs
    [ly,dm] = linear_Lyapunov(tmin,xfeas,lmis,S,coefBefore,coefMatrix,matricesXi,xi); % using fmincon
    ly_str = char(ly);
else
    [ly,dm,flag] = ly_poly(a0, a1, xi, Wa, Wco, delta, e, dm);
    if flag
        ly_str = char(ly);
    else
        ly_str = '';
    end
end


end