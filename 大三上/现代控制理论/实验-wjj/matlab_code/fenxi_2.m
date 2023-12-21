%% 选择两组初值[-0.1,0.1,0.2][1,2,3]，绘制如下系统的系统响应曲线, 绘制如下系统的状态轨迹

% %p是输入，h输出
% a=9;
% b=14.28;
% c=1;
% m0=-(1/7);
% m1=2/7;
% syms 
% syms x1 x2 x3 x1dao x2dao x3dao h p;
% x1dao=a*(x2-h*x1)
% x2dao=x1-x2+x3
% x3dao=-b*x2
% p=x1
% h=m1*x1+(1/2)*(m0-m1)*(abs(x1+c)-abs(x1-c))
% 
% A=[-9*h 9 0;
%     1 -1 1;
%     0 -14.28 0;]
% B=[0];
% C=[1 0 0];
% D=[0];
% sys=ss(A,B,C,D)
% 
% figure (1);
% step(sys); %做系统 sys 的阶跃响应图
% [y1,t]=step(sys) %求系统 sys 的阶跃响应 y1
% grid on;
% title('此系统的阶跃响应');
% xlabel('时间');ylabel('响应');
% 
% % initial()
% % lsim
%% 2 判断如下系统的能控能观性，若不完全能控且不完全能观，求其能控能观子系统 
clear;clc
fprintf('判断如下系统的能控能观性，若不完全能控且不完全能观，求其能控能观子系统');
A=[-4 1 0 0 0 0;
    0 -4 0 0 0 0;
    0 0 3 1 0 0;
    0 0 0 3 0 0;
    0 0 0 0 -1 1;
    0 0 0 0 0 -1]
B=[1 3;
   5 7;
   4 3;
   0 0;
   1 6;
   0 0;] 
C=[3 1 0 5 0 0;
   1 4 0 2 0 0;]
n=size(A,1);
M=ctrb(A,B);%能控性矩阵
N=obsv(A,C);%能观性矩阵
fprintf('系统维数n=');disp(size(A,1));
fprintf('rank(M)=');disp(rank(M));fprintf('rank(N)=');disp(rank(N));%能控子系统4维，能观子系统3维
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
%k的每一项表示变换矩阵计算的每一步分解出的可控状态数。k中的非零元素数表示计算T需要多少次迭代，
%sum(k)为Abar的可控部分Ac中的状态数。
[Ac0,Bc0,Cc0,Tc0,kc0] = ctrbf(A,B,C);   %对系统按能控性分解，t为变换阵，k为各子系统的秩;
Ac1=rot90(Ac0,2); %将ABC矩阵变换回教材上的标准形式
Bc1=rot90(Bc0,2); %将数组 A B C 按逆时针方向旋转 k*90 度
Cc1=rot90(Cc0,2);
fprintf('能控子系统:Xc''=Ac*X1+A12*X2+Bc*u \t y=C1X1 \n');
Ac=Ac1(1:rank(M),1:rank(M)) %从 A 矩阵中提取出 Ac
A12=Ac1(1:rank(M),(rank(M)+1):end)
Bc=Bc1(1:rank(M),:)
Cc=Cc1(:,1:rank(M))

disp('下面再对能控子系统进行能观性分解');
n1=size(Ac);   %能控子系统的维数 n1
[Ao0,Bo0,Co0,To0,ko0] = obsvf(Ac,Bc,Cc);   %对系统按能观性分解，t为变换阵，k为各子系统的秩;
Ao1=rot90(Ao0,2); %将ABC矩阵变换回教材上的标准形式
Bo1=rot90(Bo0,2); %将数组 A B C 按逆时针方向旋转 k*90 度
Co1=rot90(Co0,2);
disp('能控能观子系统: Xco''=A11*X1+B1*u  y=C1*X1');
A11=Ao1(1:rank(N),1:rank(N)) %从 Ac 矩阵中提取出A11
B1=Bo1(1:rank(N),:)
C1=Co1(:,1:rank(N))

