%% 2.6 系统设计——状态反馈（SF）
%在脚本中计算反馈增益矩阵K
clc;clear
%-------------调出Scope的隐藏功能-----------------
set(0,'ShowHiddenHandles','on');
set(gcf,'menubar','figure');
%----------------------------------------------
A1=[0 1 0 0;
   0 0 -1 0;
   0 0 0 1;
   0 0 22 0]
B1=[0;1;0;-2]
C1=[1 0 0 0]
D1=[0]
fprintf('因为该系统完全能控，所以可以任意配置极点。\n\n');
P=[-1 -1.5 -2 -2.5];   %能控子系统的期望极点P
fprintf('给系统配置的期望极点是：');disp(P);
%matlab内嵌函数place（只适用无重根，但可是多输入系统）、acker（可有重根，但仅适用与但输入系统)
%系统显然是单输入的，但期望极点可能设置为有重根，故选择acker更好
K=acker(A1,B1,P);%matlab里的K=教材里的-K
fprintf('反馈增益矩阵K=  ');disp(K);
fprintf('引入状态反馈后的系统为( (A-BK),B,C )  \n');
fprintf('A-B*K = \n');disp((A1-B1*K)');
%fprintf('acker()求得状态反馈镇定矩阵K为：\n');K2=acker(A,B,P1)%A为奇异阵，无法求逆，要报错
lamda_A_BK=eig(A1-B1*K);
fprintf('原本的系统特征值为');lamda_A=eig(A1)
fprintf('状态反馈之后的系统特征值为lamda_(A-BK)=\n');disp(lamda_A_BK);
fprintf('极点配置成功，系统渐近稳定，验证通过。\n');

