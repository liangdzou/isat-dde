function [ly_str,md] = ly_computer(a0, a1, xi, DELTA, LINEAR, Wa, Wco, e, md)

if LINEAR
    [ly_str,md] = ly_linear(a0, a1, xi, DELTA);
else
    ly_str = ly_poly(a0, a1, xi, DELTA, Wa, Wco, e, md);
end

end