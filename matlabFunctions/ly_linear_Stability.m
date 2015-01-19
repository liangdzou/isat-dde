function [tmin,xfeas,lmis,S] = ly_linear_Stability(As)

As_num = size(As,3);

setlmis([]);

A_size = size(As(:,:,1),1);
for i = 1 : As_num
    S(i)=lmivar(1,[A_size 1]);
    G(i)=lmivar(2,[A_size A_size]);
end

Im = diag(ones(A_size,1));
for i = 1 : As_num
    for j = 1 : As_num
        Prop((i-1)*As_num+j) = newlmi;
        lmiterm([-((i-1)*As_num+j) 1 1 G(i)],Im,Im,'s');
        lmiterm([-((i-1)*As_num+j) 1 1 S(i)],-1,1);
        lmiterm([-((i-1)*As_num+j) 1 2 G(i)'],1,double(As(:,:,i))');
        lmiterm([-((i-1)*As_num+j) 2 2 S(j)],1,1);
    end
end

lmis=getlmis;

% solving LMIs
[tmin,xfeas] = feasp(lmis);

end
