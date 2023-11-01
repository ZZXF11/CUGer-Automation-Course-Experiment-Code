function x=LPCdecode(y, a)
%解码器
%LPCdecode函数的解码程序，与编码程序用的是同一个预测器
error(nargchk(1, 2, nargin));
if nargin<2
 a=1;
 end
 a=a(end: -1: 1);     
[m, n]=size(y);     
order=length(a);
a=repmat(a, m, 1);      
x=zeros(m, n+order);
for i=1:n
 ii=i+order;
x(:, ii)=y(:, i)+round(sum(a(:, order: -1: 1).*x(:, (ii-1): -1:(ii-order)), 2));
end
x=x(:, order+1: end);
end
