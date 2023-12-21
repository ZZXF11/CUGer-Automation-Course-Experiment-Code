%% ----------------②设计状态观测器，极点P2 ➢ 验证状态观测器效果-----------
clc;clear
A=[-1 0 0 0;
    2 -3 0 0;
    0 0 2 0;
    4 -1 2 -4;]
B=[0;0;1;2]
C=[3 0 1 0]
D=zeros(1,1)
%Init=[0.1 0.2 0.3 0.44];%初始条件
Init=[-0.1 0.1 0.2 0.22];%初始条件
lamda_A=eig(A);
fprintf('原系统特征值为：lamda_A=');disp(lamda_A');
fprintf('系统矩阵特征根中含有正实部，故系统不能渐近稳定。\n');
n=size(A,1);
M=ctrb(A,B)%能控性矩阵
N=obsv(A,C)%能观性矩阵
fprintf('上一问中已求出系统不完全能控，不完全能观');
fprintf('因为原系统不完全能观，所以其不能观子系统必须渐近稳定才能设计观测器,下面进行判断：\n');
[A1,B1,C1,T,k] = obsvf(A,B,C);%对系统按能观性分解
Ano=A1(1:2,1:2);%提取不能观子系统
Q=eye(size(Ano,1));%判定不能观子系统是否渐进稳定
P=lyap(Ano,Q);
det1=det(P(1,1));
det2=det(P(1:2,1:2));
Det=[det1;det2];
if min(Det)>0
    fprintf('不能观子系统渐进稳定，所以系统的状态观测器存在。');
else
    fprintf('不能观子系统不稳定');
end
%对能观子系统进行极点配置
Ao=A1(3:4,3:4)%提取能观子系统
Bo=B1(3:4,1:1);
Co=C1(1:1,3:4);
P2_=[-6;-6.6];%观测器能观部分的期望极点
K=place(Ao',Co',P2_);
G_=K';
fprintf('状态观测器的状态方程为：~x''=(A-GC)~x+Gy+Bu  \n'); 
G=T*[0;0;G_] %将反馈矩阵进行还原
lamda_Ao_GC=eig(Ao-G_*Co)
lamda_A_GC=eig(A-G*C)
fprintf('说明极点配置成功，且观测器渐近稳定，验证通过。\n');