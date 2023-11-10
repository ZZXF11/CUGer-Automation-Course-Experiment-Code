function [MAE] = claMAE(pre,true)
%用于计算MAE
MAEE = 0;
for i = 1:size(pre,1)
    MAEE = abs(pre(i)-true(i))+MAEE;
end
MAE = MAEE/size(pre,1);
end

