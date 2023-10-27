clc;
clear all;

A=[-3 1;1 -3];
x0=[1;2];
%零状态响应 求阶跃响应的解
r = dsolve('Dx1=-3*x1+1*x2+1,Dx2=x1-3*x2','x1(0)=0,x2(0)=0');
x1 = r.x1
x2 = r.x2

Time=0:0.01:10;
xTime=[];
for t=Time
    xt=[exp(-2*t)*(exp(2*t)/4 - 1/4) + exp(-4*t)*(exp(4*t)/8 - 1/8);exp(-2*t)*(exp(2*t)/4 - 1/4) - exp(-4*t)*(exp(4*t)/8 - 1/8)];
    xTime=[xTime xt];
end
plot(Time,xTime)