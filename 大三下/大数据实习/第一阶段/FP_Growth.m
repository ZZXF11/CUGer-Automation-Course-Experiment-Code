%% 大数据课程实践 FP-Growth算法的实现
%初始化参数 设置最小支持度计数
tic
% % 初始化 设置参数 读取数据集
% filename = 'data_set.txt';
% 
% % 将文件的每一行以字符串形式存储在cell矩阵中
% fid = fopen(filename);
% lines = textscan(fid,'%s','delimiter','\n');
% lines = lines{1}; % 将cell数组降级
% fclose(fid);
% 
% % 将每一行的cell矩阵转化成数字矩阵，并存储在transactions中
% readdata = cell(size(lines));
% 
% for i = 1:length(lines)
%     line = textscan(lines{i},'%d');
%     readdata{i} = line{1}';
% end
% readdata = data_in;

data_in = {[1,2,5],[2,4],[2,3],[1,2,4],[1,3],[2,3],[1,3],[1,2,3,5],[1,2,3]};%输入数据集
data = data_in'; % 取转置，变成列向量
min_sup = 2; %设置最小支持度计数

Flist=[];
for i=1:numel(data)
	Flist=union(Flist,data{i});
end
Flist=reshape(Flist,1,[]); %将列向量Flist重构为行向量，用[ ]指定单个维度的大小，以便自动计算该维度大小，使变换前后元素数相匹配。

%获取支持度计数
Count=zeros(size(Flist));
for i=1:numel(data)
	Count=Count+ismember(Flist,data{i}); %凡是在T(i)中找得到的元素的计数都+1
end

[~,SortOrder]=sort(Count,'descend');%将事务按支持度计数的降序排列
Flist=Flist(SortOrder);

Flist=Flist(Count(SortOrder) >= min_sup); %删除支持度计数小于min_suo的事务

%% 构建FP树
%初始化FP树
empty_node.Name=[];
empty_node.Count=0;
empty_node.Parent=[];
empty_node.Children=[];
empty_node.Path=[];
empty_node.Patterns={}; %初始化模式
empty_node.PatternCount=[]; %初始化模式计数

% 添加根节点
Node(1)=empty_node;
Node(1).Name='null';
Node(1).Parent=0;%根节点没有父亲节点
LastIndex=1;

for i=1:numel(data)

	A=[];
    for item=Flist %item依次等于Flist中的各个元素（项）
        if ismember(item,data{i})
            A=[A item]; %如果Flist中某个项在事务T(i)中出现了就把它加入A中
        end
    end

	CurrentNode=1; %初始化当前节点
	Node(CurrentNode).Count=Node(CurrentNode).Count+1;

	for a=A

        ChildNodeExists=false;
        for c=Node(CurrentNode).Children
            if Node(c).Name==a
                ChildNodeExists=true;
                break;
            end
        end

        if ChildNodeExists
            CurrentNode=c;

        else
            NewNode=empty_node;
            NewNode.Name=a;
            NewNode.Parent=CurrentNode;
            NewNode.Path=[Node(CurrentNode).Path NewNode.Name];
            LastIndex=LastIndex+1;
            Node(LastIndex)=NewNode;

            Node(CurrentNode).Children=[Node(CurrentNode).Children LastIndex];
            CurrentNode=LastIndex;

        end

        Node(CurrentNode).Count=Node(CurrentNode).Count+1;

        end

end

%% 频繁模式挖掘

for i=2:numel(Node)

% Dedicated Patterns专用模式
	S=GetPowerSet(Node(i).Path(1:end-1))';
	Node(i).Patterns=cell(size(S));
	Node(i).PatternCount=zeros(size(S));
    for j=1:numel(Node(i).Patterns)
        Node(i).Patterns{j}=[S{j} Node(i).Name];
        Node(i).PatternCount(j)=Node(i).Count;
    end
	
	% Trasfer Dedicated Patterns to Parents
	%将专用模式转移给父节点
	k=i;
	while true
 
        p=Node(k).Parent;
        if p==0
            break;
        end
	
        for j=1:numel(Node(i).Patterns)
            Pj=Node(i).Patterns{j};
	
            PatternFound=false;
            for l=1:numel(Node(p).Patterns)
                Pl=Node(p).Patterns{l};
                if IsSame(Pj,Pl)
                    PatternFound=true;
                    break;
                end
            end
	
            if ~PatternFound
                l=numel(Node(p).Patterns)+1;
                Node(p).Patterns{l}=Pj;
                Node(p).PatternCount(l)=0;
            end
	
            Node(p).PatternCount(l)=Node(p).PatternCount(l)+Node(i).PatternCount(j);
        
        end
	
        k=p;

    end

end

Patterns=Node(1).Patterns;
PatternCount=Node(1).PatternCount;

Patterns=Patterns(PatternCount>=min_sup);
PatternCount=PatternCount(PatternCount>=min_sup);

for j=1:size(Patterns,2)
	Patterns{2,j}=PatternCount(j);
end

%% 输出结果
L=Patterns(1,:); %频繁项集L

disp('执行FP-growth算法挖掘结果为：');
k=1;
for i=1:numel(L)
	str_k=num2str(k);
	str=['频繁',str_k,'项集：'];
	disp(str);disp(L{i});
	k=k+1;
end
toc
disp(['FP-Growth运行时间: ',num2str(toc)]);