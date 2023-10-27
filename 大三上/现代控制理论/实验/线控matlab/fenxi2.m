clc;
clear;
A=[-4,1,0,0,0,0;0,-4,0,0,0,0;0,0,3,1,0,0;0,0,0,3,0,0;0,0,0,0,-1,1;0,0,0,0,0,-1];
B=[1,3;5,7;4,3;0,0;1,6;0,0];
C=[3,1,0,5,0,0;1,4,0,2,0,0];
D=zeros(2,2);
n=size(A,1); %n为A的满秩
Qc=ctrb(A,B);
Qo=obsv(A,C);
m=rank(Qc)-1;
if rank(Qc)==n
     disp('系统完全能控')
else
    disp('系统不完全能控')
end
    %进行能控性分解
    [A1,B1,C1,T,k1]=ctrbf(A,B,C);
    %提取能控子系统
    Ac=A1(6-m:6,6-m:6)
    Bc=B1(6-m:6,1:2)
    Cc=C1(1:2,6-m:6)
    %判断能控性子系统是否完全能观
    nc=size(Ac,1);
    Qcs=obsv(Ac,Cc);
    mc=rank(Qcs)-1;
if rank(Qcs)==nc
     disp('系统完全能观')
else
    disp('系统不完全能观')
end
    %进行能观性分解
    [A2,B2,C2,T2,k2]=obsvf(Ac,Bc,Cc);
    %提取能观子系统
    Aco=A2(size(Ac,1)-mc:size(Ac,1),size(Ac,1)-mc:size(Ac,2));
    Bco=B2(size(Bc,1)-mc:size(Bc,1),1:size(Bc,2));
    Cco=C2(1:size(Cc,1),size(Cc,2)-mc:size(Cc,2));
    %对最终的结果进行判断
    no=size(Aco,1);
    Qco=ctrb(Aco,Bco);
    Qoc=obsv(Aco,Cco);
    if rank(Qco)==no
        if rank(Qoc)==no
            str='系统能控能观'
            disp('能控能观分解求得能控能观子系统：')
            sys=ss(Aco,Bco,Cco,D)
        else
            str='系统能控不能观'
        end
    else
        str='系统不能控'
    end

G=ss(A,B,C,D);
disp('最小实现求得能控能观子系统：')
G_minreal=minreal(G) %最小实现
