function [RMSE] = claRMSE(pre,true)
%用于计算RMSE
RMSEE = 0;
for i = 1:size(pre,1)
    RMSEE = (pre(i)-true(i))*(pre(i)-true(i))+RMSEE;
end
RMSE = sqrt(RMSEE/size(pre,1));
end

