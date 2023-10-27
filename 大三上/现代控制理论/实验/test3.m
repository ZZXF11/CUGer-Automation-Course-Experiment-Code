%%
%%%%%%%%%%%%%
%设计部分作业一
clc
clear

A=[-1 0 0 0;2 -3 0 0;0 0 2 0;4 -1 2 -4];
B=[0 0 1 2]';
C=[3 0 1 0];
D=[0];
n=size(A,1);

%设计状态反馈控制器 极点P1
if rank(ctrb(A,B)) == n
    disp('系统能控，可通过状态反馈任意配置极点')
else
    disp('系统不完全能控，不可通过状态反馈任意配置极点')
    disp('对系统进行能控性分解')
    m=rank(ctrb(A,B));
    [Ac1,Bc1,Cc1,Tc1,Ko1]=ctrbf(A,B,C);
    Ac=Ac1(m+1:size(Ac1,1),m+1:size(Ac1,1));
    Bc=Bc1(m+1:size(Bc1,1));
    Cc=Cc1(m+1:size(Cc1,2));
    Acn=Ac1(1:m,1:m);
    if max(eig(Acn))<0
        disp('不能控子系统渐进稳定，系统可以被镇定')
        P1=[-5,-6];
        K1=acker(Ac,Bc,P1);
        eig(Ac-Bc*K1);
        %变换
        K=[0 0 K1(1) K1(2)]*Tc1;
        eig(A-B*K)
        ABK=A-B*K
        K
    else
        disp('系统不可被镇定')
    end
end
%设计状态观测器 极点P2
if rank(obsv(A,C))==n
    disp('系统能观，可任意配置观测器极点')
else
    disp('系统不完全能观，不可任意配置观测器极点')
    disp('对系统进行能观性分解')
    o=rank(obsv(A,C));
    [Ao1,Bo1,Co1,To1,Ko1]=obsvf(A,B,C);
    Ao=Ao1(o+1:size(A,1),o+1:size(A,1));
    Bo=Bo1(o+1:size(B,1));
    Co=Co1(o+1:size(C,2));
    Aon=Ao1(1:m,1:m);
    if max(eig(Aon))<0
        disp('不能观子系统渐进稳定，可以设计状态观测器')
        P2=[-1,-2];
        Ko1=acker(Ao',Co',P2);
        Go1=Ko1';
        Go=[0 0 Go1(1) Go1(2)]';
        G=inv(To1)*Go;
        AGC=A-G*C;
        eig(AGC);
        G
    else
        disp('不能控子系统不稳定')
    end
end
%设计基于状态观测器的状态反馈 极点P1

%%
figure(1)
set(gca,'FontSize',12,'FontName','Times New Roman')
plot(out.y1.time,out.y1.signals.values(:,1),'b-',...
    out.y.time,out.y.signals.values(:,1),'r--')
xlabel('Time')
ylabel('Outout')
title('验证状态观测器控制效果(x1)')
%axis([0 100 -0.1 0.6])
grid on
legend('x1','观测器x1')
figure(2)
plot(out.y1.time,out.y1.signals.values(:,2),'b-',...
    out.y.time,out.y.signals.values(:,2),'r--')
xlabel('Time')
ylabel('Outout')
title('验证状态观测器控制效果(x2)')
grid on
legend('x2','观测器x2')
figure(3)
plot(out.y1.time,out.y1.signals.values(:,3),'b-',...
    out.y.time,out.y.signals.values(:,3),'r--')
xlabel('Time')
ylabel('Outout')
title('验证状态观测器控制效果(x3)')
grid on
legend('x3','观测器x3')
figure(4)
plot(out.y1.time,out.y1.signals.values(:,4),'b-',...
    out.y.time,out.y.signals.values(:,4),'r--')
xlabel('Time')
ylabel('Outout')
title('验证状态观测器控制效果(x4)')
grid on
legend('x4','观测器x4')

%%
figure(1)
set(gca,'FontSize',12,'FontName','Times New Roman')
% plot(out.y1.time,out.y1.signals.values(:,1),'b-',...
%     out.y.time,out.y.signals.values(:,1),'r--')
plot(out.y1.time,out.y1.signals.values(:,1),'b-')
xlabel('Time')
ylabel('Outout')
title('验证基于状态观测器的状态反馈控制效果')
%axis([0 20 -0.005 0.05])
grid on
legend('y')

%%
figure(1)
set(gca,'FontSize',12,'FontName','Times New Roman')
plot(out.y.time,out.y.signals.values(:,1),'b-',...
     out.y1.time,out.y1.signals.values(:,1),'r--')
xlabel('Time')
ylabel('Outout')
title('比较两类状态反馈的效果')
%axis([0 20 -0.005 0.05])
grid on
legend('状态反馈','基于观测器的状态反馈')