function [tmin,xfeas,lmis,S] = ly_linear_Stability(As)

As_num = size(As,3);
% specifying LMIs
setlmis([]);
% S = sym('S',[1, As_num]);
% G = sym('G',[1, As_num]);
sgSize = size(As(:,:,1),1);
for i = 1 : As_num
    S(i)=lmivar(1,[sgSize 1]);
    G(i)=lmivar(2,[sgSize sgSize]);
end
% Prop = sym('Prop',[1, As_num]);
for i = 1 : As_num
    for j = 1 : As_num
        Prop((i-1)*As_num+j) = newlmi;
        lmiterm([-Prop((i-1)*As_num+j) 1 1 G(i)],1,1,'s');
        lmiterm([-Prop((i-1)*As_num+j) 1 1 S(i)],-1,1);
        lmiterm([-Prop((i-1)*As_num+j) 1 2 G(i)'],1,double(As(:,:,i))');
        lmiterm([-Prop((i-1)*As_num+j) 2 2 S(j)],1,1);
    end
end
lmis=getlmis;

% solving LMIs
[tmin,xfeas] = feasp(lmis);

end
