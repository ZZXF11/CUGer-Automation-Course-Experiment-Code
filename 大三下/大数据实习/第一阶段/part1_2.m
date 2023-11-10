%% 第一题
M=[1,7,4;
    8,5,3;
    6,2,1];
CL=det(M);     %求矩阵行列式行列式
rank=rank(M);      %矩阵的秩
trace=trace(M);        %矩阵的迹
norm1=norm(M,1);       %求1范数
norm2=norm(M,2);      %求2范数
normW=norm(M,inf);    %求无穷范数
%% 第二题
M = [0,3,0;
    1,2,3;
    5,6,2]
output = addoz(M)

%% 第三题
data=[];%将输入的数据存放入data
in=input('请输入需要求和的数字，以0结束:');%请输入需要求和的数字，以0结束
while (isempty(in)||in~=0)%空数据或者数据不为0进入循环，数据为0跳出循环
    data=[data in];%在原来的数据末端加入新的数据
    in=input('请输入需要求和的数字，以0结束:');%请输入需要求和的数字，以0结束:
end
mean(data)%求数据的平均值
sum(data)%求数据的和

%% 第四题
A=[12 34 -4;34 7 87;3 65 7];
B=[1 3 -1;2 0 3;3 -2 7];
AmB=A*B %矩阵乘法
AdotB=A.*B;%A和B的点乘
A3=A^3 %矩阵求幂
Adot3=A.^3 %A的每个元素单独求3次方
AZB=A/B%存在解的情况下 求x*A = B 的解 
AFB=A\B %存在解的情况下 求A*x = B 的解
AB=[A,B] %把矩阵A和B横向拼接
A13B2=[A([1,3],:);B^2]%矩阵A的第1行和第3行，与矩阵B的平方，竖向拼接

%% 第五题
x1=-pi/2:0.01:pi/2;
y1=sqrt(cos(x1));

x2=-2:0.01:2;
y2=-4:0.01:4;
[X2,Y2]=meshgrid(x2,y2);
Z1=X2.^2/(2^2)+Y2.^2/(4^2);

x3=-3:0.01:3;
y3=-3:0.01:3;
[X3,Y3]=meshgrid(x3,y3);
Z2=X3.^2+Y3.^2;

a=unifrnd(0.5, 4.5)
t=linspace(0,2*pi,1000);
x4=a*cos(t);
y4=(sqrt(25)-a)*sin(t);
figure(1)
subplot(2,2,1);
plot(x1,y1);
title('√cos(x)')
subplot(2,2,2);
mesh(X2,Y2,Z1);
title('f(x,y)=x^2/(2^2)+y^2/(4^2)')
subplot(2,2,3);
mesh(X3,Y3,Z2);
title('z=x^2+y^2')
subplot(2,2,4);
plot(x4,y4);
title('x^2/(a^2)+y^2/(25-a^2)=1')

figure(2)
subplot(1,3,1);
mesh(X2,Y2,Z1);
title('f(x,y)=x^2/(2^2)+y^2/(4^2)')
subplot(1,3,2);
meshc(X2,Y2,Z1);
title('f(x,y)=x^2/(2^2)+y^2/(4^2)')
subplot(1,3,3);
meshz(X2,Y2,Z1);
title('f(x,y)=x^2/(2^2)+y^2/(4^2)')
