%% 第一题
%读入一幅 RGB 图像，变换为灰度图像和二值图像，并在同一个窗口内分成三个子窗口来分别显示 RGB 图像和灰度图像，注上文字标题。
% 读入RGB图像
figure(1)

init = imread('51.png');
subplot(1,3,1)
imshow(init)
title('原始图像')

%转换为灰度图
gray = rgb2gray(init);
subplot(1,3,2)
imshow(gray)
title('灰度图像')

%二值化图像
thresh = graythresh(gray);     %自动确定二值化阈值
BW = imbinarize(gray,thresh); %对图像二值化
subplot(1,3,3)
imshow(BW)
title('二值化图像')



%% 第三题
%读入一幅 RGB 图像，编写 MATLAB 程序实现下列变换：图像向上、向右平移，并用白色填充空白部分，
%再对其做水平镜像，然后旋转 45 度，再缩小 4 倍。
%最后，在同一个窗口内分成两个子窗口来分别显示原图像和经历复合变换后的图像，注上文字标题。
figure(2)
init2 = imread('51.png');
% se = translate(strel(1), [-250 250]);%将一个平面结构化元素分别向下和向右移动30个位置
% J = imdilate(init2,se);%利用膨胀函数平移图像
J = move(init2,-500,500);

J = mirror(J,0);
J = imrotate(J,45);
aa = 0.25;
J = imresize(J,aa,'nearest');

figure(2)

subplot(1,2,1)
imshow(init2)
title('原始图像')

subplot(1,2,2)
imshow(J)
title('复合变换后的图像');



%% 第五题
%读入一幅 RGB 图像，编写 MATLAB 程序实现下列要求：
%采用三种不同算子对图像进行锐化处理，在同一窗口输出图像；使用同态滤波器实现图像增强，输出图像。
figure(3)
img = imread('51.png');
img = rgb2gray(img);
subplot(2,3,1);
imshow(img);
title('原始图像');
[m,n] = size(img);
T = 20;

%Roberts算子
imgr = zeros(m,n);
for i=2:m-1
    for j=2:n-1
        imgr(i,j)= abs(img(i,j)-img(i+1,j+1)) + abs(img(i+1,j)-img(i,j+1));
        if imgr(i,j)<T
            imgr(i,j) = 0;
        else
            imgr(i,j) = 255;
        end
    end
end
subplot(2,3,2);
imshow(imgr);
title('Roberts算子图像');

%Laplace算子
imgl = zeros(m,n);
for i=2:m-1
    for j=2:n-1
        imgl(i,j)= abs(img(i+1,j)+img(i-1,j)+img(i,j+1)+img(i,j-1)-4*img(i,j));
        if imgl(i,j)<T
            imgl(i,j) = 0;
        else
            imgl(i,j) = 255;
        end
    end
end
subplot(2,3,3);
imshow(imgl);
title('Laplace算子图像');

%Sobel算子
imgs = zeros(m,n);
for i=2:m-1
    for j=2:n-1
        imgs(i,j)= abs(img(i-1,j+1)+2*img(i,j+1)+img(i+1,j+1)-img(i-1,j-1)-2*img(i,j-1)-img(i+1,j-1)) + abs(img(i+1,j-1)+2*img(i+1,j)+img(i+1,j+1)-img(i-1,j-1)-2*img(i-1,j)-img(i-1,j+1));
        if imgs(i,j)<T
            imgs(i,j) = 0;
        else
            imgs(i,j) = 255;
        end
    end
end
subplot(2,3,4);
imshow(imgs);
title('Sobel算子图像');

%Prewitt算子
imgp = zeros(m,n);
for i=2:m-1
    for j=2:n-1
        imgp(i,j)= abs(img(i-1,j+1)+img(i,j+1)+img(i+1,j+1)-img(i-1,j-1)-img(i,j-1)-img(i+1,j-1)) + abs(img(i+1,j-1)+img(i+1,j)+img(i+1,j+1)-img(i-1,j-1)-img(i-1,j)-img(i-1,j+1));
        if imgp(i,j)<T
            imgp(i,j) = 0;
        else
            imgp(i,j) = 255;
        end
    end
end
subplot(2,3,5);
imshow(imgp);
title('Prewitt算子图像');

%% 同态滤波

In=imread('51.png');
I=rgb2gray(In);
[H,W]=size(I);
rH=2;
rL=0.2;
C=2;
D0=max(H,W);
J=homomorphicfiltering(I,rH,rL,C,D0);
%figure(4)
% subplot(2,2,1);imshow(I);title('原始图像');
% subplot(2,2,2);imshow(J);title('同态滤波后的图像');
% subplot(2,2,3);imhist(I);title('原始图像直方图');
% subplot(2,2,4);imhist(J);title('同态滤波后的图像直方图');

figure(4)
subplot(1,2,1);imshow(In);title('原始图像');
subplot(1,2,2);imshow(J);title('同态滤波后的图像');

