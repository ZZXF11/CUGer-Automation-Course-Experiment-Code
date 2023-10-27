clc;
clear;

format short
A=[0 1 0 0;0 0 -1 0;0 0 0 1;0 0 11 0];
B=[0;1;0;-1];
eig(A)
if max(eig(A))<0
    disp('系统稳定')
else
    disp('系统不稳定')
    M=ctrb(A,B)
    n=size(A,1);
    rank(M)
    if rank(M)==n
        disp('系统完全能控，可以镇定')
        P=[-5 -5 -5 -5];
        K=acker(A,B,P)
    else
        disp('系统不完全能控')
        [Ac,Bc,Cc,T,K]=ctrbf(A,B,C)
    end    
A1=A-B*K
disp('配置后极点')
eig(A1)
end