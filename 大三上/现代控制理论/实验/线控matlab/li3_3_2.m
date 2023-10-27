clc;
clear;

A=[-2 -1 1;1 0 1;-1 0 1];
B=[1;1;1];
C=[0 0 1];
D=0;
figure(1);
step(A,B,C,D);
%原系统 极点和零点
[z,p,k]=ss2zp(A,B,C,D)
%讨论该系统的单位阶跃响应，超调量小于10％，过渡时间＜2s
%近似二阶系统考虑主导极点
wn=2.2/0.59;
wd=wn*sqrt(1-0.59^2);
p1=-0.59+wd*i;
p2=-0.59-wd*i;
if rank(ctrb(A,B))==size(A,1)
   disp( '系统完全能控，可任意配置极点')
   P=[p1 p2 -2];
   K=acker(A,B,P)
else
    disp('不能任意配置极点')
end
A1=A+B*(-K);
B1=B;
C1=C;
D1=D;
[z,p,k]=ss2zp(A1,B1,C1,D1);
sys=zpk(z,p,k);
figure(2);
pzmap(sys);
t=0:0.1:10;
figure(3);
step(sys,t);