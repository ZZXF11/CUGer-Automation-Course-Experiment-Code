function J = mirror(I, a)
[M, N, G] = size(I);
I = im2double(I);
J = ones(M, N, G); 
for i = 1:M
    for j = 1:N
        if(a == 0)%水平镜像            
            J(i, N-j+1, :) = I(i, j, :);
        elseif(a == 1 )%垂直镜像 
            J(M-i+1, j, :) = I(i, j, :);
        elseif(a == 2 )%水平垂直
            J(M-i+1, N-j+1, :) = I(i, j, :);
        end
    end
end
