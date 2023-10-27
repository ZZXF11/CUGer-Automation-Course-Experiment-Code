clc;
clear;

A=[-3 -6 -2 -1;1 0 0 0;0 1 0 0;0 0 1 0];

Lembda=eig(A);
s=real(Lembda);
smax=max(s);

if smax>0
    sys='系统不稳定'
else 
    sys='系统稳定'
end