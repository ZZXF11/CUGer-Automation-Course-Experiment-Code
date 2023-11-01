I=imread('51.png');
[m,n,z]=size(I);
y=0+0.1*randn(m,n);%二维高斯分布矩阵 0是均值 0.1是标准差

%先将其double化，再除以255 便于后面计算
I1=double(I)/255;
%加上噪声
I1=I1+y;
%将像素范围扩大至0--255
I1=I1*255;
%转换为uint8类型
I1=uint8(I1);

I2=imnoise(I,'speckle');%加入乘性噪声

figure(1);
subplot(1,3,1),imshow(I),title('原图');
subplot(1,3,2),imshow(I1),title('加入高斯噪声后');
subplot(1,3,3),imshow(I2),title('加入乘性噪声后');

R_1 = I2(:,:,1);
G_1 = I2(:,:,2);
B_1 = I2(:,:,3);

h=fspecial('average',3);
%fspecial用于产生预定义滤波器
R1_junzhi=uint8(round(filter2(h,R_1)));
G1_junzhi=uint8(round(filter2(h,G_1)));
B1_junzhi=uint8(round(filter2(h,B_1)));
%均值滤波，uin8为变量类型，round为取整，h为滤波参数即均值，h后的变量为要处理的图像
R1_zhongzhi=medfilt2(R_1,[5,5]);
G1_zhongzhi=medfilt2(G_1,[5,5]);
B1_zhongzhi=medfilt2(B_1,[5,5]);
%中值滤波
R1_wiener1=wiener2(R_1,[5,5]);
G1_wiener1=wiener2(G_1,[5,5]);
B1_wiener1=wiener2(B_1,[5,5]);
%第一次维纳滤波
R1_wiener2=wiener2(R_1,[5,5]);
G1_wiener2=wiener2(G_1,[5,5]);
B1_wiener2=wiener2(B_1,[5,5]);
%第二次维纳滤波
H = fspecial('gaussian',[5 5]);
R1_Blurred2 = imfilter(R_1,H);
G1_Blurred2 = imfilter(G_1,H);
B1_Blurred2 = imfilter(B_1,H);
%高斯滤波

RGB_junzhi(:,:,1)=R1_junzhi(:,:,1);
RGB_junzhi(:,:,2)=G1_junzhi(:,:,1);
RGB_junzhi(:,:,3)=B1_junzhi(:,:,1);

RGB_zhongzhi(:,:,1)=R1_zhongzhi(:,:,1);
RGB_zhongzhi(:,:,2)=G1_zhongzhi(:,:,1);
RGB_zhongzhi(:,:,3)=B1_zhongzhi(:,:,1);

RGB_wiener1(:,:,1)=R1_wiener1(:,:,1);
RGB_wiener1(:,:,2)=G1_wiener1(:,:,1);
RGB_wiener1(:,:,3)=B1_wiener1(:,:,1);

RGB_wiener2(:,:,1)=R1_wiener2(:,:,1);
RGB_wiener2(:,:,2)=G1_wiener2(:,:,1);
RGB_wiener2(:,:,3)=B1_wiener2(:,:,1);

RGB_Blurred2(:,:,1)=R1_Blurred2(:,:,1);
RGB_Blurred2(:,:,2)=G1_Blurred2(:,:,1);
RGB_Blurred2(:,:,3)=B1_Blurred2(:,:,1);

figure(2);
subplot(2,3,1);imshow(I);title('原图像');
subplot(2,3,2);imshow(I2);title('加入乘性噪声后');
subplot(2,3,3);imshow(RGB_junzhi);title('均值滤波后');
subplot(2,3,4);imshow(RGB_zhongzhi);title('中值滤波后');
subplot(2,3,5);imshow(RGB_wiener2);title('二次维纳滤波后');
subplot(2,3,6);imshow(RGB_Blurred2);title('高斯滤波后');
%subplot(2,3,6);imshow(RGB_wiener1);title('一次维纳滤波后');


R_2 = I1(:,:,1);
G_2 = I1(:,:,2);
B_2 = I1(:,:,3);

h1=fspecial('average',3);
%fspecial用于产生预定义滤波器
R2_junzhi=uint8(round(filter2(h1,R_2)));
G2_junzhi=uint8(round(filter2(h1,G_2)));
B2_junzhi=uint8(round(filter2(h1,B_2)));
%均值滤波，uin8为变量类型，round为取整，h为滤波参数即均值，h后的变量为要处理的图像
R2_zhongzhi=medfilt2(R_2,[5,5]);
G2_zhongzhi=medfilt2(G_2,[5,5]);
B2_zhongzhi=medfilt2(B_2,[5,5]);
%中值滤波
R2_wiener1=wiener2(R_2,[5,5]);
G2_wiener1=wiener2(G_2,[5,5]);
B2_wiener1=wiener2(B_2,[5,5]);
%第一次维纳滤波
R2_wiener2=wiener2(R_2,[5,5]);
G2_wiener2=wiener2(G_2,[5,5]);
B2_wiener2=wiener2(B_2,[5,5]);
%第二次维纳滤波
H1 = fspecial('gaussian',[5 5]);
R2_Blurred2 = imfilter(R_2,H1);
G2_Blurred2 = imfilter(G_2,H);
B2_Blurred2 = imfilter(B_2,H);
%高斯滤波

RGB1_junzhi(:,:,1)=R2_junzhi(:,:,1);
RGB1_junzhi(:,:,2)=G2_junzhi(:,:,1);
RGB1_junzhi(:,:,3)=B2_junzhi(:,:,1);

RGB1_zhongzhi(:,:,1)=R2_zhongzhi(:,:,1);
RGB1_zhongzhi(:,:,2)=G2_zhongzhi(:,:,1);
RGB1_zhongzhi(:,:,3)=B2_zhongzhi(:,:,1);

RGB1_wiener1(:,:,1)=R2_wiener1(:,:,1);
RGB1_wiener1(:,:,2)=G2_wiener1(:,:,1);
RGB1_wiener1(:,:,3)=B2_wiener1(:,:,1);

RGB1_wiener2(:,:,1)=R2_wiener2(:,:,1);
RGB1_wiener2(:,:,2)=G2_wiener2(:,:,1);
RGB1_wiener2(:,:,3)=B2_wiener2(:,:,1);

RGB1_Blurred2(:,:,1)=R2_Blurred2(:,:,1);
RGB1_Blurred2(:,:,2)=G2_Blurred2(:,:,1);
RGB1_Blurred2(:,:,3)=B2_Blurred2(:,:,1);

figure(3);
subplot(2,3,1);imshow(I);title('原图像');
subplot(2,3,2);imshow(I1);title('加入高斯噪声后');
subplot(2,3,3);imshow(RGB1_junzhi);title('均值滤波后');
subplot(2,3,4);imshow(RGB1_zhongzhi);title('中值滤波后');
subplot(2,3,5);imshow(RGB1_wiener2);title('二次维纳滤波后');
subplot(2,3,6);imshow(RGB1_Blurred2);title('高斯滤波后');
%subplot(2,3,6);imshow(RGB1_wiener1);title('一次维纳滤波后');
