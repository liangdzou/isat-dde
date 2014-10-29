A=[0.8 -0.25 0 1; 1 0 0 0; 0 0 0.2 0.03; 0 0 1 0];
B=[0; 0; 1; 0]*[0.8 -0.5 0 1];
A1=A;
A2=A+0.4619*B;

setlmis([]);
S1=lmivar(1,[4 1]);
S2=lmivar(1,[4 1]);
G1=lmivar(2,[4 4]);
G2=lmivar(2,[4 4]);

Prop1=newlmi;
lmiterm([-Prop1 1 1 G1],1,1,'s');
lmiterm([-Prop1 1 1 S1],-1,1);
lmiterm([-Prop1 1 2 G1'],1,A1');
lmiterm([-Prop1 2 2 S1],1,1);

Prop2=newlmi;
lmiterm([-Prop2 1 1 G1],1,1,'s');
lmiterm([-Prop2 1 1 S1],-1,1);
lmiterm([-Prop2 1 2 G1'],1,A1');
lmiterm([-Prop2 2 2 S2],1,1);

Prop3=newlmi;
lmiterm([-Prop3 1 1 G2],1,1,'s');
lmiterm([-Prop3 1 1 S2],-1,1);
lmiterm([-Prop3 1 2 G2'],1,A2');
lmiterm([-Prop3 2 2 S1],1,1);

Prop4=newlmi;
lmiterm([-Prop4 1 1 G2],1,1,'s');
lmiterm([-Prop4 1 1 S2],-1,1);
lmiterm([-Prop4 1 2 G2'],1,A2');
lmiterm([-Prop4 2 2 S2],1,1);

LMISYS=getlmis;

c = mat2dec(LMISYS,eye(4),eye(4),eye(4),eye(4));
options = [1e-5,0,0,0,0];
[copt,xopt] = mincx(LMISYS,c,options);