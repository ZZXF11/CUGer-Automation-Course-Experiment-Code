clc;
clear;

A1=[-1 1;2 -3];
P1=eye(size(A1,1));
Q1=-P1*A1-A1'*P1;

%Cholesky分解判断正定
[R,p]=chol(Q1);
if p==0
   disp('系统1稳定')
end

A2=[-1 1;-1 -1];
Q2=eye(size(A2,1));
P2=lyap(A2,Q2);

det1= det(Q2(1,1));
det2= det(Q2);
Det=[det1;det2];

if min(Det)>0
    disp('系统2稳定')
else
    disp('系统2不稳定')
end



