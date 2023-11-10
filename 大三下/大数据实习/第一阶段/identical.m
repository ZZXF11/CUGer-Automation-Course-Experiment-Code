function b = identical(A,B)
	b= (numel(A)==numel(B) && all(sort(A)==sort(B)) ); %若A和B完全相同，则返回1
%sort(A)按升序对 A 的元素进行排序，all(sort(A)==sort(B))把A和B排序后对比，
%当所有元素为非零时，all(A) 返回逻辑 1。
end

