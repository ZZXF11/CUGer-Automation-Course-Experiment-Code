%% 2.2 系统建模——非线性系统的线性化、2.3 系统分析——绘制并比较响应曲线 
%车重M=1kg，球重m=0.1kg，杆长L=0.5m
%x1=z，x2=z'，x3=θ，x4=θ'
clc;clear;
%①非线性模型
syms x1 x2 x3 x4 u;
M = 1;
m = 0.1;
l = 0.5;
g = 9.8;
dx1 = x2;
dx2 = (u+m*l*x4^2*sin(x3)-m*g*sin(x3)*cos(x3))/(M+m-m*cos(x3)^2);
dx3 = x4;
dx4 = (-u*cos(x3)+(M+m)*g*sin(x3)-m*l*x4^2*sin(x3)*cos(x3))/((M+m)*l-m*l*cos(x3)^2);

%②手动线性化之后的模型
disp('手动线性化之后的系统为：');
A1=[0 1 0 0;
   0 0 -1 0;
   0 0 0 1;
   0 0 22 0]
B1=[0;1;0;-2]
C1=[1 0 0 0]
D1=[0]

%③在MATLAB中应用求偏导的方法将其线性化
disp('在MATLAB中应用求偏导的方法线性化得到的系统为：');
A2=[diff(dx1,x1),diff(dx1,x2),diff(dx1,x3),diff(dx1,x4);
    diff(dx2,x1),diff(dx2,x2),diff(dx2,x3),diff(dx2,x4);
    diff(dx3,x1),diff(dx3,x2),diff(dx3,x3),diff(dx3,x4);
    diff(dx4,x1),diff(dx4,x2),diff(dx4,x3),diff(dx4,x4);]
B2=[diff(dx1,u);diff(dx2,x2);diff(dx3,u);diff(dx4,u)]
C2=C1
D2=D1

%④求出开环传递函数
[num,den]=ss2tf(A1,B1,C1,D1); %分子多项式的系数矩阵NUM和分母多项式的系数向量DEN
sys=tf(num,den)  %得到开环传函