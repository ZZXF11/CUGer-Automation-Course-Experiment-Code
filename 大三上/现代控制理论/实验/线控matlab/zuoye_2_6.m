clc;
clear all;

A=[0 1;0 0];
B=[0;1];
C=[1,0];
D=0;
se=ss(A,B,C,D);
[y2,t2,x2]=step(se);
figure(1);
plot(t2,x2);
title('状态解响应曲线')
figure(2);
plot(t2,y2);
title('输出响应曲线')
syms s t x
eAt1=expm(A*t)
% FS=inv(s*eye(2)-A);
% eAt2=ilaplace(FS,s,t);

% 阶跃响应的解
x0=[1;1];
y1=int(expm(A*(t-x))*B,x,0,t);
y=eAt1*x0+y1
