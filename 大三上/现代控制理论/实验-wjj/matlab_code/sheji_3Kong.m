clc
clear
 
A=[-1 0 0 0;2 -3 0 0;0 0 2 0;4 -1 2 -4];
B=[0;0;1;2];
C=[3 0 1 0];
Init=[-0.1 0.1 0.2 -0.3];%初始条件
n=size(A,1);
Qc=ctrb(A,B);
Qo=obsv(A,C);
 
%状态观测器
if rank(Qo) == n
    disp('系统可观测')
    P=[-3 -2 -3 -1];
    K=acker(A',C',P);
    G=K';
else
   disp( '系统不能完全能观，不能任意配置极点')
   [A1,B1,C1,T,k]=obsvf(A,B,C);
   Ano=A1(1:2,1:2);%不能观子系统
   Q=eye(size(Ano,1));%不能观子系统渐进稳定判定
   P=lyap(Ano,Q);
   det1=det(P(1,1));
   det2=det(P(1:2,1:2));
   Det=[det1;det2];
   if min(Det)>0
       disp('不能观子系统稳定')
   else
       disp('不能观子系统不稳定')
   end
   %对能观子系统进行极点配置
   Ao=A1(3:4,3:4)%能观子系统
   Bo=B1(3:4,1:1);
   Co=C1(1:1,3:4);
   P=[-1 -2];
   K1=acker(Ao',Co',P);
   G1=K1';
   X=[0;0];
   G2=[X;G1] %反馈矩阵
   G=T*G2    %将G转换回dX=AX+Bu+G(y-Y)中的G 
   eig(A-G*C)
end
%基于状态观测器的状态反馈
if rank(Qc) == n
    disp('系统可控制')
    P=[-3 -4 -5 -2];
    K=acker(A,B,P);
else
   disp( '系统不能完全控制，不能任意配置极点')
   [A1,B1,C1,T,k]=ctrbf(A,B,C);
   Anc=A1(1:2,1:2);%不能控子系统
   Q=eye(size(Anc,1));%不能控子系统渐进稳定判定
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
   Ac=A1(3:4,3:4)%能控子系统
   Bc=B1(3:4,1:1);
   Cc=C1(1:1,3:4);
   P=[-1 -3];
   K1=acker(Ac,Bc,P);
   X=[0 0];
   K2=[X,K1] %反馈增益
   K=K2*T    %将K转换回u=kx中的k
end
eig(A-B*K)
