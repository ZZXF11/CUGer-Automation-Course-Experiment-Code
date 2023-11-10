%% 大数据课程实践 Apriori算法的实现
% 前期调试代码使用的手动输入数据集
%data_in = {[1,2,5],[2,4],[2,3],[1,2,4],[1,3],[2,3],[1,3],[1,2,3,5],[1,2,3]};%输入数据集
tic
% 初始化 设置参数 读取数据集
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
%% 初始化 以及得到频繁1项集
data_in = {[1,2,5],[2,4],[2,3],[1,2,4],[1,3],[2,3],[1,3],[1,2,3,5],[1,2,3]};%输入数据集
data = data_in'; % 取转置，变成列向量
min_sup = 2; %设置最小支持度计数

Select_TID=[];

for i=1:numel(data) %获取元胞数组的长度，用于获取项集数目
    Select_TID=union(Select_TID,data{i}); %取并集，获取事务总数
end
Select_TID = Select_TID(:)';
TID_num=numel(Select_TID);

%提取候选1项集-C1
C{1}=cell(1,TID_num); %初始化一个行向量元胞数组
count{1}=zeros(size(C{1})); %用于记录事务出现的次数
for r=1:TID_num
	C{1}{r}=Select_TID(r); %分别将每个事务的名称赋值给C，元胞数组单独给每一位赋值
    for i=1:numel(data) %循环项集数量次
        if all(ismember(C{1}{r},data{i})) %其中，isnumber用来判断第一个参数是否在第二个参数中
            count{1}(r)=count{1}(r)+1; %C{1}{r}的出现次数+1
        end
    end
end
L{1}=C{1}(count{1} >= min_sup); %筛选出C1中sup>min_sup的项集，加入L1


%% 在频繁1项集的基础上生成后续所有项集
num=1;%用于计数
while ~isempty(L{num}) %只要Lk还不为空，就一直循环。
	getL=[];
    for i=1:numel(L{num}) %读取频繁项集的个数
        getL=union(getL,L{num}{i}); %提取出所有的频繁项集
    end
    % 开始生成候选2项集至候选k项集
	C{num+1}={}; %初始化C(num+1)
    for i=1:numel(L{num})
        for j=1:numel(getL)
            if ~ismember(getL(j),L{num}{i}) %找出不在频繁项集里的事务，与频繁项集构成新的项集
                new_c=[L{num}{i} getL(j)];% 构建新的项集
                Found=false; %标记为没找到
                for r=1:numel(C{num+1})
                    %不允许生成的新项集中有与之前重复的项集
                    if numel(new_c)==numel(C{num+1}{r}) && all(sort(new_c)==sort(C{num+1}{r}))
                        Found=true; %标记为找到
                        break;
                    end
                end
                if ~Found %如果没找到
                    C{num+1}=[C{num+1} {new_c}]; %把新项集加入C(num+1)
                end
            end
        end
    end
    % 统计C(k+1)中各个（k+1）项集在T中的支持度计数count
	count{num+1}=zeros(size(C{num+1}));
    for r=1:numel(C{num+1})
        for i=1:numel(data)
            if all(ismember(C{num+1}{r},data{i})) %其中，isnumber用来判断第一个参数是否在第二个参数中
                count{num+1}(r)=count{num+1}(r)+1; %则计数+1
            end
        end
    end

	L{num+1}=C{num+1}(count{num+1}>=min_sup); %生成频繁C{num+1}项集L{num+1}
	
	% 更新计数器num
	num=num+1;
end

%% 输出结果

L=L(1:end-1); 
disp('开始显示Apriori算法挖掘结果：');
num_show=1;
for i=1:numel(L)
	for j=1:numel(L{i})
        str_k=num2str(num_show);
        b = L{i}{j};
        str=[ '频繁',str_k,'项集：',b ];
        disp(str);
        disp(L{i}{j});
        num_show=num_show+1;
	end
end
toc

disp(['Apriori运行时间: ',num2str(toc)]);