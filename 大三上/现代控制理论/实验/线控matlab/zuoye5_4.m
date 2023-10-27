clc;
clear;

z=[1 -2];
p=[-1 2 -3];
k=1;
[A,B,C,D]=zp2ss(z,p,k)
P=[-2 -2 -3];
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
[z1,p1,k1]=ss2zp(A1,B,C,D);
sys=zpk(z1,p1,k1)
