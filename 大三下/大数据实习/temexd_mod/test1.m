%最初数据可视化
figure(1)
subplot(2,2,1)
histogram(simout_00(:,1))
title('A物料流量')
subplot(2,2,2)
plot(1:7201,simout_00(:,1))
title('A物料流量')
subplot(2,2,3)
boxplot(simout_00(:,1),'Labels','A物料流量','Whisker',1)
title('箱体图')
subplot(2,2,4)
area(1:7201,simout_00(:,1))
title('A物料流量')

%小波去噪
figure(2)
subplot(3,1,1)
plot(1:size(simout_00,1),simout_00(:,1))
title('A物料流量-去噪前')
subplot(3,1,2)
simout_00wde = wdenoise(simout_00);
plot(1:size(simout_00wde,1),simout_00wde(:,1))
title('A物料流量-小波去噪')
subplot(3,1,3)
simout_00mov = movmedian(simout_00,20);
plot(1:size(simout_00mov,1),simout_00mov(:,1))
title('A物料流量-均值滤波')

%均值滤波比较
figure(20)
subplot(4,1,1)
plot(1:size(simout_00,1),simout_00(:,1))
title('A物料流量-去噪前')
subplot(4,1,2)
simout_00mov1 = movmedian(simout_00,10);
plot(1:size(simout_00mov1,1),simout_00mov1(:,1))
title('A物料流量-均值滤波-k=10')
subplot(4,1,3)
simout_00mov2 = movmedian(simout_00,20);
plot(1:size(simout_00mov2,1),simout_00mov2(:,1))
title('A物料流量-均值滤波-k=20')
subplot(4,1,4)
simout_00mov3 = movmedian(simout_00,30);
plot(1:size(simout_00mov3,1),simout_00mov3(:,1))
title('A物料流量-均值滤波-k=30')

figure(3)
subplot(3,1,1)
plot(1:size(simout_00wde,1),simout_00wde(:,1))
title('A物料流量-归一化前')
%进行最大最小归一化
subplot(3,1,2)
simout_00maxminT = mapminmax(simout_00wde');
simout_00maxmin = simout_00maxminT';
plot(1:size(simout_00maxmin,1),simout_00maxmin(:,1))
title('A物料流量-最大最小归一化')
%进行Z分数变换
subplot(3,1,3)
simout_00zscore = zscore(simout_00wde);
plot(1:size(simout_00zscore,1),simout_00zscore(:,1))
title('A物料流量-z分数')

%% 相关性分析
[R,P] = corrcoef(simout_00maxmin);
figure(4)
h = heatmap(R);
%大于0.8为强相关
power = 0.8;
%将强相关的变量筛选出来，并放入矩阵中 (行 列 相关系数)
scorr = [];
max_scorr = [0,0,0];%用于存放最强相关的变量
%用于计数
scor_set = 0;
for i = 2:size(simout_00maxmin,2)
    for ii=1:i-1
        if abs(R(ii,i)) > power
            scor_set = scor_set + 1;
            scorr(scor_set,:) = [ii,i,R(ii,i)];
        end
    end
end
out_1 = ['共找到 ',num2str(scor_set),' 个强相关变量'];
disp(out_1)
disp(scorr)
%取出最强相关的变量
for i = 1:size(scorr,1)
    if abs(scorr(i,3)) > abs(max_scorr(1,3))
       max_scorr(1,:) = scorr(i,:); 
    end
end
disp('最强相关变量为：')
disp(max_scorr)

%% 最小二乘法
%被拟合数据可视化
figure(5)
x = simout_00maxmin(:,max_scorr(:,1));
y = simout_00maxmin(:,max_scorr(:,2));
test_x = x(1:4800,:);
test_y = y(1:4800,:);
pre_x = x(4801:end,:);
pre_y = y(4801:end,:);
plot(test_x,test_y,'bo')
grid on
hold on  %在下一幅图中保持
%用一次函数拟合
p = polyfit(test_x,test_y,1);%得到斜率和截距
pre = polyval(p,test_x);%得到拟合曲线的纵坐标
plot(test_x,pre,'r-','LineWidth',1)
hold on
axis([-1 1 -1 1])
xlabel(['变量',num2str(max_scorr(:,1))]);
ylabel(['变量',num2str(max_scorr(:,2))]);
title('最小二乘法拟合曲线')  
[fitresult, gof] = poly(test_x, test_y)
%误差分析
[MAE] = claMAE(pre,test_y)
[RMSE] = claRMSE(pre,test_y)

%% 故障设置以及预处理
%小波去噪
simout_01t = wdenoise(simout_01);
simout_02t = wdenoise(simout_02);
simout_03t = wdenoise(simout_03);
simout_04t = wdenoise(simout_04);

%最大最小归一化
simout_01tt = mapminmax(simout_01t');
simout_02tt = mapminmax(simout_02t');
simout_03tt = mapminmax(simout_03t');
simout_04tt = mapminmax(simout_04t');
simout_01_end = simout_01tt';
simout_02_end = simout_02tt';
simout_03_end = simout_03tt';
simout_04_end = simout_04tt';
