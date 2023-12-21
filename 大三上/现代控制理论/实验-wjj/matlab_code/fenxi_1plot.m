figure (1); %以图窗 1 作为当前图窗
plot3(out.ScopeData_x1.signals.values,out.ScopeData_x2.signals.values,out.ScopeData_x3.signals.values)
grid on; %绘制网格线
title('初值[-0.1，0.1，0.2]时系统状态轨迹 '); %设置图标题
%title('初值[1，2，3]时系统状态轨迹 '); %设置图标题
xlabel('状态变量x1');ylabel('状态变量x2');zlabel('状态变量x3'); %设置横轴、纵轴、竖轴标签
