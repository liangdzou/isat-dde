% function V = impl()

initProcess;

% get templates for this segment (coefBefore) and the next segment (coefAfter)
syms t;
vars_num = size(init,2);
a0 = sym('cb',[vars_num, deg+1]);
a1 = sym('cf',[vars_num, deg+1]);
xTemplate = getPoly(a0,t);

% constraint computation
a1(:,1) = subs(xTemplate,t,delta);
drivTemp = ddes(xTemplate);
for i = 1 : deg-1
    a1(:,i+1) = subs(drivTemp/factorial(i),t,0);
    drivTemp = diff(drivTemp);
end
xi = sym('xi',[vars_num,1]);
for i = 1 : vars_num
    a1(i,deg+1) = subs(drivTemp(i)/factorial(deg),t,xi(i,1));
end

% stability check, output dm '-1' if it is not stable
if linear
    coefMatrix = linear_getCoefMatrix(a0,a1);
    [coefMatrices,matricesXi] = linear_getCoefMatrices(coefMatrix,xi,delta);
    [tmin,xfeas,lmis,S] = linear_Stability(coefMatrices); % using LMIs
    [V,dm] = linear_Lyapunov(tmin,xfeas,lmis,S,a0,coefMatrix,matricesXi,xi); % using fmincon
    charV = char(V);
end

charTarget = getDangerTarget(DangerTarget,xTemplate);

% end