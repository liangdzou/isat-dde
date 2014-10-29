setlmis([]);
S1=lmivar(1,[8 1]);
S2=lmivar(1,[8 1]);
G1=lmivar(2,[8 8]);
G2=lmivar(2,[8 8]);

Prop1=newlmi;
lmiterm([-Prop1 1 1 G1],1,1,'s');
lmiterm([-Prop1 1 1 S1],-1,1);
lmiterm([-Prop1 1 2 G1'],1,double(As(1))');
lmiterm([-Prop1 2 2 S1],1,1);

Prop2=newlmi;
lmiterm([-Prop2 1 1 G1],1,1,'s');
lmiterm([-Prop2 1 1 S1],-1,1);
lmiterm([-Prop2 1 2 G1'],1,double(As(1))');
lmiterm([-Prop2 2 2 S2],1,1);

Prop3=newlmi;
lmiterm([-Prop3 1 1 G2],1,1,'s');
lmiterm([-Prop3 1 1 S2],-1,1);
lmiterm([-Prop3 1 2 G2'],1,double(As(2))');
lmiterm([-Prop3 2 2 S1],1,1);

Prop4=newlmi;
lmiterm([-Prop4 1 1 G2],1,1,'s');
lmiterm([-Prop4 1 1 S2],-1,1);
lmiterm([-Prop4 1 2 G2'],1,double(As(2))');
lmiterm([-Prop4 2 2 S2],1,1);

LMISYS=getlmis;
[tmin,xfeas] = feasp(LMISYS);