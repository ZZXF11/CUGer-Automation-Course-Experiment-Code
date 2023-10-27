clc;
clear;
den1=[1 5 7 3];
num1=[1 3 2];
[A1,B1,C1,D1] =  tf2ss(num1,den1);
sys1=ss(A1,B1,C1,D1)
den2=[1 5 7 3];
num2=[1 2];
[A2,B2,C2,D2] =  tf2ss(num2,den2);
sys2=ss(A2,B2,C2,D2)

