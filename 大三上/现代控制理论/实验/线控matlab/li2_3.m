clc;
clear all;

A=[-3 1;1 -3];
B=[1;0];
C=[1 3];
D=0;

figure(1);
step(A,B,C,D);

x0=[1;2];
figure(2);
initial(A,B,C,D,x0);

figure(3);
t=0:0.01:20;
u=ones(1,size(t,2)).*sin(t);
lsim(A,B,C,D,u,t,x0)
