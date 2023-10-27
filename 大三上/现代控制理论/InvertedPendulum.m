clc
clear
% 简化的线性系统
A = [0 ,1, 0, 0;
    0, 0, -1, 0;
    0 ,0, 0, 1;
    0 ,0, 22, 0];
B = [0; 1; 0; -2];
C = [1, 0, 0, 0;];
D = 0;
% % 特征值法判断系统稳定性


% P = poly(A)     % 特征多项式
% V = roots(P)    % 特征根 
% % 李雅普诺夫法判断系统稳定性
% q = [1, 0, 0, 0;
%     0, 1, 0, 0;
%     0, 0, 1, 0;
%     0, 0, 0, 1];
% if det(A) ~= 0
%     P = lyap(a, q)
%     det1 = det(P(1, 1))
%     det2 = det(P(2, 2))
%     det3 = det(P(3, 3))
%     det4 = det(P)
% end


% % 单位阶跃响应
% sys = ss(A, B, C, D);
% t=0: 0.01: 5;
% [y, t, x] = step(sys, t);
% subplot(2, 2, 1);
% plot(t, x(:,1)); grid
% xlabel('t(s)'); ylabel('x_1');
% subplot(2, 2, 2);
% plot(t, x(:, 2)); grid
% xlabel('t(s)'); ylabel('x_2');
% subplot(2, 2, 3);
% plot(t, x(:, 3)); grid
% xlabel('t(s)'); ylabel('x_3');
% subplot(2, 2, 4);
% plot(t, x(:, 4)); grid
% xlabel('t(s)'); ylabel('x_4');

% % 判断系统能控性
% Qc = ctrb(A, B);
% Qo = obsv(A, C);
% rc = rank(Qc);
% ro = rank(Qo);
% L = size(A);
% if rc == L
%     str = '系统能控'
% else
%     str = '系统不能控'
% end
% if ro == L
%     str = '系统能观'
% else 
%     str = '系统不能观'
% end

% %配置主导极点
% %设置超调量为10%
% syms k wn
% k = solve(exp(-pi*k/sqrt(1-k*k))==0.10, k);
% k = double(k)
% %设置调节时间为3s
% wn = solve(3/(max(k)*wn)==3, wn);
% wn = double(wn)
% %G=tf([wn*wn],[1 2*max(k)*wn wn*wn]);
% [z, p, k]=tf2zp([1], [1/(wn*wn), 2*max(k)/wn, 1]);
% sys1 = zpk(z, p, k);
% disp('主导极点：')
% p%主导极点

% % 求状态反馈增益阵  
% P = [-1+1.3644i, -1-1.3644i, -6, -6];
% K = acker(A, B, P)

% % 状态反馈+输出反馈下的跟踪控制
% z = [];
% p = [-1.0000-1.3644i, -1.0000+1.3644i, -6, -6];
% k = 1; 
% G = zpk(z,p,k);
% [num, den] = zp2tf(z, p, k);
% syms k1 k2 k3 k4 kt
% [k1, k2, k3, k4] = solve([k2-2*k4==20, k1-2*k3-22==146.8616, kt-20*k2==483.5086, -20*k1==741.0514, -20*kt==618.1029], [k1,k2,k3,k4]);
% K1 = double([k1, k2, k3, k4])

% 配置全维状态观测器的极点
% P = [-5, -5, -5, -5];   % 选择极点
% G = acker(A', C', P)
% AGC = A - G'*C

% 带积分矫正的状态反馈控制
z = [];
p = [-1.0000-1.3644i, -1.0000+1.3644i, -6, -6, -6];
k = 1; 
G = zpk(z,p,k);
[num, den] = zp2tf(z, p, k)
syms k1 k2 k3 k4 kt
[k1, k2, k3, k4, kt] = solve([k2-2*k4==20, k1-2*k3-22==146.8616, kt-20*k2==483.5086, -20*k1==741.0514, -20*kt==618.1029], [k1,k2,k3,k4,kt]);
K_ = double([k1, k2, k3, k4, kt])
