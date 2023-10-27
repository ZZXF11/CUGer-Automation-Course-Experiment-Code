clc;
clear;
A=[1 -2;3 4];
B=[1;1];
C=[0 0];
D=0;
G=ss(A,B,C,D);
M=[B,A*B];
n=length(A);
rank(M)
if rank(M)==n
    disp('可控')
    [A1,B1,C1,T]=nengkong(A,B,C,n)
else
    disp('不可控')
end
%另外一种方法求能控标准型（原理未知）
Qc=ctrb(A,B);
Cm=[0 1]*inv(Qc);
Cm2=inv([Cm;Cm*A]);
sysc=ss2ss(G,inv(Cm2))

%参照书本步骤求标准型
function [D,E,F,T] = nengkong(A,B,C,n)
%能控标准型转换
T=zeros(n,n);
T(:,1)=B;
%求其特征多项式
a=poly(A);
 
for i=2:n
    T(:,i)=A*T(:,i-1)+a(1,i)*T(:,1);
end
T=fliplr(T);
%得到新的A矩阵
D=inv(T)*A*T;
%得到新的B矩阵
E=inv(T)*B;
%得到新的C矩阵
F=C*T;
end



