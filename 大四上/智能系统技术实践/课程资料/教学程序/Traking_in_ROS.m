clear;close all;clc;

%% 创建ROS环境
rosshutdown;
rosinit('192.168.153.130');

%% 路径规划
load("officemap.mat");

robotRadius=0.25;
mapInflated=copy(map);
%膨胀障碍物，得到机器人的位形空间
inflate(mapInflated,(robotRadius+0.05)); 

%%%%%%%%%%%%%%%%%%%%%%%%%%begin%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
start = [0, 0, 0];%设置起点
goal = [0, 4, 0];%设置终点
 
bounds = [mapInflated.XWorldLimits; mapInflated.YWorldLimits; [-pi pi]];

 ss = stateSpaceDubins(bounds);
 ss.MinTurningRadius = 0.4; %最小转弯半径

 stateValidator = validatorOccupancyMap(ss);
 stateValidator.Map = mapInflated;
 stateValidator.ValidationDistance = 0.05;

 planner = plannerRRT(ss, stateValidator);
 planner.MaxConnectionDistance = 0.25;
 planner.MaxIterations = 30000;

 rng(0,'twister')   %随机数生成

[pthObj, solnInfo] = plan(planner, start, goal); %使用RRT*路径规划器规划车辆路径

 %作图显示路径规划结果
 figure ( );
 show(mapInflated);%显示地图
 hold on;
 plot(start(1), start(2), 'mo',goal(1), goal(2), 'mo');%显示起点终点
 hold on;
 plot(solnInfo.TreeData(:,1), solnInfo.TreeData(:,2), 'b.-');%显示生成树
 hold on;
 plot(pthObj.States(:,1), pthObj.States(:,2), 'r-', 'LineWidth', 2)%显示路径

interpolate(pthObj,300) % 插值


%%%%%%%%%%%%%%%%%%%%%%%%%%end%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% path=findpath(prm, startLocation, endLocation); %找出可行路径
% figure(4);
% show(prm); %作图显示路径规划结果
%% 定义机器人的当前位姿
robotCurrentLocation = [start(1)+0.02, start(2)-0.05];    %定义机器人的初始位置(设置误差)
robotGoal = [goal(1), goal(2)];                %定义机器人的目标位置
initialOrientation = 0+0.01;              %定义机器人的初始朝向(设置误差)
robotCurrentPose = [robotCurrentLocation initialOrientation];   %定义机器人的当前位姿

%% 创建控制器（纯追踪算法）
controller = controllerPurePursuit;      % 创建算法
controller.Waypoints = pthObj.States(:,1:2);             % 设置目标路径的组成点
controller.DesiredLinearVelocity = 0.3; 
controller.MaxAngularVelocity = 3;
controller.LookaheadDistance = 0.5;

goalRadius=0.05;
distanceToGoal=norm(robotCurrentLocation - robotGoal);

%% 定义 Publisher 和 Subscriber
velcomd=rospublisher('/mobile_base/commands/velocity');
%velcomd=rospublisher('/cmd_vel');
vel=rosmessage(velcomd);
odomsub=rossubscriber('/odom');

%% 运动控制
while( distanceToGoal > goalRadius )

[v1,omega1] = step(controller, robotCurrentPose);          % 根据当前Pose，计算速度和转角
vel.Linear.X=v1;
vel.Angular.Z=omega1;

send(velcomd,vel);                                         % 驱动机器人

odom=receive(odomsub,1);                                   % 收集位姿信息
robotCurrentPose=MyreadPose(odom);

robotCurrentLocation = robotCurrentPose(1:2);              % 获取驱动后Pose 
distanceToGoal = norm(robotCurrentLocation - robotGoal);   % 计算偏差

waitfor(rateControl(20));                                  % 延迟等待
end

