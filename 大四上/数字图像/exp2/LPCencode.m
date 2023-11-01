function y=LPCencode(x, a)
 %编码器
%LPCencode函数用一维无损预测编码压缩图像x,a为预测系数，如果a默认，则默认a=１，就是前值预测。
error(nargchk(1, 2, nargin));
 if nargin<2
    a=1;
 end
x=double(x);   
[m, n]=size(x);
p=zeros(m, n);  %存放预测值
xs=x;   
zc=zeros(m, 1);
for i=1:length(a)
xs=[zc  xs(:, 1:end-1)];    
p=p+a(i)*xs;
end
y=x-round(p);
end

