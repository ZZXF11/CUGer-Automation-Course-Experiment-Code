%% 例3-3
clc;clear;
A=[-3,-6,-2,-1;1,0,0,0;0,1,0,0;0,0,1,0];


%% LMI toolbox
clc;clear;
%系统参数
A=[1,2,4;1,1,1;0,2,1];
%描述待求的LMI
P=sdpvar(3,3,'symmetric');% 给出待求矩阵 symmetric为对称矩阵
Fcond=[P>0,A'*P+P*A<0];% 列出所有待求LMI

%求解LMI
ops=sdpsettings('verbose',0,'solver','sedumi');% 设置求解环境
diagnostics=solvesdp(Fcond,[],ops);% 迭代求解
[m,p]=checkset(Fcond);% 返回求解结果
tmin=min(m);% 验证是否满足
m
if tmin>0
    disp('System is stable')
else
    disp('System is unstable')
end
%%
figure(1)
set(gca,'FontSize',12,'FontName','Times New Roman')
plot(out.y.time,out.y.signals.values(:,1),'b-')
xlabel('Time')
ylabel('Outout')
title('系统响应曲线')
%axis([0 10 1.4 7])
grid on
legend('y')
figure(2)
plot3(out.x1.signals.values(:,1),...
    out.x2.signals.values(:,1),...
    out.x3.signals.values(:,1))
%plot3(out.x1.signals.values(:,1),out.x2.signals.values(:,1),out.x3.signals.values(:,1),'b-')
xlabel('Time')
ylabel('Outout')
title('状态轨迹')
grid on
%legend('x1','x2','x3')
%% 作业一
clc;clear
format rat
A=[-4,1,0,0,0,0;0,-4,0,0,0,0;0,0,3,1,0,0;0,0,0,3,0,0;0,0,0,0,-1,1;0,0,0,0,0,-1];
B=[1,3;5,7;4,3;0,0;1,6;0,0];
C=[3,1,0,5,0,0;1,4,0,2,0,0];
n=size(A,1);
Qc=ctrb(A,B);
Qo=obsv(A,C);
m=rank(Qc)-1;
if rank(Qc)==n
    str='系统完全能控'
else
    str='系统不完全能控'
    %进行能控性分解
    [A1,B1,C1,T,k]=ctrbf(A,B,C)
    Ac=A1(6-m:6,6-m:6)
    Bc=B1(6-m:6,1:2)
    Cc=C1(1:2,6-m:6)
    %判断能控性子系统是否完全能观
    nc=size(Ac,1);
    Qcson=obsv(Ac,Cc);
    mc=rank(Qcson);
    %进行能观性分解
    [A2,B2,C2,T2,k2]=obsvf(Ac,Bc,Cc);
    Aco=A2(size(Ac,1)-mc+1:size(Ac,1),size(Ac,1)-mc+1:size(Ac,2));
    Bco=B2(size(Bc,1)-mc+1:size(Bc,1),1:size(Bc,2));
    Cco=C2(1:size(Cc,1),size(Cc,2)-mc+1:size(Cc,2));
end
format long
%对最终的结果进行判断
no=size(Aco,1);
Qco=ctrb(Aco,Bco);
Qoc=obsv(Aco,Cco);
if rank(Qco)==no
    if rank(Qoc)==no
        str='系统能控能观'
        Aco
        Bco
        Cco
    else
        str='系统能控不能观'
    end
else
    str='系统不能控'
end

%%
clear;
clc;
%%%LMI 判断稳定性
disp('1.用LMI YALMIP工具箱判断')
[A,B,C,D]=linmod('assign1_3');
%描述待求的LMI
P=sdpvar(size(A,1),size(A,1),'symmetric');% 给出待求矩阵 symmetric为对称矩阵
Fcond=[P>0,A'*P+P*A<0];% 列出所有待求LMI

%求解LMI
ops=sdpsettings('verbose',0,'solver','sedumi');% 设置求解环境
diagnostics=solvesdp(Fcond,[],ops);% 迭代求解
[m,p]=checkset(Fcond);% 返回求解结果
tmin=min(m);% 验证是否满足

if tmin>0
    disp('System is stable')
else
    disp('System is unstable')
end

%%%特征值判断稳定性
disp('2.特征值判断稳定性')
Lambda=eig(A)

%%%能量的方法判断稳定性
disp('3.能量的方法判断稳定性')
P=eye(size(A,1));
Q=-P*A-A'*P;

try chol(Q);
disp('系统稳定')
catch ME
disp('无法判断')
end

%%%lyap（）函数
disp('4.lyap()函数判断')
Q=eye(size(A,1));
P=lyap(A,Q);
try chol(Q);
disp('系统稳定')
catch ME
disp('系统不稳定')
end

%% 课本3-13-（2）
clc
clear
A=[1 0 0 0;2 -3 0 0;1 0 -2 0;4 -1 -2 -4];
B=[0;0;1;2];
C=[3 0 1 0];
M=[B A*B A*A*B A*A*A*B];
rank(M);
format rat
Rc=[0 0 0 1;0 0 1 0;1 -2 0 0;2 -10 0 0];
inv(Rc);
Ac=inv(Rc)*A*Rc;
Bc=inv(Rc)*B;
Cc=C*Rc;
R0=[0 1;1/3 0];
Afco=inv(R0)*[-3 2;0 1]*R0;
Cfo=[0 3]*R0;
[1 -2;0 1]*[1/3 1/3;1/6 -1/3]*[0 1;1/3 0]
