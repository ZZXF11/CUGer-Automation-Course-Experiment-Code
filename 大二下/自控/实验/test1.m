%Zyy 2021.4.16

%%
%例1-1
num=[2 24 0 25];
den=[2,4,8,2,2];
sys=tf(num,den);

%%
%例1-2
num=4*conv([1,2],conv([1,6,3],[1,6,3]));
den=conv([1,0],conv(conv([1,1],[1,1]),conv([1,1],[1,5,2,3])));
sys=tf(num,den)

%%
%例1-3
z=2;
p=[-1,-3,-5];
k=7;
sys=zpk(z,p,k)

%%
%例1-9
n1=2;d1=[2,3,7];G1=tf(n1,d1);
G=cloop(G1,-1)

%%
%problem1-1
%第一例
num=[2,4,10,3];den=[2,9,13,4,6];sys=tf(num,den);
[z,p,k]=tf2zp(num,den);
sys1=tf(num,den)
sys2=zpk(z,p,k)
%第二例
z=[-3;-4;-5];p=[-1,-7,-9,-3];k=4;
[num,den]=zp2tf(z,p,k);
sys1=zpk(z,p,k)
sys2=tf(num,den)

%%
%problem1-2
%有理多项式
clear;clc;
num1=[2,4,10,3];den1=[2,9,13,4,6];G1=tf(num1,den1)
num2=[1,7,2];den2=[1,2,5,3];G2=tf(num2,den2)
%串联
GG1=G1*G2
%并联
GG2=G1+G2
%正反馈
GG3=feedback(GG1,GG2,1)
%负反馈
GG4=feedback(GG1,GG2,-1)

%零极点增益模型
z1=[3;5;2];p1=[7,9,4,5];k1=4;
z2=[4;6;2];p2=[1,5,2,3];k2=3;
G3=zpk(z1,p1,k1)
G4=zpk(z2,p2,k2)
%串联
ZPK1=G3*G4
%并联
ZPK2=G3+G4
%正反馈
ZPK3=feedback(G3,G4,1)
%负反馈
ZPK4=feedback(G3,G4,-1)

%%
%problem1-3
clear;clc;
n1=3;d1=conv([1,0],[1,3]);n2=1;d2=[1,2];n4=10;d4=[1,1];
n5=[7,0];d5=[1,6,8];
G1=tf(n1,d1);G2=tf(n2,d2);G3=feedback(G1,G2,1);G4=tf(n4,d4);
G5=tf(n5,d5);
G6=G4*G3;
G=feedback(G6,G5,-1)

