clc;
clear;
num1={[1],[-1];[0],[1]};
den1={[1 1],[1 0];[1],[1 2]};
G1=tf(num1,den1);
sys1=ss(G1);
num2={[1],[0];[0],[1]};
den2={[1],[1];[1],[1]};
G2=tf(num2,den2);
sys2=ss(G2);
sys_chuan=feedback(sys1,sys2,-1);
A=[-2 -1 0;0 0 -1;0 0 -3] ;
B=[1 0;0 1;0 1];
C=[1 -1 0;0 0 1];
D=[0 0;0 0];
[num3,den3] = ss2tf(A,B,C,D,1)
[num4,den4] = ss2tf(A,B,C,D,2)


syms s
w1=[1/(s+1) -1/s;0 1/(s+2)];
w2=[1 0;0 1];
w=inv(eye(2)+w1*w2)*w1