function [ly,ly_str,md] = ly_computer(a0, a1, xi, xi1, DELTA, LINEAR, Wa, Wco, e, md)

if LINEAR
    [ly,ly_str,md] = ly_linear(a0, a1, xi, DELTA);
else
    [ly,ly_str] = ly_poly(a0, a1, xi, xi1, DELTA, Wa, Wco, e, md);
end

end
