%作业二
clear;clc
%% 1-5
disp('习题1-5-(1):');
[A1,B1,C1,D1]=tf2ss([1,2],[1,5,7,3])
disp('习题1-5-(2):');
[A2,B2,C2,D2]=tf2ss([1,3,2],[1,5,7,3])
fprintf('1-5-(1)、1-5-(2)题模拟结构图见simulink文件ZuoYe2\n');

%% 1-7
disp('习题1-7:');
A=[ 0 1 0;
   -2 -3 0;
   -1 1 -3];
B=[0;
   1;
   2];
C=[0 0 1];
D=[0];
sys1_7ss=ss(A,B,C,D);
[num1_7,den1_7]=ss2tf(A,B,C,D)
disp('系统的传递函数为：');
sys1_7tf=tf(num1_7,den1_7)
fprintf('1-7题模拟结构图见simulink文件ZuoYe2\n');

%% 1-9
clear;
disp('习题1-9:');

%(1)
A1=[-2 1;
    1 -2];
B1=[0;
    1];
C1=[1 0];
D1=[0];
[T1,D1]=eig(A1);
fprintf('(1)\nT1=\n');disp([T1]);
disp('约旦标准型为：');
fprintf('z''=Jz+T^(-1)Bu \t,\t y=CTz \n');
disp('J1 =');disp([T1^(-1)*A1*T1]);
disp('T^(-1)B =');disp([T1^(-1)*B1]);
disp('C1T1 =');disp([C1*T1]);

%(2)
A2=[4 1 -2;
    1 0 2;
    1 -1 3;];
B2=[3 1;
    2 7;
    5 3;];
C2=[1 2 0;
    0 1 1];
D2=[0];
[T2,D2]=eig(A2);
fprintf('(2)\nT2=\n');disp([T2]);%%%%%%？？？？？？T2不对劲？？？？？%%%%%%
disp('约旦标准型为：');
fprintf('z''=Jz+T^(-1)Bu \t,\t y=CTz \n');
disp('J2 =');disp([T2^(-1)*A2*T2]);
disp('T^(-1)B =');disp([T2^(-1)*B2]);
disp('C2T2 =');disp([C2*T2]);


%% 1-10

