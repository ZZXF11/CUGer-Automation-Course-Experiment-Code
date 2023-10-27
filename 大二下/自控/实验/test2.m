%Zyy 2021.4.16

%%
%例2-5
num=[1];den=[0.5 1];step(num,den),grid on
xlabel('t/s'),ylabel('c(t)')

%%
%例2-6
G=tf([16],[1 3.2 16]);t=0:0.1:5;c=step(G,t);
plot(t,c),grid on
Css=dcgain(G)

%%
%例2-9
num1=[16];den1=[1,10,18,16];
G1=tf(num1,den1);
num2=[1];den2=[0.5,1,1];
G2=tf(num2,den2);
t=[0:0.1:10];
step(G1,'-',G2,'--',t);
legend('原三阶系统','降阶后的二阶系统')
grid on
xlabel('time[sec]'),ylabel('step response')

%%
%例2-10
G1=tf([10],[1,2,10]);G2=tf([2,10],[1,2,10]);
G3=tf([5,10],[1,2,10]);G4=tf([10,10],[1,2,10]);
step(G1,'-',G2,'--',G3,'*',G4,'+');
legend('G1','G2增加零点-5','G3增加零点-2','G4增加零点-1');
grid on;
title('零点对单位阶跃响应曲线的影响比较');

%%
%例2-11
clear;clc;
num=[3,1,2,5,4];den=[1,4,3,5,6,2];G=tf(num,den);pzmap(G);
pole=roots(den)
[z,p,k]=tf2zp(num,den)

%%
%例2-12
clear;clc;
v=[-1+j,-1-j,-2,-4];
p=poly(v)

%%
%problem2-1
clear;clc;
num=[1,7,24,24];den=[1,10,35,50,24];
[r,p,k]=residue(num,den)

%%
%problem2-2
%第一问
clear;clc;
syms t y;
y=laplace(exp(-2*t)*sin(6*t))
pretty(y)

%%
%problem2-2
%第二问
clear;clc;
syms s F;
F=ilaplace((-s^2-s+5)/(s*(s^2+3*s+2)))

%%
%problem2-3
%单位阶跃
clear;clc;
num=1;den=[0.2,1];t=[0:0.1:4];
G=tf(num,den);
step(G,t),grid on
%%
%单位斜坡
num2=1;den2=[0.2,1];t=[0:0.1:4];u=t;
G2=tf(num2,den2);
lsim(G2,u,t),grid on
title('单位斜坡函数')
%%
%单位加速度
num3=1;den3=[0.2,1];t=[0:0.1:4];u=0.5.*t.*t;%需要使用点乘
G3=tf(num3,den3);
lsim(G3,u,t),grid on
title('单位加速度')
%%
%problem2-4
clear;clc;
num=10;den=[1,2,10];t=[0;0.1;10];
[r,p,k]=residue(num,den)
pole=roots(den)
wn=sqrt(10)
B=1/wn
%绘制单位阶跃响应曲线
num2=10;den2=[1,2,10];t=[0:0.1:10];
G2=tf(num2,den2);
step(G2,t),grid on
xlabel('t/s'),ylabel('c(t)')
%峰值与峰值时间
[y,t]=step(G2);
[Y,k]=max(y);
i=length(t);
peakvalue=Y
timetopeak=t(k)
Css=dcgain(G2);
overshoot=100*(Y-Css)/Css
while(y(i)>0000.98*Css)&(y(i)<1.02*Css)
    i=i-1;
end
settlingtime=t(i)

%%
%problem2-5
clear;clc;
G1=tf([1],[1,0,1]);G2=tf([1],[1,0.2,1]);G3=tf([1],[1,0.4,1]);G4=tf([1],[1,0.6,1]);
G5=tf([1],[1,0.8,1]);G6=tf([1],[1,1,1]);G7=tf([1],[1,1.2,1]);G8=tf([1],[1,1.4,1]);
G9=tf([1],[1,1.6,1]);G10=tf([1],[1,2,1]);G11=tf([1],[1,4,1]);t=[0:0.1:25];
step(G1,G2,G3,G4,G5,G6,G7,G8,G9,t),grid on
legend('G1','G2','G3','G4','G5','G6','G7','G8','G9')
%%
G1=tf([4],[1,2.4,4]);G2=tf([16],[1,4.8,16]);G3=tf([36],[1,7.2,36]);G4=tf([64],[1,9.6,64]);
G5=tf([100],[1,12,100]);G6=tf([144],[1,14.4,144]);t=[0:0.01:5];
step(G1,G2,G3,G4,G5,G6,t),grid on
legend('G1','G2','G3','G4','G5','G6')

%%
%problem2-6
clear;clc;
num1=[16.41,31.9995];den1=[1,12,38,52,32];
G1=tf(num1,den1);t=[0:0.1:10];
[z,p,k]=tf2zp(num1,den1);
G2=zpk(z,p,k)
G3=tf([1],[0.5,1,1])
step(G1,'-',G3,'--',t)
legend('降阶前','降阶后')

%%
%problem2-7
clear;clc;
num=[1,2,3,2,1];den=[1,2,6,7,3,1];
G=tf(num,den);
[z,p,k]=tf2zp(num,den);
sys=zpk(z,p,k)
pzmap(G);
pole=roots(den)