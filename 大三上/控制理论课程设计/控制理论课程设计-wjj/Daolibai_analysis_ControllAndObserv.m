%% 2.5 系统分析——能控性和能观性
clc;clear
A1=[0 1 0 0;
   0 0 -1 0;
   0 0 0 1;
   0 0 22 0]
B1=[0;1;0;-2]
C1=[1 0 0 0]
D1=[0]

A=[0 1 0 0;
   0 0 -1 0;
   0 0 0 1;
   0 0 22 0]
B=[0;1;0;-2]
C=[1 0 0 0]
D=[0]

%①秩判据
fprintf('①秩判据\n\n');
n=size(A,1);
M=ctrb(A,B);%能控性矩阵
N=obsv(A,C);%能观性矩阵
fprintf('系统维数n=');disp(size(A,1));
fprintf('rank(M)=');disp(rank(M));fprintf('rank(N)=');disp(rank(N));%能控子系统4维，能观子系统3维
if (rank(M)==n)&&(rank(N)==n)
    fprintf('所以系统能控能观。\n\n');
else if rank(M)==n
         fprintf('所以系统能控不能观。\n\n');
    else if rank(N)==n
            fprintf('所以系统不能控能观。\n\n');
        else 
            fprintf('所以系统不能控不能观。\n\n');
        end
    end
end

%②约旦标准型判据
fprintf('②约旦标准型判据\n');
sys=ss(A,B,C,D);
[T,J] = jordan(A);%V为变换阵，J为约旦标准型里的A阵
fprintf('化为约旦标准型的变换阵T=: \n');disp(T);
fprintf('系统的约旦标准型为：');
fprintf('T^(-1)*A*T =  \n');disp(T^(-1)*A*T);
fprintf('T^(-1)*B =   \n');disp(T^(-1)*B);
fprintf('C*T =   \n');disp(C*T);
fprintf('每个约旦块的最后一行在输入矩阵(T^(-1)*B)中对应的行均不全为零，所以系统完全能控；\n');
fprintf('每个约旦块的第一列在输出矩阵（C*T）中对应的列均不全为零，所以系统完全能观；\n');

%或者用canon函数求约旦标准型
sys_Jordan=canon(sys,'modal');
%csys = canon(sys,type)返回指定的标准型的状态方程模型。这里的type为变换类型，
%有两个选项：'modal':对角标准型;  'companion':伴随标准型.

