%% --------③设计基于状态观测器的状态反馈，极点P1 ➢ 验证基于状态观测器的状态反馈控制效果-------
% 设计基于状态观测器的状态反馈，极点P1
% 验证基于状态观测器的状态反馈控制效果
% 比较上述两类状态反馈的效果(P1, P2在合理条件下任意选)
clc;clear
A=[-1 0 0 0;
    2 -3 0 0;
    0 0 2 0;
    4 -1 2 -4;]
B=[0;0;1;2]
C=[3 0 1 0]
D=[0]
Init=[-0.1 0.1 0.2 -0.05];%系统初始条件
Initobserv=[-0.1 0.1 0.1 -0.3];%观测器的初始条件
lamda_A=eig(A);
fprintf('原系统特征值为：lamda_A=');disp(lamda_A');
fprintf('系统矩阵特征根中含有正实部，故系统不能渐近稳定。\n');
n=size(A,1);
M=ctrb(A,B)%能控性矩阵
N=obsv(A,C)%能观性矩阵
fprintf('系统维数n=');disp(size(A,1));
fprintf('rank(M)=');disp(rank(M));
fprintf('rank(N)=');disp(rank(N));
if (rank(M)==n)&&(rank(N)==n)
    fprintf('所以系统能控能观\n');
else if rank(M)==n
         fprintf('所以系统能控不能观\n');
    else if rank(N)==n
            fprintf('所以系统不能控能观\n');
        else 
            fprintf('所以系统不能控不能观\n');
        end
    end
end
fprintf('但根据分离原理，我们可以对能控能观子系统分别设计K和G\n');

%设计状态反馈增益K
[A1,B1,C1,T,k] = ctrbf(A,B,C);   %对系统按能控性分解，t为变换阵，k为各子系统的秩;
Anc=A1(1:2,1:2); %提取不能控子系统
%判断不能控子系统是否渐进稳定
Q=eye(size(Anc,1));
P=lyap(Anc,Q);
det1=det(P(1,1));
det2=det(P(1:2,1:2));
Det=[det1;det2];
if min(Det)>0
    fprintf('不能控子系统渐进稳定，系统状态反馈能镇定\n\n');
else
      fprintf('不能控子系统不稳定');
end
%对能控子系统进行极点配置  
Ac=A1(3:4,3:4);%提取能控子系统
Bc=B1(3:4,1:1);
Cc=C1(1:1,3:4);
P1=[-11 -10];   %能控子系统的期望极点P1_
fprintf('给能控子系统配置的极点是：');disp(P1);
K_=place(Ac,Bc,P1);
K=[0 0 K_]*T;

%设计状态观测器增益矩阵G
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
G0=place(Ao',Co',P2_);
G_=G0';
fprintf('状态观测器的状态方程为：~x''=(A-GC)~x+Gy+Bu  \n'); 
G=T*[0;0;G_] %将反馈矩阵进行还原

