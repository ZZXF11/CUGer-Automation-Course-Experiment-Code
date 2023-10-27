clc;
clear;
A=[0 1 0;-2 -3 0;-1 1 -3];
B=[0;1;2];
C=[0 0 1];
D=0;
[num,den]=ss2tf(A,B,C,D);
sys=tf(num,den)