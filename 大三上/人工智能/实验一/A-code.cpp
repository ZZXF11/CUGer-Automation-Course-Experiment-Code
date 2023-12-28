#include<iostream>
#include<cmath>
#include "stdlib.h" 
#include "time.h" 
#include<stack>
#include<queue>
#include<vector>
using namespace std;
#define num 9

class Node {
private:
	int depth = 0;//���
	int dislocation;//����λ��
	int value;//����ֵ
	int hamilton;//���ܶپ���

public:
	int state[9];
//��������˽�г�Ա
	void setDepth(int x) { depth = x; }
	void setDislocation(int x) { dislocation = x; }
	void setValue(int x) { value = x; }
	void setHamilton(int x) { hamilton = x; }
//�ӿں��������ڵ���˽�г�Ա
	int depth_() { return depth; }
	int dislocation_() { return dislocation; }
	int value_() { return value; }
	int hamilton_() { return hamilton; }
//���չ���ֵС�ķ����������ȼ����У�������ֵ��ȣ����ղ���λ��С����
	friend bool operator < (Node A, Node B) {
		if (A.value == B.value) return A.dislocation > B.dislocation;
		return A.value > B.value;
	}
//����==����������������Ϊÿλ�����
	bool operator == (Node A) {
		for (int i = 0; i < num - 1; i++) {
			if (state[i] != A.state[i])  return false;
		}
		return true;
	}
//���㲻��λ��	
	int cal_Dislocation(Node A) {
		int d = 8;
		for (int i = 0; i < num; i++) {
			if (state[i] == A.state[i] && A.state[i] != 0)  d--;
		}
		return d;
		//return 0;
	}
//���ò���λ���������ֵ	
	int cal_value(Node T) {
		int n = 8;
		for (int i = 0; i < num; i++) {
			if (state[i] == T.state[i] && T.state[i] != 0)  n--;
		}
		return n + depth;
		//return n;
	}
//������ܶپ���
	int cal_Hamilton(Node T) {
		int n = 0;
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				if (state[i] == 0) continue;
				else if (state[i] != T.state[j]) continue;
				else n = n + abs((i / 3) - (j / 3)) + abs((i % 3) - (j % 3));
			}
		}
		return n;
		//return 0;
	}
//���ù��ܶپ���������ֵ
	int cal_value_1(Node T) {
		int n = 0;
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				if (state[i] == 0) continue;
				else if (state[i] != T.state[j]) continue;
				else n = n + abs((i / 3) - (j / 3)) + abs((i % 3) - (j % 3));
			}
		}
		return n + depth;
		//return depth;
	}
};

priority_queue<Node> open;//open����Ŵ���չ�ڵ㣻���ȶ���priority_queue�����Զ��Լ���Ķ�������
vector<Node> close;//close���������չ�ڵ�

//��������ż�Լ��
int check_nixu(Node& Ini, Node& Tar) {
//����ʼĩ״̬��������
	int nixu_i = 0, nixu_t = 0;
	for (int i = 0; i <= num - 2; i++) {
		for (int j = i + 1; j < num; j++) {
			if (Ini.state[i] > Ini.state[j] && Ini.state[i] * Ini.state[j] != 0) 
				nixu_i++;	
		}
	}
	for (int i = 0; i <= num - 2; i++) {
		for (int j = i + 1; j < num; j++)
			if (Tar.state[i] > Tar.state[j] && Tar.state[i] * Tar.state[j] != 0)
				nixu_t++;
	}
//���ʼĩ״̬������
	if (nixu_i % 2 == 1) cout << "��ʼ״̬������Ϊ " << nixu_i << " Ϊ��" << endl;
	if (nixu_i % 2 == 0) cout << "��ʼ״̬������Ϊ " << nixu_i << " Ϊż" << endl;
	if (nixu_i % 2 == 1) cout << "Ŀ��״̬������Ϊ " << nixu_t << " Ϊ��" << endl;
	if (nixu_i % 2 == 0) cout << "Ŀ��״̬������Ϊ " << nixu_t << " Ϊż" << endl;

//�ж���������ż���Ƿ���ͬ����ͬ���н�
	if (nixu_i % 2 != nixu_t % 2){
		return 0;
	}
	return 1;
}
//�����ʽ���
int check_in(Node A, Node B) {
	for (int i = 0; i < num; i++) {
		if (A.state[i] >= 0 && A.state[i] <= 8 && B.state[i] >= 0 && B.state[i] <= 8) continue;
		else return 0;
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			if (i == j)continue;
			else if (A.state[i] == A.state[j] || B.state[i] == B.state[j]) return 0;
		}
	}
	return 1;
}


//�����ж�������Ƿ���ͬ
int judge(Node A, Node B)
{
	for (int i = 0; i <= 8; i++){
		if (A.state[i] != B.state[i]){
			return 0;
		}
	}
	return 1;
}

//�����½ڵ㣬����OPEN��
void creatNode(Node& A, Node B)
{
	//ȷ���ո�λ�ú��������һ�λ�γ��ӽڵ㣬�ų�������Χ�Ļ�λ����
	int blank; 
	for (blank = 0; blank < 9 && A.state[blank] != 0; blank++);//ȷ���ո���һά�����е����

	int x = blank / 3, y = blank % 3; //�ո��Ӧ��3*3�����е�����


	for (int d = 0; d <= 3; d++) 
	{
		int new_x = x, new_y = y;
		int flag = 0;
		Node temp;
		//�ֱ��ĸ������ƶ��ո�
		if (d == 0)  new_x = x - 1;
		if (d == 1)	 new_y = y - 1;
		if (d == 2)  new_x = x + 1;
		if (d == 3)	 new_y = y + 1;
		//���ڼ�¼�ƶ���ո��λ��
		int new_blank = new_x * 3 + new_y;

		//���ƶ���������3*3��Χ�ڣ��������в���
		if (new_x >= 0 && new_x < 3 && new_y >= 0 && new_y < 3){ 
			//temp���ڴ���²����Ľ��
			temp = A;
			temp.state[blank] = A.state[new_blank];
			temp.state[new_blank] = 0;
			//����²����Ľڵ��Ƿ���close����
			for (auto it = close.begin(); it != close.end(); ++it) {
				if (*it == temp) { flag=1; continue; }
			}			
			if (flag == 0) {
				//���ò���λ������
				//temp.setDislocation(temp.cal_Dislocation(B));
				//���ù��ܶپ������
				temp.setHamilton(temp.cal_Hamilton(B));
				temp.setValue(temp.cal_value_1(B));//��ѡ��ͬ�Ĺ���ֵ���㷽ʽ�������½��Ĺ���ֵ
				temp.setDepth(A.depth_() + 1);//�½������Ϊԭ�ڵ�+
				open.push(temp);//�½�����open��
			}
		}
	}
}

int main(){
	Node Ini, Tar;
	cout << "�������ʼ״̬..."<<endl;
	for (int i = 0; i < num; i++)
		cin >> Ini.state[i];
	cout << "������Ŀ��״̬..."<<endl;
	for (int i = 0; i < num; i++)
		cin >> Tar.state[i];
	cout << "--------------------" << endl;

	if (!check_in(Ini, Tar)) {
		cout << "�������" << endl;
		return 0;
	}
	if (!check_nixu(Ini, Tar)){
		cout << "ʼĩ״̬��������ż�Բ�ͬ���޽�!" << endl;
		return 0;
	}	
	open.push(Ini);//��ʼ������open��
	int max = 20000;//���ѭ��20000��
	int num_ = 0;
	while (1){
		//��open�������ȼ���ߵ�Ԫ��β����close���У�����open����ɾ���ý��
		close.push_back(open.top()); 
		open.pop(); 
		//�Աȵ�ǰ״̬��Ŀ��״̬������ͬ����չ��ǰ��㣬�����˳�ѭ��
		if (!judge(close.back(), Tar)) {
			creatNode(close.back(), Tar);
		}
		else break;
//		cout << max-- << endl;
		if (max == 0) {
			cout << "����ʧ�ܣ�" << endl;
			break;
		}
	}
	// ��ӡ�ƶ�����
	cout << "����Ҫ�ƶ�" << close.size() - 1 << "��!" << endl;//��������Ϊclose����Ԫ�ظ���-1
	for (auto it = close.begin(); it != close.end(); ++it) {
		for (int i = 0; i <= 8; i++) {
			cout << (*it).state[i] << " ";
			if ((i + 1) % 3 == 0)  cout << endl; 
		}
	    //���ò���λ������	
		/*(*it).setDislocation((*it).cal_Dislocation(Tar));
		cout << "g: ��ǰ��ȣ�" << (*it).depth_() << endl;
		cout << "h: ����������" << (*it).dislocation_() << endl;
		cout << "f=g+h=" << (*it).depth_() + (*it).dislocation_() << endl;
		cout << "\n";*/
		//���ù��ܶپ������
		(*it).setHamilton((*it).cal_Hamilton(Tar));
		cout << "g: ��ǰ��ȣ�" << (*it).depth_() << endl;
		cout << "h: ����������" << (*it).hamilton_() << endl;
		cout << "f=g+h= " << (*it).depth_() + (*it).hamilton_() << endl;
		cout << "open��" << open.size() << endl;
		cout << "\n";
	}
	return 0;
	
}
/*��������

�������ʼ״̬
2 8 3 1 6 4 7 0 5
������Ŀ��״̬?
1 2 3 8 0 4 7 6 5
*/

