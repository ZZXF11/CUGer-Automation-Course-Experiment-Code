function J = move(I, a, b)

[M, N, G] = size(I);
I = im2double(I);
J = ones(M + abs(a), N + abs(b), G); %建立新的矩阵，将新图像扩大，避免越过边界

for i = 1:M
    for j = 1:N
        if(a < 0 && b < 0)            
            J(i, j, :) = I(i, j, :);
        elseif(a > 0 && b > 0)
            J(i + a, j + b, :) = I(i, j , :);
        elseif(a < 0 && b > 0)
            J(i, j + b, :) = I(i, j, :);
        else
            J(i + a, j, :) = I(i, j, :);
        end
    end
end
end
