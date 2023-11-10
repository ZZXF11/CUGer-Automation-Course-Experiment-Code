function [error,BPoutput]=BP_error(input_train,output_train,input_test,output_test) 
%���룺1.input_train:ѵ�������������� 2.output_train��ѵ������������� 3.���Լ����������� 4.���Լ�����������
%�����1.error��Ԥ���� 2.BPoutput��Ԥ����

%�ҳ�ѵ�����ݺ�Ԥ������
% input_train=input(n(1:1900),:)';
% output_train=output(n(1:1900));
% input_test=input(n(1901:2000),:)';
% output_test=output(n(1901:2000));

input_train=input_train';
input_test=input_test';
output_train=output_train';
output_test=output_test';
%ѡ����������������ݹ�һ��
[inputn,inputps]=mapminmax(input_train,0,1);
[outputn,outputps]=mapminmax(output_train,0,1);

%% BP����ѵ��
% %��ʼ������ṹ
net=newff(inputn,outputn,30);

net.trainParam.epochs=1000;
net.trainParam.lr=0.01;
net.trainParam.goal=0.00004;

%����ѵ��
net=train(net,inputn,outputn);

%% BP����Ԥ��
%Ԥ�����ݹ�һ��
% inputn_test=mapminmax('apply',input_test,inputps);
inputn_test=mapminmax('apply',input_test,inputps);
outputn_test=mapminmax('apply',output_test,outputps);
 
%����Ԥ�����
an=sim(net,inputn_test);
 
%�����������һ��
BPoutput=mapminmax('reverse',an,outputps);

%% �������

% figure(1)
% plot(BPoutput,':og')
% hold on
% plot(output_test,'-*');
% legend('Ԥ�����','�������')
% title('BP����Ԥ�����','fontsize',12)
% ylabel('�������','fontsize',12)
% xlabel('����','fontsize',12)
%Ԥ�����
error=an-outputn_test;

% 
% figure(2)
% plot(error,'-*')
% title('BP����Ԥ�����','fontsize',12)
% ylabel('���','fontsize',12)
% xlabel('����','fontsize',12)
% 
% figure(3)
% plot((output_test-BPoutput)./BPoutput,'-*');
% title('������Ԥ�����ٷֱ�')
% 
% errorsum=sum(abs(error));


%%
% <html>
% <table width="656" align="left" >	<tr><td align="center"><p><font size="2"><a href="http://video.ourmatlab.com/">Matlab������30����������</a></font></p><p align="left"><font size="2">�����̳��</font></p><p align="left"><font size="2">��Matlab������30�������������ٷ���վ��<a href="http://video.ourmatlab.com">video.ourmatlab.com</a></font></p><p align="left"><font size="2">Matlab������̳��<a href="http://www.matlabsky.com">www.matlabsky.com</a></font></p><p align="left"><font size="2">M</font><font size="2">atlab�����ٿƣ�<a href="http://www.mfun.la">www.mfun.la</a></font></p><p align="left"><font size="2">Matlab������̳��<a href="http://www.ilovematlab.com">www.ilovematlab.com</a></font></p></td>	</tr></table>
% </html>