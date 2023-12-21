%% 3.4 系统设计——基于状态反馈的同步控制设计
%%建立状态空间模型
clc
clear
A=[-18/7 9 0;1 -1 1;0 -14.28 0];
B=[27/7;0;0];
C=[1 0 0];
D=[1 0 0];
H=B;

%%LMI验证
P=sdpvar(3,3,'symmetric');
T=sdpvar(1,1,'full');
V=sdpvar(3,1,'full');
Fcond=[P>=0,T>=0,[P*A-V*C+A'*P'-C'*V', P*H+D'*T; T'*D+H'*P', -2*T]<=0];

ops=sdpsettings('verbose',0,'solver','sedumi');
diagnostics=solvesdp(Fcond,[],ops);
[s, p]=checkset(Fcond);
tmin=min(s);
if tmin>0
    V1=double(V);
    P1=double(P);
    disp( '系统是渐进稳定的, 控制器增益为：' );
    K=inv(P1)*V1
else
     disp(' 系统不稳定' ); 
end


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% a=9;b=14.28;c=1;m0=-1/7;m1=2/7;c=1;
% A=[-a*m1 a 0;1 -1 1;0 -b 0];
% H=[-a*(m0-m1);0;0];
% C=[1 0 0];
% D=C;
% W=1;
% P = sdpvar(3,3,'symmetric');
% T = sdpvar(1,1,'symmetric');
% V= sdpvar(3,1,'fu11');
% V=sdpvar(3,1,'full');
% S=[P*A-V*C+A'*P-C'*V' P*H+D'*W*T;T'*W'*D+H'*P -2*T];
% 
% Fcond = [P>=0, T>=0, S<=0];
% ops = sdpsettings( 'verbose', 0, 'solver' ,' sedumi' );
% diagnostics = solvesdp (Fcond,[], ops);
% [m p]= checkset(Fcond);
% tmin=min(m);
% 
% if tmin>0
%     P = doub1e(P) ;
%     T = double(T);
%     V = doub1e(V);
%     disp( '系统是渐进稳定的, 控制器增益为：' );
%     K=iny(P)*V
% else
%     disp(' System cannot be stabilized' )
% end