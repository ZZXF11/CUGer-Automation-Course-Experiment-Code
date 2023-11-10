function [error,BPoutput]=BP_error(input_train,output_train,input_test,output_test) 
%输入：1.input_train:训练集的输入数据 2.output_train：训练集的输出数据 3.测试集的输入数据 4.测试集的输入数据
%输出：1.error：预测误差集 2.BPoutput：预测结果

%找出训练数据和预测数据
% input_train=input(n(1:1900),:)';
% output_train=output(n(1:1900));
% input_test=input(n(1901:2000),:)';
% output_test=output(n(1901:2000));

input_train=input_train';
input_test=input_test';
output_train=output_train';
output_test=output_test';
%选连样本输入输出数据归一化
[inputn,inputps]=mapminmax(input_train,0,1);
[outputn,outputps]=mapminmax(output_train,0,1);

%% BP网络训练
% %初始化网络结构
net=newff(inputn,outputn,30);

net.trainParam.epochs=1000;
net.trainParam.lr=0.01;
net.trainParam.goal=0.00004;

%网络训练
net=train(net,inputn,outputn);

%% BP网络预测
%预测数据归一化
% inputn_test=mapminmax('apply',input_test,inputps);
inputn_test=mapminmax('apply',input_test,inputps);
outputn_test=mapminmax('apply',output_test,outputps);
 
%网络预测输出
an=sim(net,inputn_test);
 
%网络输出反归一化
BPoutput=mapminmax('reverse',an,outputps);

%% 结果分析

% figure(1)
% plot(BPoutput,':og')
% hold on
% plot(output_test,'-*');
% legend('预测输出','期望输出')
% title('BP网络预测输出','fontsize',12)
% ylabel('函数输出','fontsize',12)
% xlabel('样本','fontsize',12)
%预测误差
error=an-outputn_test;

% 
% figure(2)
% plot(error,'-*')
% title('BP网络预测误差','fontsize',12)
% ylabel('误差','fontsize',12)
% xlabel('样本','fontsize',12)
% 
% figure(3)
% plot((output_test-BPoutput)./BPoutput,'-*');
% title('神经网络预测误差百分比')
% 
% errorsum=sum(abs(error));


%%
% <html>
% <table width="656" align="left" >	<tr><td align="center"><p><font size="2"><a href="http://video.ourmatlab.com/">Matlab神经网络30个案例分析</a></font></p><p align="left"><font size="2">相关论坛：</font></p><p align="left"><font size="2">《Matlab神经网络30个案例分析》官方网站：<a href="http://video.ourmatlab.com">video.ourmatlab.com</a></font></p><p align="left"><font size="2">Matlab技术论坛：<a href="http://www.matlabsky.com">www.matlabsky.com</a></font></p><p align="left"><font size="2">M</font><font size="2">atlab函数百科：<a href="http://www.mfun.la">www.mfun.la</a></font></p><p align="left"><font size="2">Matlab中文论坛：<a href="http://www.ilovematlab.com">www.ilovematlab.com</a></font></p></td>	</tr></table>
% </html>