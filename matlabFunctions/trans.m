function a1 = trans(DDES, INIT, DELTA, DEG)

% get templates for this segment (coefBefore) and the next segment (coefAfter)
syms t;
vars_num = size(INIT,1);
a0 = sym('cb',[vars_num, DEG+1]);
a1 = sym('cf',[vars_num, DEG+1]);
expr0 = expr_from_coef_mat(a0,t);

% constraint computation
a1(:,1) = subs(expr0,t,DELTA);
lie_div = DDES(expr0);
for i = 1 : DEG-1
    a1(:,i+1) = subs(lie_div/factorial(i),t,0);
    lie_div = diff(lie_div);
end
xi = sym('xi',[vars_num,1]);
for i = 1 : vars_num
    a1(i,DEG+1) = subs(lie_div(i)/factorial(DEG),t,xi(i,1));
end

end