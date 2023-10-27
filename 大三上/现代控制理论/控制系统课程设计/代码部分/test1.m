%% 判断稳定性
clc;clear;
A = [0 1 0 0;0 0 -1 0;0 0 0 1;0 0 22 0];
B = [0;1;0;-2];
C = [1 0 0 0];
D = [0];
disp('基于传递函数模型分析稳定性')
P=poly(A),V=roots(P)
[num,den]=ss2tf(A,B,C,D);
disp('作Bode图')
sys=tf(num,den)
figure(1);
bode(sys);

disp('基于传递函数模型分析性能')
figure(2);
margin(sys);grid on;
[Gm,Pm,Wcg,Wcp]=margin(sys);
magdb=20*log10(Gm);
fprintf('可知幅值裕度为%d,穿越频率为%d,相角裕度为%d,截止频率为%d\n',magdb,Wcg,Pm,Wcp)
disp('基于状态空间模型分析系统稳定性')
disp('李氏间接法')
Lambda=eig(A)
disp('李氏直接法')
%描述待求的LMI
P=sdpvar(size(A,1),size(A,1),'symmetric');% 给出待求矩阵 symmetric为对称矩阵
Fcond=[P>0,A'*P+P*A<0];% 列出所有待求LMI

%求解LMI
ops=sdpsettings('verbose',0,'solver','sedumi');% 设置求解环境
diagnostics=solvesdp(Fcond,[],ops);% 迭代求解
[m,p]=checkset(Fcond);% 返回求解结果
tmin=min(m);% 验证是否满足

try chol(Q);
disp('系统稳定')
catch ME
disp('无法判断')
end

%% 判断能控能观性
clc;clear;
A = [0 1 0 0;0 0 -1 0;0 0 0 1;0 0 22 0];
B = [0;1;0;-2];
C = [1 0 0 0];
D = [0];
Qc=ctrb(A,B);
rc=rank(Qc);
L=size(A);
if rc==L
    str='系统能控'
else
    str='系统不完全能控'
end
Qo=obsv(A,C);
ro=rank(Qo)
L=size(A);
if ro==L
    str='系统能观'
else
    str='系统不完全能观'
end
disp('约旦标准型判断方法')
J=jordan(A)
[V,J]=jordan(A)
T=inv(V)
[An,Bn,Cn,Dn]=ss2ss(A,B,C,D,T)
%% 状态反馈控（SF）
clc;clear;
A = [0 1 0 0;0 0 -1 0;0 0 0 1;0 0 22 0];
B = [0;1;0;-2];
C = [1 0 0 0];
D = [0];
Qc=ctrb(A,B);
P=[-1,-2,-1+j,-1-j];
K_SF=acker(A,B,P)
% 基于状态观测器的的状态反馈（OSF）
P=poly(A-B*K_SF),V=roots(P)
P=[-10,-10,-10,-10];
    A1=A';
    B1=C';
    K=acker(A1,B1,P);
    G=K'
    AGC=A-G*C
% 状态反馈+输出反馈 原k值会跑飞 此时重新配置极点
Qc=ctrb(A,B);
P=[-5,-5,-1+2j,-1-2j];
K_OF=acker(A,B,P)

%设计超调量为20%，调节时间为3s
syms k wn;%计算阻尼比和频率
k=solve(exp(-pi*k/sqrt(1-k^2))==0.2,k)
k=double(k);
e=max(k)
wn=solve(3.5/(e*wn)==3,wn);
wn=double(wn)
[z,p,k]=tf2zp([1],[1/(wn*wn) 2*max(k)/wn 1]);
sys1=zpk(z,p,k/wn);
p%主导极点
z=[];p1=[p(1),p(2),-5,-5,-5];k=1;
[num,den]=zp2tf(z,p1,k);
sys_1=tf(num,den);
figure(1)
step(sys_1)%验证超调量是否满足要求
%[A zeros(4,1);-C 0]-[B;0][K1 -K2]
A1=[A zeros(4,1);-C 0];
B1=[B;0];

K=acker(A1,B1,p1)
K1=K(1:4)
K2=-K(5)
