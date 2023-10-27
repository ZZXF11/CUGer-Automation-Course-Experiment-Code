%最小二乘法线性拟合y=ax+b 
x=[20,40,60,80,100,120,140,160,180,200];%自变量 
y=[4.7,13.7,32.3,50.9,69.6,88.2,106.9,125.8,144.4,162.9];%因变量 
xmean=mean(x);%求均值
ymean=mean(y);
sumx2=(x-xmean)*(x-xmean)';
sumxy=(y-ymean)*(x-xmean)';
a=sumxy/sumx2;%解出直线斜率a(即传感器灵敏度) 
b=ymean-a*xmean;%解出直线截距b 
a
b
%非线性误差=最大误差/量程
wucha=abs((a*x+b)-y)
Maxwucha=max(wucha)
FXXWuCha= Maxwucha/max(y)




%作图,先把原始数据点用蓝色"十"字描出来 
figure (1);
plot(x,y,'+');
hold on;
px=linspace(0,200,10000);%(linspace语法(从横坐标负轴起点0画到横坐标正轴终点6，50等分精度)) 
py=a*px+b;
plot(px,py,'r');% 用红色绘制拟合出的直线 
grid on;