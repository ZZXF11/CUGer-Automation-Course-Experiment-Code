%% 2.4 系统分析——稳定性与性能
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

disp('之前环节已经求出系统的开环传递函数模型为：');
num= [0 0 1 0 -20];
den= [1 0 -22 0 0];
sys=tf(num,den)  %sys：开环传函
sys_bihuan=feedback(sys, tf([1],[1]))  %根据 开环传函 求解 闭环传函
% 求得num_bihuan=[1 0 -20], den_kaihuan=[1 0 -21 0 -20]

%①传递函数，求根的方法（极点分布位置）
r=roots(cell2mat(sys_bihuan.Denominator))    %对对闭环传函的特征多项式求根r
if max(real (r))<0
    disp('系统稳定。')
elseif max(real (r))>0
    disp('有极点位于右半平面，系统不稳定。')
else
    disp('系统临界稳定。')
end

%②传递函数，Bode图法
figure(1);
margin(sys); %做出Bode图，返回增益裕量 Gm=-Inf、相位裕量 Pm=0deg,Gm<0dB,Pm=0,所以系统不稳定
disp('从Bode图中可知，增益裕量 Gm<0dB、相位裕量 Pm=0deg,所以系统不稳定。');
grid on;

%③状态空间表达式，李亚普洛夫第一法，间接法
A=[0 1 0 0;
   0 0 -1 0;
   0 0 0 1;
   0 0 22 0]
B=[0;1;0;-2]
C=[1 0 0 0]
D=[0]
lamda_A=eig(A)
if max(lamda_A)<0
    fprintf('矩阵A的所有特征值均具有负实部，所以系统是渐近稳定的。\n');
else
    fprintf('矩阵A的特征值不是均具有负实部，所以系统是不稳定的。\n');
end

%④状态空间表达式，李亚普洛夫第二法（直接法）不用lyap()函数
disp('下面用李亚普洛夫第二法（直接法）,不用lyap()函数来解：');
P=eye(size(A,1))%先选择一个正定的P 
Q=-P*A-A'*P    %然后由李亚普洛夫方程算出Q
sign2=1;
for x=1:size(Q)     
    detxx=det(Q(1:x,1:x))   
    if detxx<=0
       sign2=0;
    end
end
%**注意：先给P解出Q，再判断Q的正定是充分条件，若不正定则不能得出否定的结果！！！**%
if sign2==1      
    fprintf('Q的各阶顺序主子式均>0，所以矩阵Q正定，该系统稳定！\n\n');
else 
     fprintf('Q的顺序主子式中有≤0的，所以矩阵Q不正定，此方法无法判断系统是否稳定！\n');
end

%因为P=lyap(A,Q)报错The solution of this Lyapunov equation does not exist or is not unique.
%所以不用解lyap函数的方法⑤

% %⑤状态空间表达式，李亚普洛夫第二法（直接法）,用lyap()函数
% disp('下面用李亚普洛夫第二法（直接法）,用lyap()函数来解：');
% Q=eye(size(A,1))   %返回一个 n×n 的单位矩阵（先确定能量递减）
% P=lyap(A,Q)
% sign=1;
% for x=1:size(P)      %希尔维斯特判据判定P是否正定
%     detx=det(P(1:x,1:x))   
%     if detx<=0
%        sign=0;
%     end
% end
% if sign==1      %输出结果，先给Q解出P，再判断P的正定是充要条件
%     fprintf('P的各阶顺序主子式均>0，所以矩阵P正定，该系统稳定！\n\n');
% else
%     disp('P不是所有顺序主子式均>0，所以矩阵P不正定，该系统不稳定！\n\n');
% end