cd 'C:\Users\lenovo\Desktop\数字图像处理\实验二'
clc;clear;
%% 实验一：一阶无损预测编码
% 下面对大小为512*512像素、灰度级为256的标准lena图像进行无损的一阶预测编码，其matlab程序如下：
rgb_image = imread('51.png');%原始图片
gray_image = rgb2gray(rgb_image);%灰度图片     
x=double(gray_image);
y=LPCencode(x);   
xx=LPCdecode(y);
%显示预测误差值
figure(1);
subplot(2,3,1);
imshow(gray_image);
title('原灰度图像');
subplot(2,3,2);
imshow(mat2gray(y));
title('一阶编码预测图像');
% 计算均方差误差，因为是无损编码，那么erms应该为０
subplot(2,3,3);
imshow(mat2gray(xx));
title('解码图像');
e=double(x)-double(xx);
[m, n]=size(e);
erms = sqrt(sum(e(:).^2)/(m*n))    
% 显示原图直方图
subplot(2,3,4);
[h, f] = hist(x(:));    
bar(f, h, 'k');
title('原图直方图');
%显示预测误差的直方图
subplot(2,3,5);
[h, f] = hist(y(:));    
bar(f, h,'k');
title('预测误差的直方图');
subplot(2,3,6);
[h, f] = hist(xx(:));    
bar(f, h,'k');
title('解码图像的直方图');
%% 实验二：开和闭运算
% 要求1：用二阶单位矩阵的结构元素进行开、闭运算
I1 = imnoise(gray_image,'salt & pepper',0.2);
subplot(2,2,1),imshow(gray_image);
title('原始图像');
axis on;                  %显示坐标系
subplot(2,2,2),imshow(I1);
title('噪声图像');
axis on;                  %显示坐标系
se=strel('rectangle',[2 2]);  %采用二阶单位矩阵的结构作为结构元素
I2=imopen(I1,se);         %开启操作
I3=imclose(I1,se);        %闭合操作
subplot(2,2,3),imshow(I2);
title('开启运算后图像');
axis on;                  %显示坐标系
subplot(2,2,4),imshow(I3);
title('闭合运算后图像');
axis on;                  %显示坐标系

% 要求2：用半径为1的平坦圆盘形结构元素进行开、闭运算
figure
subplot(2,2,1),imshow(gray_image);
title('原始图像');
axis on;                  %显示坐标系
subplot(2,2,2),imshow(I1);
title('噪声图像');
axis on;                  %显示坐标系
se=strel('disk',1);  %采用半径为1的平坦圆盘形结构作为结构元素
I2=imopen(I1,se);         %开启操作
I3=imclose(I1,se);        %闭合操作
subplot(2,2,3),imshow(I2);
title('开启运算后图像');
axis on;                  %显示坐标系
subplot(2,2,4),imshow(I3);
title('闭合运算后图像');
axis on;                  %显示坐标系

% 要求3：使用开和闭运算实现形态学滤波
sca = 5;                       % 结构元素尺寸
se=strel('diamond',(sca-1)/2); % 形态学结构元素
Io=imopen(I1,se);              % 开操作
Ioc=imclose(Io,se);            % 闭操作
Iobr=imreconstruct(Io,Ioc);    % 结构重建

Iobrd = imdilate(Iobr,se);   % 膨胀
Iobrcbr = imreconstruct(imcomplement(Iobrd),imcomplement(Iobr)); % 结构重建
Iobrcbr = imcomplement(Iobrcbr);   

% 要求4：显示滤波效果
figure
subplot(121),imshow(I1);title('噪声图像')
subplot(122),imshow(Iobrcbr,[]);title('形态学滤波图像')

%% 实验三：最大信息熵阈值分割
clc;clear;
rgb_image = imread('51.png');
a = rgb_image;
count=imhist(a);
[m,n]=size(a);
N=m*n;
L=256;
count=count/N;%%每一个像素的分布概率

for i=1:L
    if count(i)~=0
        st=i-1;
        break;
    end
end

for i=L:-1:1
    if count(i)~=0
        nd=i-1;
        break;
    end
end

f=count(st+1:nd+1);  %f是每个灰度出现的概率
size(f)
E=[];

for Th=st:nd-1   %%%设定初始分割阈值为Th
    av1=0;
    av2=0;
    Pth=sum(count(1:Th+1));
    %%%第一类的平均相对熵为
    for i=0:Th
        av1=av1-count(i+1)/Pth*log(count(i+1)/Pth+0.00001);
    end
    %%%第二类的平均相对熵为
    for i=Th+1:L-1
        av2=av2-count(i+1)/(1-Pth)*log(count(i+1)/(1-Pth)+0.00001);
    end
    E(Th-st+1)=av1+av2;
end
position=find(E==(max(E)));
th=st+position-1

for i=1:m
    for j=1:n
        if a(i,j)>th
            a(i,j)=255;
        else
            a(i,j)=0;
        end
    end
end

figure
subplot(1,2,1)
imshow(rgb_image);
title('原始图像');
subplot(1,2,2)
imshow(a); 
title('最大信息熵阈值分割图像');
