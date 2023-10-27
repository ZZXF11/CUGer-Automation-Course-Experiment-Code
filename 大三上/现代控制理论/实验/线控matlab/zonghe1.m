clc;
clear;

A=[-1 0 0 0;2 -3 0 0;0 0 2 0;4 -1 2 -4];
B=[0;0;1;2];
C=[3 0 1 0];
D=[0];
disp('能控矩阵秩')
rank(ctrb(A,B))
disp('系统极点')
eig(A)
if rank(ctrb(A,B))==size(A,1)
   disp( '系统完全能控，可任意配置极点')
else
    disp('不能任意配置极点')
end

%按能控性分解
[A1,B1,C1,Tc,kc]=ctrbf(A,B,C);
%提取不能控矩阵
Acx=A1(1:2,1:2);
disp('不能控子系统极点')
eig(Acx)
%不能控子系统极点-3 -1   能控子系统极点 -4 2
if max(eig(Acx))<0
    disp( '系统不能控子系统为稳定，状态反馈可镇定')
    %所以对能控子系统进行状态反馈使系统稳定
    %提取能控矩阵
    Ac=A1(3:4,3:4);
    Bc=B1(3:4,1:1);
    %极点P1 给定-4 -2
    P1=[-2 -4];
    %状态反馈控制器的增益K
    K1=acker(Ac,Bc,P1);
    eig(Ac+Bc*(-K1))
    %做变换
    K=[0 0 K1(1)  K1(2)]*Tc
    disp('镇定后系统极点')
    eig(A+B*(-K))
else
    disp('系统不稳定')
end

rank(obsv(A,C))
if rank(obsv(A,C))==size(A,1)
    disp('系统完全能观，可设计状态观测器')
else 
    disp('系统不能观')
end

%按能观性分解
[A2,B2,C2,To,ko]=obsvf(A,B,C);
%提取不能观矩阵
Aox=A2(1:2,1:2);
eig(Aox)
if max(eig(Aox))<0
    disp('系统不完全能观，但不能观子系统为渐进稳定，可设计状态观测器')
    %设计状态观测器
    %提取能观矩阵
    Ao=A2(3:4,3:4);
    Bo=B2(3:4,1:1);
    Co=C2(1:1,3:4);
    %极点P2 给定-4 -2
    P2=[-4 -2];
    K2=acker(Ao',Co',P2);
    G1=K2'
    eig(Ao-G1*Co)
    G=inv(To)*[0;0;G1(1);G1(2)]
    eig(A-G*C)
else
    disp('不可设计状态观测器')
end






