clc;
clear;

A=[0 1 0;0 -1 1;0 -1 -10];
B=[0;0;10];
P=[-10 -1+sqrt(3)*i -1-sqrt(3)*i];
M=ctrb(A,B)
n=size(A,1);
rank(M)
if rank(M)==n
    disp('系统完全能控，可以配置任意极点')
    K=acker(A,B,P)
else
    disp('系统不完全能控')
    [Ac,Bc,Cc,T,K]=ctrbf(A,B,C)
end    
A1=A-B*K
disp('配置后极点')
eig(A1)