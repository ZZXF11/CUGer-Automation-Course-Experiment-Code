clc
clear
 
A=[-1 0 0 0;2 -3 0 0;0 0 2 0;4 -1 2 -4];
B=[0;0;1;2];
C=[3 0 1 0];
n=size(A,1);
Qc=ctrb(A,B);
Qo=obsv(A,C);
%判断能控性
if rank(Qc) == n
    disp('系统可控制')
    %目标极点
    P1=[-3 -4 -5 -2];
    %计算给定极点下的状态反馈增益
    K=acker(A,B,P1);
else
   disp( '系统不能完全控制，不能任意配置极点')
   %按能控性分解系统
   [A1,B1,C1,T,k]=ctrbf(A,B,C);
   %不能控子系统
   Anc=A1(1:2,1:2);
   %不能控子系统渐进稳定判定
   Q=eye(size(Anc,1));
   P=lyap(Anc,Q);
   det1=det(P(1,1));
   det2=det(P(1:2,1:2));
   Det=[det1;det2];
   if min(Det)>0
       disp('不能控子系统稳定')
   else
       disp('不能控子系统不稳定')
   end
   
   %对能控子系统进行极点配置
   Ac=A1(3:4,3:4);%能控子系统
   Bc=B1(3:4,1:1);
   Cc=C1(1:1,3:4);
   P11=[-1 -2];
   K1=acker(Ac,Bc,P11);
   
   X=[0 0];
   K2=[X,K1]
   K=K2*T%将K转换回u=kx中的
end
