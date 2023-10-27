clc;
clear;

A=[-3 -6 -2 -1;1 0 0 0;0 1 0 0;0 0 1 0];
P=eye(size(A,1));
Q=-P*A-A'*P;

det1= det(Q(1,1));
det2= det(Q(1:2,1:2));
det3= det(Q(1:3,1:3));
det4= det(Q);
Det=[det1;det2;det3;det4];
if min(Det)>0
     disp('系统稳定')
end
%Cholesky分解判断正定
[R,p]=chol(Q)
if p==0
    disp('系统稳定')
end