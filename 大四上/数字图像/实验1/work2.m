I=imread('51.png');
I=rgb2gray(I);
%imwrite(I,'F:\matlab\shu_zi_tu_xiang_chu_li\Blackpink_gray.jpg');
I=im2double(I);%将图像的数据格式转换为double型的，此时图像的数值范围由原来的[0,255]，变成了[0,1],其实不进行转换的话，也可以进行傅里叶变换，只是傅里叶变换后的图像会有所不同
F=fft2(I);%进行傅里叶变换
F=fftshift(F);%对傅里叶变换后的图像进行象限转换，没有这一步的话，最终输出的结果会不同
F=abs(F);%求傅里叶变换的模，我们都知道傅里叶变换后的结果为复数，包含real实部和imag虚部，而abs就是求复数的模，经过这一步，F的类型由复数的double变成了实数的double
T=log(F+1);%经过前几步之后，我们得到了傅里叶变换的幅值，但是傅里叶变换后的数值范围非常大，maxF = 2.04e+05，minF = 0.009，如果不进行转换的话在图中显示就是图(6)的样子，中间有个小白点
%那为什么要用log(F+1)呢。如图7所示，对(0，1)之间的x值，经过log(X)变换后会变成负数，而log(X+1)则将所有的x值，映射成正数，数值范围也更小一些。

[A,H,V,D]=dwt2(I,'db2');%其中X为输入图像，wname为小波函数名称，例如haar，cA,cH,cV,cD分别为，一次小波变换的近似图像，水平方向细节，竖直方向细节，对角方向细节。
M=figure(1);
subplot(131),imshow(I),title('原图');
subplot(132),imshow(T,[]),title('傅里叶变换');
subplot(133),imshow(uint8(A)),title('小波变换');
% imwrite(M,'F:\matlab\shu_zi_tu_xiang_chu_li\work2_pic.jpg');
%saveas(M,'F:\matlab\shu_zi_tu_xiang_chu_li\work2_pic.jpg');
