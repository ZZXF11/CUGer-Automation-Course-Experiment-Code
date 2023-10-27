%%
%problem4-1
sys=tf([16],[1 4.8 16]);bode(sys);
grid on;title('problem4-1 Bode Diagram of G(s)=16/(s^2+4.8s+16)')
%%
sys=tf([9 1.8 9],[1 1.2 9 0]);bode(sys);
grid on;title('problem4-1 Bode Diagram of G(s)=9(s^2+0.2s+1)/s(s^2+1.2s+9)')
%%
%problem4-2
num=[1];den=[1 0.8 1];p=roots(den),nyquist(num,den);
grid on;title('problem4-2 Bode Diagram of G(s)=1/s(s^2+0.8s+1)')
%%
%problem4-3
z=[];p=[-5 -1 0];k=30;sys=zpk(z,p,k);nyquist(sys);grid on;
axis([-2,0,-1,1]);
title('problem4-3 Nyquist Plot')
%%
%problem4-4
G=zpk([],[0 -1 -10],5);
bode(G);grid on;
title('problem4-4 G(s)=5/[s(s+1)(0.1s+1)] Bode图')
%%
G=zpk([],[0 -1 -10],5);margin(G);grid on;
[