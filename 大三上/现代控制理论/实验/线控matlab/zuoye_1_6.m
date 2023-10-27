clc;
clear;
z1=[1];p1=[0 -1 -3];k1=10;
z2=[-1];p2=[0 -2 -3 -3];k2=6;
[A1,B1,C1,D1]=zp2ss(z1,p1,k1);
[A2,B2,C2,D2]=zp2ss(z2,p2,k2);
sys1=ss(A1,B1,C1,D1)
sys2=ss(A2,B2,C2,D2)
disp('系统2有重根，转换为约旦标准型')
[V2,J2]=jordan(A2);
T2=inv(V2);
sys2_new=ss2ss(sys2,T2)
disp('系统1无重根，转换为对角标准型')
[V1,J1]=eig(A1);
T1=inv(V1);
sys1_new=ss2ss(sys1,T1)
disp('canon函数直接转换为对角标准型')
disp('canon函数结果转换如下：')
csys = canon(sys1,'modal')