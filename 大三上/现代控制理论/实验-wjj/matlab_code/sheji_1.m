%% ①设计状态反馈控制器，极点P1,验证状态反馈控制效果 选P1=[]
clc;clear
A=[-1 0 0 0;
    2 -3 0 0;
    0 0 2 0;
    4 -1 2 -4;]
B=[0;0;1;2]
C=[3 0 1 0]
D=zeros(1,1)
Init=[-0.1 0.1 0.2 -0.3];%初始条件
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
% %% ----------------①设计状态反馈控制器，极点P1➢验证状态反馈控制效果-----------
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
%matlab内嵌函数place（只适用无重根，但可是多输入系统）、acker（可有重根，但仅适用与但输入系统)
Ac=A1(3:4,3:4);%提取能控子系统
Bc=B1(3:4,1:1);
Cc=C1(1:1,3:4);
P1=[-11 -10];   %能控子系统的期望极点P1_（二维）
fprintf('给能控子系统配置的极点是：');disp(P1);
K_=place(Ac,Bc,P1);%matlab里的K=教材里的-K
K=[0 0 K_]*T;%将K转换回u=kx中的**************进行了结构分解的才要这一步变换，否则不必********************
fprintf('状态反馈后的系统为( (A-BK),B,C )  \n');
fprintf('A-B*K = \n');disp((A-B*K)');
%fprintf('acker()求得状态反馈镇定矩阵K为：\n');K2=acker(A,B,P1)%A为奇异阵，无法求逆，要报错
lamda_A_BK=eig(A-B*K);
fprintf('原本的系统特征值为');lamda_A=eig(A)
fprintf('状态反馈之后的系统特征值为lamda_(A-BK)=\n');disp(lamda_A_BK);
fprintf('极点配置成功，系统渐近稳定，验证通过。\n');



%%%%%%%%%%%%(2)课堂方法计算增益K：期望特征方程 VS 实际特征方程%%%%%%%%%%%%%%%%
% [V,DX]=eig(A);
% T=V; %V是特征向量组成的矩阵
% Aj=T^(-1)*A*T;Bj=T^(-1)*B;Cj=C*T;
% disp('把系统化为标准型可得：');
% fprintf('T^(-1)*A*T =\n');disp(Aj);
% fprintf('T^(-1)*B =\n');disp(Bj);
% fprintf('C*T =\n');disp(Cj);
% [Ac0,Bc0,Cc0,Tc0,kc0] = ctrbf(A,B,C);   %对系统按能控性分解，t为变换阵，k为各子系统的秩;
% Ac1=rot90(Ac0,2); %将ABC矩阵变换回教材上的标准形式
% Bc1=rot90(Bc0,2); %将数组 A B C 按逆时针方向旋转 k*90 度
% Cc1=rot90(Cc0,2);
% %判断状态反馈能镇定的存在性
% fprintf('不能控子系统:X2''=A22*X2 \t y2=C2*X2 \n');
% A22=Ac1((rank(M)+1):end,(rank(M)+1):end) %从 A 矩阵中提取出 A22
% C2=Cc1(:,(rank(M)+1):end)
% lamda_A22=eig(A22)
% fprintf('A22的特征值均具有负实部，所以不能控子系统是渐近稳定的，\n故原系统（A，B，C）是状态反馈能镇定的。\n\n\n');
% fprintf('取能控性分解变换矩阵Rc为:\n');
% Rc=[0 0 1 0;
%     0 0 0 1;
%     1 2 0 0;
%     2 -6 0 0]
% A_bo=Rc^(-1)*A*Rc;
% B_bo=Rc^(-1)*B;
% C_bo=C*Rc;
% % 设A_xing 为具有期望特征值的闭环系统矩阵,且X_xing'=Ac_bo*X_xing+B1_bo*u
% % 期望的闭环极点取为-10 -33
% A11=A_bo(1:rank(M),1:rank(M))
% B1=B_bo(1:rank(M),:)
% C1=C_bo(:,1:rank(M))
% P1_=[-1 -3];  %能控子系统的期望闭环极点取为-1 -3
% K_=acker(A11,B1,P1_);%求出反馈增益矩阵K
% K=[0 0 K_]*Rc %整个系统的反馈增益矩阵K，注意0要加在前面
% lamda_A_BK=eig(A-B*K);%验证状态反馈控制器设计效果
% fprintf('状态反馈之后的系统特征值lamda_(A-BK)=\n');disp(lamda_A_BK);
%????????????????为啥还有正值???????????????????


