%%  K1=1，Kp=2,Kb=3,Kn=4,J1=1,J2=2
clc;clear;
sys1=tf([1],[1 0]); %创建各子系统的传函模型
sys2=tf([4],[1 0]);
sys3=tf([2 1],[1 0]);
sys4=tf([1],[1]);
sys5=tf([1],[2,1]);
sys6=tf([3],[2 0 0]);

sys_a=feedback(sys1,sys2,-1); %对子系统进行串连、反馈连接
sys_b=series(sys3,sys_a);
sys_c=feedback(sys_b,sys4,-1);
sys_d=series(sys_c,sys5);
sys_e=series(sys_d,sys6);
sys_all=feedback(sys_e,sys4,-1) %得到整个系统的传函
sysr=minreal(sys_all) %零极点对消，得到能控能观子系统

num_all=sys_all.num{1}; %花括号{}进行索引来访问元胞的内容,提取传函的分子
den_all=sys_all.den{1}; %提取传函的分母
[A,B,C,D]=tf2ss(num_all,den_all)  %系统状态空间表达式

numr=sysr.num{1}; %花括号{}进行索引来访问元胞的内容,提取传函的分子
denr=sysr.den{1}; %提取传函的分母
[Ar,Br,Cr,Dr]=tf2ss(numr,denr)  %系统状态空间表达式
lamudaAr=eig(Ar)
lamudaA=eig(A)