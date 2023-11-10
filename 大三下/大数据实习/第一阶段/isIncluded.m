function b = isIncluded(A,B)
    Lia = ismember(A,B) ;%如果 A 中某位置的数据能在 B 中找到， 将返回一个在该位置包含逻辑值 1 (true) 的数组。
	b=all(Lia); %矩阵A 的各列的元素全为非零时，all(A) 返回逻辑 1 (true)；当有零元素时，返回逻辑 0 (false)。
end

