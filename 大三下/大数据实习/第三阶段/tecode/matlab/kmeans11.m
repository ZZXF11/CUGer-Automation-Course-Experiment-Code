function [B,CC,sse]=kmeans11(PM,k)
% ��άk-�������㷨
% PM �������� k ������

dim = length(PM(1,:)); % ģʽ����ά��
N = size(PM,1);
% figure();
% subplot(1,2,1);
% for(i=1:N)
%    plot(PM(i,1),PM(i,2), '*r'); % ���ԭʼ�����ݵ�
%    hold on
% end
% xlabel('X');
% ylabel('Y');
% title('����֮ǰ�����ݵ�');

CC = zeros(k,dim); % �������ľ���CC(i,:)��ʼֵΪi����������
D = zeros(N,k); % D(i,j)������i�;�������j�ľ���

C = cell(1,k); %% ������󣬶�Ӧ�����������������ʼ״���£�����i(i<k)����������Ϊ[i],����k����������Ϊ[k,k+1,...N]
for i = 1:k-1
    C{i} = [i];
end
C{k} = k:N;

B = 1:N; % �ϴε����У�����������һ���࣬���ֵΪ1
B(k:N) = k;

for i = 1:k
    CC(i,:) = PM(i,:);%% ��ʼ���������ĵ���ֵ
end

while 1   
    change = 0;%������Ƿ������Ƿ�仯
    % ��ÿһ������i�����㵽k���������ĵľ���
    for i = 1:N
        for j = 1:k
%             D(i,j) = eulerDis( PM(i,:), CC(j,:) );
              D(i,j) = sqrt((PM(i,1) - CC(j,1))^2 + (PM(i,2) - CC(j,2))^2);
        end
        t = find( D(i,:) == min(D(i,:)) ); % i���ڵ�t��
        if B(i) ~= t % �ϴε���i�����ڵ�t��
            change = 1;
            % ��i�ӵ�B(i)����ȥ��
            t1 = C{B(i)};
            t2 = find( t1==i );            
            t1(t2) = t1(1);
            t1 = t1(2:length(t1)); 
            C{B(i)} = t1;

            C{t} = [C{t},i]; % ��i�����t��

            B(i) = t;
        end        
    end

    if change == 0 %�������ޱ仯�������ֹͣ
        break;
    end

    % ���¼���������ľ���CC
    for i = 1:k
        CC(i,:) = 0;
        iclu = C{i};
        for j = 1:length(iclu)
            CC(i,:) = PM( iclu(j),: )+CC(i,:);
        end
        CC(i,:) = CC(i,:)/length(iclu);
    end
end
% 
% subplot(1,2,2);
% plot(CC(:,1),CC(:,2),'o')
% hold on
% for(i=1:N)
%     if(B(1,i)==1)
%         plot(PM(i,1),PM(i,2),'*b'); %������һ����ͼ��
%         hold on
%     elseif(B(1,i)==2)
%         plot(PM(i,1),PM(i,2), '*r'); %�����ڶ�����ͼ��
%      hold on
%      elseif(B(1,i)==3)
%         plot(PM(i,1),PM(i,2),'*g'); %������������ͼ��
%         hold on
%     else
%         plot(PM(i,1),PM(i,2), '*m'); %������������ͼ��
%         hold on
%     end
% end
% xlabel('X');
% ylabel('Y');
% title('����֮������ݵ�');
%       % ��ӡC,CC     
% for i = 1:k    %���ÿһ�����������
%     str=['��' num2str(i) '�������:  ' num2str(C{i})];
%     disp(str);
% end
% %% ������ƽ����
sse=0;
for i=1:length(D(:,1))
    sse=sse+min(D(i,:));
end

end
