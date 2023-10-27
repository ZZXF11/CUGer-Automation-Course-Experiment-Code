clc;
clear;

A=[1 2 4;1 1 1;0 2 1];

P=sdpvar(3,3,'symmetric');
Fcond=[P>=0,A'*P+P*A<=0]

ops=sdpsettings('verbose',0,'solver','sedumi'); %verbose 冗余度 solver求解器
diagnostics=solvesdp(Fcond,[],ops);
[m p]=checkset(Fcond);
tmin = min(m);

if tmin > 0
   disp('System is stable')
else
   disp('System is unstable')
end