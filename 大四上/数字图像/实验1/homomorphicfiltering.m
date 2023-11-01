% 同态滤波器
% ImageIn   -   进行滤波的输入灰度图像(若输入RGB图像需要先利用rgb2gray函数转换成灰度图像)
% High      -   高频增益,取值大于1
% Low       -   低频增益,取值在0和1之间
% C         -   锐化系数
% D0        -   截止频率(越大图像越亮)
% ImageOut  -   滤波后的输出灰度图像
function [ImageOut] = homomorphicfiltering(ImageIn, High, Low, C, D0)
    I = double(ImageIn);        % 将图像类型转换为双精度型,不会改变数据本身便于进行傅里叶变换
    [M,N] = size(ImageIn);      % 返回输入图像行数和列数
    a = floor(M / 2);           % 中心点坐标
    b = floor(N / 2);
    LogImg = log(I + 1);        % 对输入图像取对数
    Log_FFT = fft2(LogImg);    
    D=zeros(M,N);               % 初始化中间变量D和H
    H=zeros(M,N);
    for i = 1 : M 
        for j = 1 : N 
            D(i,j)=sqrt((i - a)^2 + (j - b)^2);                                           %   频率点(i,j)到频率中心的距离
            H(i, j)=(High - Low) * (1 - exp(-C * (D(i,j)^2 / (D0 ^2)))) + Low;            %   同态滤波器函数
        end 
    end
    H = ifftshift(H);                   %   对H做反中心化                             
    Log_FFT = H.* Log_FFT;              %   滤波，矩阵点乘                                                
    Log_FFT = ifft2(Log_FFT);           %   反傅立叶变换 
    ImageOut = real(exp(Log_FFT)-1);    %   取指数 
end

