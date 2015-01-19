function [ly_str,dm] = ly_computer(a0, a1, xi, DELTA, LINEAR)

if LINEAR
    [ly_str,dm] = ly_linear(a0, a1, xi, DELTA);
else
    ly_str = ly_poly(a0, a1, xi, DELTA, Wa, Wco, e, dm);
end

end