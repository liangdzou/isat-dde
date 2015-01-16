% function V = impl()

initProcess;

% get templates for this segment (coefBefore) and the next segment (coefAfter)
syms t;
varNums = size(init,2);
coefBefore = sym('cb',[varNums, deg+1]);
coefAfter = sym('cf',[varNums, deg+1]);
xTemplate = getPoly(coefBefore,t);

% constraint computation
coefAfter(:,1) = subs(xTemplate,t,delta);
drivTemp = ddes(xTemplate);
for i = 1 : deg-1
    coefAfter(:,i+1) = subs(drivTemp/factorial(i),t,0);
    drivTemp = diff(drivTemp);
end
xi = sym('xi',[varNums,1]);
for i = 1 : varNums
    coefAfter(i,deg+1) = subs(drivTemp(i)/factorial(deg),t,xi(i,1));
end

% stability check, output dm '-1' if it is not stable
if linear
    coefMatrix = linear_getCoefMatrix(coefBefore,coefAfter);
    [coefMatrices,matricesXi] = linear_getCoefMatrices(coefMatrix,xi,delta);
    [tmin,xfeas,lmis,S] = linear_Stability(coefMatrices); % using LMIs
    [V,dm] = linear_Lyapunov(tmin,xfeas,lmis,S,coefBefore,coefMatrix,matricesXi,xi); % using fmincon
    charV = char(V);
end

charTarget = getDangerTarget(DangerTarget,xTemplate);

% end