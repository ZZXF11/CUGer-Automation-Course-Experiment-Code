clc;
clear;
A1=[-2 1;1 -2];B1=[0;1];C1=[1 0];D1=0;
sys1=ss(A1,B1,C1,D1);
eig(A1)
disp('系统1无重根，转换为对角标准型')
[V1,L1]=eig(A1);
T1=inv(V1);
sys1_new1 = ss2ss(sys1,T1)
disp('canon函数结果转换如下：')
sys1_new2 = canon(sys1,'modal')
A2=[4 1 -2;1 0 2;1 -1 3];B2=[3 1;2 7;5 3];C2=[1 2 0;0 1 1];D2=0;
sys2=ss(A2,B2,C2,D2);
eig(A2)
disp('系统2有重根，转换为约旦标准型')
[V2,L2]=jordan(A2);
T2=inv(V2);
sys2_new1 = ss2ss(sys2,T2)