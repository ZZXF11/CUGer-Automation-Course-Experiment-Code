%
% Copyright (c) 2015, Yarpiz (www.yarpiz.com)
% All rights reserved. Please read the "license.txt" for license terms.
%
% Project Code: YPML116
% Project Title: FP-Growth Algorithm for Association Rule Mining
% Publisher: Yarpiz (www.yarpiz.com)
% 
% Developer: S. Mostapha Kalami Heris (Member of Yarpiz Team)
% 
% Contact Info: sm.kalami@gmail.com, info@yarpiz.com
%

function S=GetPowerSet(A)

    n=numel(A);
    
    S=cell(2^n,1);
    for i=1:numel(S)
        f=dec2binvec(i-1);
        f=[f zeros(1,n-numel(f))];
        S{i}=A(logical(f));
    end

end