clear;
clc;

[A,B,C,D]=linmod('fenximoxing');

%LMI求解稳定性
P=sdpvar(size(A,1),size(A,1),'symmetric');
Fcond=[P>=0,A'*P+P*A<=0]

ops=sdpsettings('verbose',0,'solver','sedumi'); %verbose 冗余度 solver求解器
diagnostics=solvesdp(Fcond,[],ops);
[m p]=checkset(Fcond);
tmin = min(m)

if tmin > 0
   disp('System is stable')
else
   disp('System is unstable')
end

%特征根判断稳定性
Lembda=eig(A)
s=real(Lembda);
smax=max(s);

if smax>0
    sys='系统不稳定'
else 
    sys='系统稳定'
end
