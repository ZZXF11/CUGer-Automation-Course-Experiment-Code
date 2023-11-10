function [output] = addoz(M)
    num=length(M);
     sum=0;
     for i = 1:num
        if(M(i)>0) 
           sum =sum+M(i);
        end
     end
     output=sum;
end

