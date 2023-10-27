%% 1-5-1
clc;clear;
num=[1,2];
den=[1,5,7,3];
tf(num,den)
[A,B,C,D] = tf2ss(num,den)
%% 1-5-2
clc;clear
num1=[1,3,2];
den1=[1,5,7,3];
[A1,B1,C1,D1] = tf2ss(num1,den1)

%% 1-6-1
clear;clc;
z=[1];
p=[0,-1,-3];
k=10;
[A2,B2,C2,D2]=zp2ss(z,p,k);
[V,J]=jordan(A2);
T=inv(V);
[A3,B3,C3,D3]=ss2ss(A2,B2,C2,D2,T)

%% 1-6-2
format long
clear;clc;
z=[-1];
p=[0,-2,-3,-3];
k=6;
[A2,B2,C2,D2]=zp2ss(z,p,k)
[V,J]=jordan(A2);
T=inv(V);
[A3,B3,C3,D3]=ss2ss(A2,B2,C2,D2,T)

%% 1-7
clear;clc;
A=[0,1,0;-2,-3,0;-1,1,-3];
B=[0;1;2];
C=[0,0,1];
D=[0];
[num,den]=ss2tf(A,B,C,D)
G=tf(num,den)
%% 1-9-1
clear;clc;
A=[-2,1;-1,-2];
B=[0;1];
C=[1,0];
D=[0];
[V,J]=jordan(A);
T=inv(V);
[A2,B2,C2,D2]=ss2ss(A,B,C,D,T)
%% 1-9-2
clear;clc;
A=[4,1,-2;1,0,2;1,-1,3];
B=[3,1;2,7;5,3];
C=[1,2,0;0,1,1];
D=[0,0;0,0];
[V,J]=jordan(A);
T=inv(V);
[A3,B3,C3,D3]=ss2ss(A,B,C,D,T)
%% 作业1
%Kb=3 Kp=4 J1=2 J2=1 K1=5 Kn=6
clc;clear;
sys1=tf([3],[1,0,0]);
sys2=tf([1],[2,0]);
sys3=tf([6],[1,0]);
sys4=tf([4,5],[1,0]);
sys5=tf([5],[4,5]);
sys6=feedback(sys2,sys3,-1);
sys7=series(sys4,sys6);
sys8=feedback(sys7,1,-1);
sys9=series(sys5,sys8);
sys10=series(sys9,sys1);
sys=feedback(sys10,1,-1)
num=[60,75,0];
den=[8,26,64,55,60,75,0];
format rat
[A,B,C,D]=tf2ss(num,den)

%%
figure(1)
set(gca,'FontSize',12,'FontName','Times New Roman')
plot(out.y.time,out.y.signals.values(:,1),'b-')
xlabel('Time')
ylabel('Outout')
title('响应曲线')
%axis([0 10 1.4 7])
grid on
legend('y')
figure(2)
plot(out.x1.time,out.x1.signals.values(:,1),'b-',...
    out.x2.time,out.x2.signals.values(:,1),'r*',...
    out.x3.time,out.x3.signals.values(:,1),'g--')
xlabel('Time')
ylabel('Outout')
title('状态轨迹')
grid on
legend('x1','x2','x3')
%%
figure(1)
set(gca,'FontSize',12,'FontName','Times New Roman')
plot(out.y.time,out.y.signals.values(:,1),'b-')
xlabel('Time')
ylabel('Outout')
title('初值为[1,2,3]的响应曲线')
%axis([0 10 1.4 7])
grid on
legend('y')
figure(2)
plot(out.x1.time,out.x1.signals.values(:,1),'b-',...
    out.x2.time,out.x2.signals.values(:,1),'r*',...
    out.x3.time,out.x3.signals.values(:,1),'g--')
xlabel('Time')
ylabel('Outout')
title('初值为[1,2,3]的状态轨迹')
grid on
legend('x1','x2','x3')