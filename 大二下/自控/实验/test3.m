%%problem3-1
z=[];p=[-4,-6,-2,-2,0];k=1;sys=zpk(z,p,k);
[num,den]=zp2tf(z,p,k);printsys(num,den)
%求开环零极点
num=[1,2,2];den=[1,14,68,136,96,0];[p,z]=pzmap(num,den)
%绘制开环零极点图
num=[1,2,2];den=[1,14,68,136,96,0];pzmap(num,den)
%%
%绘制系统的根轨迹图
z=[-1+i,-1-i];p=[-4,-6,-2,-2,0];k=1;G=zpk(z,p,k);
figure(2);rlocus(G),title('系统的根轨迹图');
%%
%确定根轨迹的分离点与相应的根轨迹增益
z=[-1+i,-1-i];p=[-4,-6,-2,-2,0];k=1;G=zpk(z,p,k);rlocus(G)
axis([-6,0,-2,2]),[k,p]=rlocfind(G)
%%
%确定临界根轨迹增益Kcr
z=[-1+i,-1-i];p=[-4,-6,-2,-2,0];k=1;G=zpk(z,p,k);rlocus(G)
axis([-8,1,-7,7]),[k,p]=rlocfind(G)

%%
%problem3-2
num=[1 1];den=[1 3 12 -16 0];[p,z]=pzmap(num,den)
num=[1 1];den=[1 3 12 -16 0];
[z,p,k]=tf2zp(num,den);k;G=zpk(z,p,k);
figure(1);rlocus(G),title('系统的根轨迹图')
%%
%确定系统与虚轴交点的K值
num=[1 1];den=[1 3 12 -16 0];[z,p,k]=tf2zp(num,den);k;G=zpk(z,p,k);
figure(1);rlocus(G)
axis([-1 1 1 3]),[k,p]=rlocfind(G)
%%
%problem3-3
num=[1 1];den=[1 4 2 9];[z,p,k]=tf2zp(num,den);k;G=zpk(z,p,k);
figure(1);rlocus(G),title('Root Locus of problem3-3')
%%
%绘制k在（1,10）的根轨迹图
num=[1 1];den=[1 4 2 9];[z,p,k]=tf2zp(num,den);G=zpk(z,p,k);
k=1:0.1:10;figure(2);rlocus(G)
title('Root Locus of problem3-3')
%%
%problem3-4
z=[];p=[0 0 -2 -5];k=1;G=zpk(z,p,k);
figure(1);rlocus(G),title('系统根轨迹图')
%%
z=[-0.5];p=[0 0 -2 -5];k=1;G=zpk(z,p,k);
figure(1);rlocus(G),title('系统的根轨迹图')
axis([-5 5 -5 5]),[k,p]=rlocfind(G)