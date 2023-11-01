function [p,X]=Indirect_DSS_InteriorPoint
% 最短时间拦截，带有一个内点约束
% 间接法推导必要条件，把协态变量函数、以及OCP问题本身
% 用(mu1,mu2,pi1,pi2,t1,tf)几个参数刻画，求解参数优化问题即可
% 采用直接打靶法
% 计算量小于直接法
% edited by: Siyang Meng in Northwestern Polytechnical University

%% problem parameters
    p.ns = 4; p.nu = 1; % number of states and controls
    p.t0 = 0; 
    p.tf = 12; % tf为性能指标
    p.acc=60;
    p.X10 = 0; p.X20 = 0; p.X30=0; p.X40=0;% initial conditions
    p.X11 = 1500; p.X21=300; % interior point the trajectory passes
    p.X1f = 2000; p.X2f = 0; % boundary conditions
    
%% shooting parameters
    p.nt1 = 30;     % number of node points in Phase 1
    p.nt2 = 10;      % number of node points in Phase 2( t1 not included )

    
%% initial guess of decision variables, based on emprical evidance
    decVar0 = [6;   % t1 initial Guess 
               2;  % tf-t1 initial Guess 
               -0.3;% mu1
               0.2;% mu2
               1.1;% pi1
               1];% pi2
%           % u 不是决策变量

    
%% solve the problem with NLP method
    options = optimoptions(@fmincon,'Display','Iter','MaxIter',1e3); % option
    [decVar_NLP,minJ] = fmincon(@(decVar) objective(decVar,p),decVar0,...
        [],[],[],[],[],[],@(x) constraints(x,p),options);
    minJ
%% obtain the optimal solution
    [~,ceq,p] = constraints(decVar_NLP,p)
    [~,X] = ode45(@(t,y) odeCon(t,y,p),p.t,[p.X10,p.X20,p.X30,p.X40]); 
    y1 = X(:,1); y2 = X(:,2); % extract states
    
%% plots
    figure(1)
    plot(y1,y2,'LineWidth',2);hold on,plot(p.X11,p.X21,'bo',p.X1f,p.X2f,'rx')
    xlabel('x/m');ylabel('y/m');
    title('弹道曲线');
    figure(2);
    plot(p.t,p.u,'LineWidth',2);
    xlabel('t/s');ylabel('θ(t)/rad');title('控制曲线');
end

%% objective function
function f = objective(decVar,p)
    f=decVar(1)+decVar(2);
%     u = x(p.u_IDX);      % extract
%     L = u.^2/2;       % integrand
%     f = trapz(p.t,L); % calculate objective
end

%% constraint function, c<=0, ceq=0
function [c,ceq,p] = constraints(decVar,p)
    p.t1 = decVar(1);
    p.dtf = decVar(2);
    p.mu1= decVar(3);
    p.mu2= decVar(4);
    p.pi1= decVar(5);
    p.pi2= decVar(6);
%     p.u = decVar(p.u_IDX); % extract
    p.t = [linspace(p.t0,p.t1,p.nt1)';
           linspace(p.t1,p.t1+p.dtf,p.nt2)']; % time horizon
    p.t(p.nt1)=p.t1-0.001;
    p.t(p.nt1+1)=p.t1+0.001;
    % 由解析表达式得到最优控制
    [p.u,p.lambda]=necessaryOptimal(p.t,p);
    [~,Y] = ode45(@(t,y) odeCon(t,y,p),p.t,[p.X10,p.X20,p.X30,p.X40]); % simulation
    % path and terminal constraints
    ceq1 = Y(p.nt1,1) - p.X11; % passes position
    ceq2 = Y(p.nt1,2) - p.X21;
    ceq3 = Y(end,1) - p.X1f; % final state conditions
    ceq4 = Y(end,2) - p.X2f;
    % interoir time and terminal time constraints
    ceq5 = p.pi1*( Y(p.nt1,3)-Y(p.nt1+1,3) )+ p.pi1*Y(p.nt1,3) + ...
            p.pi2*( Y(p.nt1,4)-Y(p.nt1+1,4) )+ p.pi2*Y(p.nt1,4);
    ceq6 = 1+p.pi1*Y(end,3)+p.pi2*Y(end,4);
    ceq = [ ceq1;
            ceq2;
            ceq3;
            ceq4;
            ceq5;
            ceq6];
    % inequality constraints
    c1= 0.1-p.t1;
    c2= -p.dtf;
    c3= p.u-pi;% Active Constraints
    c4=-p.u-pi;
    c=[ c1;
        c2;
        c3;
        c4];
end

%% indirect method result
function [theta,lambda]=necessaryOptimal(t,p)
    t1=p.t1; tf=t1+p.dtf; mu1=p.mu1; mu2=p.mu2; pi1=p.pi1; pi2=p.pi2;
    t_phase1=t(1:p.nt1);
    t_phase2=t(p.nt1+1:p.nt1+p.nt2);
    lambda1=[repmat(mu1+pi1,p.nt1,1);
             repmat(mu1    ,p.nt2,1)];
    lambda2=[repmat(mu2+pi2,p.nt1,1);
             repmat(mu2    ,p.nt2,1)];
    lambda3=[mu1*tf+t1*(mu1+pi1)-(2*mu1+pi1)*t_phase1;
             mu1*(tf-t_phase2)];
    lambda4=[mu2*tf+t1*(mu2+pi2)-(2*mu2+pi2)*t_phase1;
             mu2*(tf-t_phase2)];
    theta=atan2(lambda4,lambda3);
    theta(end)=theta(end-1);% for case that lambda3=lambda4=0
    lambda=[lambda1,lambda2,lambda3,lambda4];
end

%% derivative function
function dydt = odeCon(t,X,p)
    theta = interp1(p.t,p.u,t); % u
    dydt(1,1) = X(3);
    dydt(2,1) = X(4);
    dydt(3,1) = p.acc*cos(theta);
    dydt(4,1) = p.acc*sin(theta);
end
