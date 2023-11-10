%大数据实习第三部分
%张宇一
%2022年5月31日
%班级231192
%数据导入
%demo = table2array(datapltr(1:20000,2:4));
%% 数据预处理部分
id = [0 NaN];
TF = ismissing(demo,id);   %查询demo中缺失值所在的位置
demo_1 = demo; %删除缺失值后的矩阵
for i = size(TF,1):-1:4
    for j = 1:3
        if TF(i-3,j)+TF(i-2,j)+TF(i-1,j) > 2 %连续三行的空值直接删除
            demo_1(i,:) = [];
        end
    end
end
%TF2 = ismissing(demo_1,id)

%数据可视化
figure (1)
subplot(2,5,1)
plot(demo(:,1),demo(:,3),'o');
title('处理前的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,2)
plot(demo(:,2),demo(:,3),'o');
title('处理前的风向功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,3)
histogram(demo(:,1))
title('处理前风速直方图');
subplot(2,5,4)
histogram(demo(:,2))
title('处理前的风向直方图');
subplot(2,5,5)
polarhistogram(demo(:,2))
title('处理前的风向玫瑰图');
subplot(2,5,6)
plot(demo_1(:,1),demo_1(:,3),'o');
title('删除缺失值的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,7)
plot(demo_1(:,2),demo_1(:,3),'o');
title('删除缺失值的风向功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,8)
histogram(demo_1(:,1))
title('删除缺失值的风速直方图');
subplot(2,5,9)
histogram(demo_1(:,2))
title('删除缺失值的风向直方图');
subplot(2,5,10)
polarhistogram(demo_1(:,2))
title('处理前的风向玫瑰图');
%% DBSCAN剔除离群点
demo_2 = [demo_1(:,1),demo_1(:,3)];  %风速+功率
demo_DP = [demo_1(:,2),demo_1(:,3)]; %风向+功率
[IDX, isnoise]=DBSCAN(demo_2,5,5);  %DCSCAN 其中IDX为类标签 
[IDX_DP, isnoise_DP]=DBSCAN(demo_2,5,5);  %DCSCAN 其中IDX为类标签 


% 绘制散点图观察DBSCAN的效果
figure (2)
subplot(1,2,1)
gscatter(demo_2(:,1),demo_2(:,2),IDX); %按IDX的不同，分组绘制散点图
title('使用DBSCAN识别风速功率图的离群点')
subplot(1,2,2)
gscatter(demo_DP(:,1),demo_DP(:,2),IDX_DP); %按IDX的不同，分组绘制散点图
title('使用DBSCAN识别风向功率图的离群点')


%根据DBSCAN的聚类 剔除离群点
demo_3 = demo_2;  %用DBSCAN去除离群点后的矩阵（风速+功率）
for i = size(isnoise):-1:1 %需要从后往前剔除 保证索引不变
    if isnoise(i) == 1
        demo_3(i,:) = [];
    end
end
demo_DP_2 = demo_DP;
for i = size(isnoise_DP):-1:1 %需要从后往前剔除 保证索引不变
    if isnoise_DP(i) == 1
        demo_DP_2(i,:) = [];
    end
end

%剔除效果可视化
figure (3)
subplot(2,5,1)
plot(demo_1(:,1),demo_1(:,3),'o');
title('删除缺失值的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,2)
plot(demo_1(:,2),demo_1(:,3),'o');
title('删除缺失值的风向功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,3)
histogram(demo_1(:,1))
title('删除缺失值的风速直方图');
subplot(2,5,4)
histogram(demo_1(:,2))
title('删除缺失值的风向直方图');
subplot(2,5,5)
polarhistogram(demo_1(:,2))
title('处理前的风向玫瑰图');
subplot(2,5,6)
plot(demo_3(:,1),demo_3(:,2),'o');
axis([0 31.88 0 3000])
title('DBSCAN去除离群点后的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,7)
plot(demo_DP_2(:,1),demo_DP_2(:,2),'o');
title('DBSCAN去除离群点后的风向功率图');
xlabel('实测风向v');ylabel('发电功率W');
subplot(2,5,8)
histogram(demo_3(:,1))
axis([0 31.88 0 1400])
title('DBSCAN去除离群点后的风速直方图');
subplot(2,5,9)
histogram(demo_DP_2(:,1))
title('DBSCAN去除离群点后的风向直方图');
subplot(2,5,10)
polarhistogram(demo_DP_2(:,1))
title('DBSCAN去除离群点后的风向玫瑰图');
%% 使用箱线图剔除离群点
demo_4 = rmoutliers(demo_2,'quartiles');%去除离群点，其中‘quartiles’的意思是删除超过1.5IQR的数据
demo_4_DP = rmoutliers(demo_DP,'quartiles');
% 将箱线图可视化
figure (4)
subplot(2,3,1)
boxplot(demo_2(:,1),'Labels','风速','Whisker',1.5)
title('剔除前的风速箱线图');
subplot(2,3,2)
boxplot(demo_DP(:,1),'Labels','风向','Whisker',1.5)
title('剔除前的风向箱线图');
subplot(2,3,3)
boxplot(demo_2(:,2),'Labels','功率','Whisker',1.5)
title('剔除前的功率箱线图');
subplot(2,3,4)
boxplot(demo_4(:,1),'Labels','风速','Whisker',2)
title('剔除后的风速箱线图');
subplot(2,3,5)
boxplot(demo_4_DP(:,1),'Labels','风向','Whisker',2)
title('剔除后的风向箱线图');
subplot(2,3,6)
boxplot(demo_4(:,2),'Labels','功率','Whisker',2)
title('剔除后的功率箱线图');

%剔除效果可视化
figure (5)
subplot(2,5,1)
plot(demo_1(:,1),demo_1(:,3),'o');
title('删除缺失值的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,2)
plot(demo_1(:,2),demo_1(:,3),'o');
title('删除缺失值的风向功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,3)
histogram(demo_1(:,1))
title('删除缺失值的风速直方图');
subplot(2,5,4)
histogram(demo_1(:,2))
title('删除缺失值的风向直方图');
subplot(2,5,5)
polarhistogram(demo_1(:,2))
title('处理前的风向玫瑰图');
subplot(2,5,6)
plot(demo_4(:,1),demo_4(:,2),'o');
axis([0 31.88 0 3000])
title('箱线图去除离群点后的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,7)
plot(demo_4_DP(:,1),demo_4_DP(:,2),'o');
title('箱线图去除离群点后的风向功率图');
xlabel('实测风向v');ylabel('发电功率W');
subplot(2,5,8)
histogram(demo_4(:,1))
axis([0 31.88 0 1400])
title('箱线图去除离群点后的风速直方图');
subplot(2,5,9)
histogram(demo_4_DP(:,1))
title('箱线图去除离群点后的风向直方图');
subplot(2,5,10)
polarhistogram(demo_4_DP(:,1))
title('箱线图去除离群点后的风向玫瑰图');

%% DBSCAN与箱线图剔除效果可视化对比
figure (6)
subplot(3,5,1)
plot(demo_1(:,1),demo_1(:,3),'o');
title('删除缺失值的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(3,5,2)
plot(demo_1(:,2),demo_1(:,3),'o');
title('删除缺失值的风向功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(3,5,3)
histogram(demo_1(:,1))
title('删除缺失值的风速直方图');
subplot(3,5,4)
histogram(demo_1(:,2))
title('删除缺失值的风向直方图');
subplot(3,5,5)
polarhistogram(demo_1(:,2))
title('处理前的风向玫瑰图');
subplot(3,5,6)
plot(demo_3(:,1),demo_3(:,2),'o');
axis([0 31.88 0 3000])
title('DBSCAN去除离群点后的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(3,5,7)
plot(demo_DP_2(:,1),demo_DP_2(:,2),'o');
title('DBSCAN去除离群点后的风向功率图');
xlabel('实测风向v');ylabel('发电功率W');
subplot(3,5,8)
histogram(demo_3(:,1))
axis([0 31.88 0 1400])
title('DBSCAN去除离群点后的风速直方图');
subplot(3,5,9)
histogram(demo_DP_2(:,1))
title('DBSCAN去除离群点后的风向直方图');
subplot(3,5,10)
polarhistogram(demo_DP_2(:,1))
title('DBSCAN去除离群点后的风向玫瑰图');
subplot(3,5,11)
plot(demo_4(:,1),demo_4(:,2),'o');
axis([0 31.88 0 3000])
title('箱线图去除离群点后的风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(3,5,12)
plot(demo_4_DP(:,1),demo_4_DP(:,2),'o');
title('箱线图去除离群点后的风向功率图');
xlabel('实测风向v');ylabel('发电功率W');
subplot(3,5,13)
histogram(demo_4(:,1))
axis([0 31.88 0 1400])
title('箱线图去除离群点后的风速直方图');
subplot(3,5,14)
histogram(demo_4_DP(:,1))
title('箱线图去除离群点后的风向直方图');
subplot(3,5,15)
polarhistogram(demo_4_DP(:,1))
title('箱线图去除离群点后的风向玫瑰图');
%% 最大最小归一化
%DBSCAN的效果比箱线图要好，故在此选择DBSCAN剔除离群点的数据
figure(7)
demo_5_T = mapminmax(demo_3',0,1); %归一化到0-1的区间
demo_5 = demo_5_T';
subplot(1,2,1)
plot(demo_5(:,1),demo_5(:,2),'o')
title('最大最小归一化_风速功率')
demo_DP_3_T = mapminmax(demo_DP_2',0,1);
demo_DP_3 = demo_DP_3_T';
subplot(1,2,2)
plot(demo_DP_3(:,1),demo_DP_3(:,2),'o')
title('最大最小归一化_风向功率')

%% 聚类部分
% DBSCAN聚类
[IDX_DB_SP, isnoise_DB_SP]=DBSCAN(demo_5,0.02,18);  %DCSCAN 其中IDX为类标签 
[IDX_DB_DP, isnoise_DB_DP]=DBSCAN(demo_DP_3,0.04,120);  %DCSCAN 其中IDX为类标签 
figure (8)
subplot(1,2,1)
gscatter(demo_5(:,1),demo_5(:,2),IDX_DB_SP); %按IDX的不同，分组绘制散点图
title('使用DBSCAN对风速功率聚类')
subplot(1,2,2)
gscatter(demo_DP_3(:,1),demo_DP_3(:,2),IDX_DB_DP); %按IDX的不同，分组绘制散点图
title('使用DBSCAN对风向功率聚类')

%% k-means聚类
% 肘部法
SSE_SP = [0,0;];%用于存放不同k值时的组内平方和
for i = 1:4
    [B,CC,sse]=kmeans11(demo_5,i);%第一个属性为类标签，第二个属性为类中心，第三个属性为组内平方和
    SSE_SP(i,:) = [i,sse];
end
% 肘部法可视化
figure(9)
plot(SSE_SP(:,1),SSE_SP(:,2))
%利用肘部法确定最佳的K值为2
[L_SP,center_SP,SSE_SP_K2]=kmeans11(demo_5,2);%对风速进行聚类
%[L_DP,center_DP,SSE_DP_K2]=kmeans11(demo_DP_3,2);%对风速进行聚类

%聚类效果可视化
figure(10)
subplot(1,2,1)
gscatter(demo_5(:,1),demo_5(:,2),L_SP); %按L的不同，分组绘制散点图
xlabel('实测风速V');ylabel('发电功率W');
title('K_means聚类效果可视化—风速功率')
subplot(1,2,2)
gscatter(demo_DP_3(:,1),demo_DP_3(:,2),L_SP); %按L的不同，分组绘制散点图
xlabel('实测风向D');ylabel('发电功率W');
title('K_means聚类效果可视化—风向功率')

%根据k-means的结果将数据分类
L1_SP = [0,0;];%存放第一类风速功率
L1_DP = [0,0;];%存放第一类风向功率
L2_SP = [0,0;];%存放第二类风速功率
L2_DP = [0,0;];%存放第二类风向功率
L1n = 1;%用于计数，没有实际意义
L2n = 1;
for i = 1:size(L_SP,2)
    if L_SP(i) == 1
        L1_SP(L1n,:) = demo_5(i,:);
        L1_DP(L1n,:) = demo_DP_3(i,:);
        L1n =L1n+1;
    end
    if L_SP(i) == 2
        L2_SP(L2n,:) = demo_5(i,:);
        L2_DP(L2n,:) = demo_DP_3(i,:);
        L2n =L2n+1;
    end   
end

%对两类数据进行可视化
figure(11)
subplot(2,5,1)
plot(L1_SP(:,1),L1_SP(:,2),'o');
title('第一类风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,2)
plot(L1_DP(:,1),L1_DP(:,2),'o');
title('第一类风向功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,3)
histogram(L1_SP(:,1))
title('第一类风速直方图');
subplot(2,5,4)
histogram(L1_DP(:,1))
title('第一类风向直方图');
subplot(2,5,5)
polarhistogram(L1_DP(:,2))
title('第一类风向玫瑰图');
subplot(2,5,6)
plot(L2_SP(:,1),L2_SP(:,2),'o');
title('第二类风速功率图');
xlabel('实测风速v');ylabel('发电功率W');
subplot(2,5,7)
plot(L2_DP(:,1),L2_DP(:,2),'o');
title('第二类风向功率图');
xlabel('实测风向v');ylabel('发电功率W');
subplot(2,5,8)
histogram(L2_SP(:,1))
title('第二类风速直方图');
subplot(2,5,9)
histogram(L2_DP(:,1))
title('第二类风向直方图');
subplot(2,5,10)
polarhistogram(L2_DP(:,1))
title('第二类风向玫瑰图');

%% 预测建模部分
%最小二乘法
%用一次函数拟合
%选取前10000项作为训练集，后面的剩余项作为测试集
Train_L1_SP = L1_SP(1:10000,:);%L1训练集
Train_L1_DP = L1_DP(1:10000,:);
Test_L1_SP = L1_SP(10000:end,:);%L1测试集
Test_L1_DP = L1_DP(10000:end,:);
%选取前4000项作为训练集，后面的剩余项作为测试集
Train_L2_SP = L2_SP(1:4000,:);%L2训练集
Train_L2_DP = L2_DP(1:4000,:);
Test_L2_SP = L2_SP(4000:end,:);%L2测试集
Test_L2_DP = L2_DP(4000:end,:);

%开始训练
%第一类（低风速）
pL1_SP = polyfit(Train_L1_SP(:,1),Train_L1_SP(:,2),1);%得到斜率和截距
pre_L1_SP = polyval(pL1_SP,Test_L1_SP(:,1));%得到拟合曲线的纵坐标(即预测的功率纵坐标）
%计算误差
[MAE_L1] = claMAE(pre_L1_SP,Test_L1_SP(:,2));
[RMSE_L1] = claRMSE(pre_L1_SP,Test_L1_SP(:,2));
%第二类（高风速）
pL2_SP = polyfit(Train_L2_SP(:,1),Train_L2_SP(:,2),1);%得到斜率和截距
pre_L2_SP = polyval(pL2_SP,Test_L2_SP(:,1));%得到拟合曲线的纵坐标(即预测的功率纵坐标）
%计算误差
[MAE_L2] = claMAE(pre_L2_SP,Test_L2_SP(:,2));
[RMSE_L2] = claRMSE(pre_L2_SP,Test_L2_SP(:,2));

%最小二乘法回归效果可视化
figure(12)
subplot(1,2,1)
plot([1:size(pre_L1_SP)],pre_L1_SP,'b-',[1:size(pre_L1_SP)],Test_L1_SP(:,2),'r-')
xlabel('风速v');ylabel('发电功率W');
title('第一类（低风速）最小二乘法拟合曲线')  
tt1=strcat('MAE:',num2str(MAE_L1),'/   ','RMSE',num2str(RMSE_L1));
lgd1 = legend('预测','实际');
title(lgd1,tt1)
subplot(1,2,2)
plot([1:size(pre_L2_SP)],pre_L2_SP,'b-',[1:size(pre_L2_SP)],Test_L2_SP(:,2),'r-')
xlabel('风速v');ylabel('发电功率W');
title('第二类（高风速）最小二乘法拟合曲线')  
tt2=strcat('MAE:',num2str(MAE_L2),'/   ','RMSE',num2str(RMSE_L2));
lgd2 = legend('预测','实际');
title(lgd2,tt2)

%% BP神经网络预测效果分析
%分割训练集和测试集
L1_BP = [L1_SP(:,1),L1_DP(:,1),L1_SP(:,2)];
L2_BP = [L2_SP(:,1),L2_DP(:,1),L2_SP(:,2)];
L1_BP_train = L1_BP(1:10000,:);
L1_BP_test = L1_BP(10000:end,:);
L2_BP_train = L2_BP(1:4000,:);
L2_BP_test = L2_BP(4000:end,:);

%开始训练模型
[error_1,BPoutput_1]=BP_error(L1_BP_train(:,1:2),L1_BP_train(:,3),L1_BP_test(:,1:2),L1_BP_test(:,3)) ;
[error_2,BPoutput_2]=BP_error(L2_BP_train(:,1:2),L2_BP_train(:,3),L2_BP_test(:,1:2),L2_BP_test(:,3)) ;

%误差分析
[MAE_BP_L1] = claMAE(BPoutput_1,L1_BP_test(:,3));
[RMSE_BP_L1] = claRMSE(BPoutput_1,L1_BP_test(:,3));
[MAE_BP_L2] = claMAE(BPoutput_2,L2_BP_test(:,3));
[RMSE_BP_L2] = claRMSE(BPoutput_2,L2_BP_test(:,3));

figure(13)
subplot(1,2,1)
plot([1:size(BPoutput_1')],BPoutput_1','b-',[1:size(L1_BP_test(:,3))],L1_BP_test(:,3),'r-')
xlabel('风速v');ylabel('发电功率W');
title('第一类（低风速）BP神经网络预测曲线')  
tt3=strcat('MAE:',num2str(MAE_BP_L1),'/   ','RMSE',num2str(RMSE_BP_L1));
lgd3 = legend('预测','实际');
title(lgd3,tt3)
subplot(1,2,2)
plot([1:size(BPoutput_2')],BPoutput_2','b-',[1:size(BPoutput_2')],L2_BP_test(:,3),'r-')
xlabel('风速v');ylabel('发电功率W');
title('第二类（高风速）最小二乘法拟合曲线')  
tt4=strcat('MAE:',num2str(MAE_BP_L2),'/   ','RMSE',num2str(RMSE_BP_L2));
lgd4 = legend('预测','实际');
title(lgd4,tt4)

%% 最终预测
test_end = [L1_BP_test(1:50,:);L2_BP_test(1:50,:)];%选择测试数据集，低风速、高风速各50组
%获取两个类的中心点
center1 = center_SP(1,:);
center2 = center_SP(2,:);
%分别判断每组数据是哪个类别，分类进行神经网络预测
for i = 1:size(test_end,1)
    dis1 = (test_end(i,1)-center1(1)).^2+ (test_end(i,2)-center1(2)).^2;
    dis2 = (test_end(i,1)-center2(1)).^2+ (test_end(i,2)-center2(2)).^2;
    if dis1 < dis2 %定义为低风速类
        [error_end1,BPoutput_end1]=BP_error(L1_BP_train(:,1:2),L1_BP_train(:,3),test_end(i,1:2),test_end(i,3)) ;
        fin(i) = BPoutput_end1;
    else %定义为高风速类
        [error_end2,BPoutput_end2]=BP_error(L2_BP_train(:,1:2),L2_BP_train(:,3),test_end(i,1:2),test_end(i,3)) ;
        fin(i) = BPoutput_end2;
    end
end
final = fin'; %得到的是行向量，转置成列向量
%误差分析
[MAE_BP_fin] = claMAE(final,test_end(:,3));
[RMSE_BP_fin] = claRMSE(final,test_end(:,3));
%神经网络回归效果可视化
figure(14)
plot([1:size(final)],final,'b-',[1:size(test_end(:,3))],test_end(:,3),'r-')
xlabel('风速v');ylabel('发电功率W');
title('BP神经网络预测曲线')  
tt5=strcat('MAE:',num2str(MAE_BP_fin),'/   ','RMSE',num2str(RMSE_BP_fin));
lgd5 = legend('预测','实际');
title(lgd5,tt5)
%张宇一
%2022年5月31日
%班级231192