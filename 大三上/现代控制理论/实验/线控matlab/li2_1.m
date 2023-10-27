clc;
clear all;

A=[-3 1;1 -3];
B=[1;0];
syms s t  x t1
eAt1=expm(A*t);
FS=inv(s*eye(2)-A);
eAt2=ilaplace(FS,s,t);


%零状态响应  阶跃响应的解
x0=[0;0];
Time1=0:0.01:10;
xTime1=[];
for t=Time1
    eAt1=expm(A*t);
    %利用化简公式求阶跃响应
    xt=eAt1*x0+inv(A)*(eAt1-eye(2))*B;
    xTime1=[xTime1 xt];
end
figure(1);
plot(Time1,xTime1)
grid on
title('方法一：零状态响应-单位阶跃响应')

%零输入响应
x0=[1;2];
Time2=0:0.01:10;
xTime2=[];
for t=Time2
    eAt1=expm(A*t);
    xt=eAt1*x0;
    xTime2=[xTime2 xt];
end
figure(2);
plot(Time2,xTime2)
grid on
title('零输入响应')


y1=int(expm(A*(t1-x))*B,x,0,t1)
y=y1+eAt1*x0;
figure(3)
fplot(y(1),[0,10])
hold on
fplot(y(2),[0,10])
grid on
title('方法二：零状态响应-单位阶跃响应')

