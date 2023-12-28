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
	int depth = 0;//深度
	int dislocation;//不在位数
	int value;//估价值
	int hamilton;//哈密顿距离

public:
	int state[9];
//用于设置私有成员
	void setDepth(int x) { depth = x; }
	void setDislocation(int x) { dislocation = x; }
	void setValue(int x) { value = x; }
	void setHamilton(int x) { hamilton = x; }
//接口函数，用于调用私有成员
	int depth_() { return depth; }
	int dislocation_() { return dislocation; }
	int value_() { return value; }
	int hamilton_() { return hamilton; }
//按照估价值小的方案构造优先级队列，若估价值相等，则按照不在位数小构造
	friend bool operator < (Node A, Node B) {
		if (A.value == B.value) return A.dislocation > B.dislocation;
		return A.value > B.value;
	}
//重载==运算符，定义结点相等为每位都相等
	bool operator == (Node A) {
		for (int i = 0; i < num - 1; i++) {
			if (state[i] != A.state[i])  return false;
		}
		return true;
	}
//计算不在位数	
	int cal_Dislocation(Node A) {
		int d = 8;
		for (int i = 0; i < num; i++) {
			if (state[i] == A.state[i] && A.state[i] != 0)  d--;
		}
		return d;
		//return 0;
	}
//利用不在位数计算估价值	
	int cal_value(Node T) {
		int n = 8;
		for (int i = 0; i < num; i++) {
			if (state[i] == T.state[i] && T.state[i] != 0)  n--;
		}
		return n + depth;
		//return n;
	}
//计算哈密顿距离
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
//利用哈密顿距离计算估价值
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

priority_queue<Node> open;//open表，存放带扩展节点；优先队列priority_queue，可自动对加入的对象排序
vector<Node> close;//close表，存放已扩展节点

//逆序数奇偶性检查
int check_nixu(Node& Ini, Node& Tar) {
//计算始末状态的逆序数
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
//输出始末状态逆序数
	if (nixu_i % 2 == 1) cout << "起始状态逆序数为 " << nixu_i << " 为奇" << endl;
	if (nixu_i % 2 == 0) cout << "起始状态逆序数为 " << nixu_i << " 为偶" << endl;
	if (nixu_i % 2 == 1) cout << "目标状态逆序数为 " << nixu_t << " 为奇" << endl;
	if (nixu_i % 2 == 0) cout << "目标状态逆序数为 " << nixu_t << " 为偶" << endl;

//判断逆序数奇偶性是否相同，相同才有解
	if (nixu_i % 2 != nixu_t % 2){
		return 0;
	}
	return 1;
}
//输入格式检查
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


//用于判断两结点是否相同
int judge(Node A, Node B)
{
	for (int i = 0; i <= 8; i++){
		if (A.state[i] != B.state[i]){
			return 0;
		}
	}
	return 1;
}

//产生新节点，加入OPEN表
void creatNode(Node& A, Node B)
{
	//确定空格位置后，上下左右换位形成子节点，排除超出范围的换位操作
	int blank; 
	for (blank = 0; blank < 9 && A.state[blank] != 0; blank++);//确定空格在一维数组中的序号

	int x = blank / 3, y = blank % 3; //空格对应到3*3网格中的坐标


	for (int d = 0; d <= 3; d++) 
	{
		int new_x = x, new_y = y;
		int flag = 0;
		Node temp;
		//分别朝四个方向移动空格
		if (d == 0)  new_x = x - 1;
		if (d == 1)	 new_y = y - 1;
		if (d == 2)  new_x = x + 1;
		if (d == 3)	 new_y = y + 1;
		//用于记录移动后空格的位置
		int new_blank = new_x * 3 + new_y;

		//若移动过后仍在3*3范围内，继续进行操作
		if (new_x >= 0 && new_x < 3 && new_y >= 0 && new_y < 3){ 
			//temp用于存放新产生的结点
			temp = A;
			temp.state[blank] = A.state[new_blank];
			temp.state[new_blank] = 0;
			//检查新产生的节点是否在close表中
			for (auto it = close.begin(); it != close.end(); ++it) {
				if (*it == temp) { flag=1; continue; }
			}			
			if (flag == 0) {
				//利用不在位数计算
				//temp.setDislocation(temp.cal_Dislocation(B));
				//利用哈密顿距离计算
				temp.setHamilton(temp.cal_Hamilton(B));
				temp.setValue(temp.cal_value_1(B));//可选择不同的估价值计算方式，计算新结点的估价值
				temp.setDepth(A.depth_() + 1);//新结点的深度为原节点+
				open.push(temp);//新结点进入open表
			}
		}
	}
}

int main(){
	Node Ini, Tar;
	cout << "请输入初始状态..."<<endl;
	for (int i = 0; i < num; i++)
		cin >> Ini.state[i];
	cout << "请输入目标状态..."<<endl;
	for (int i = 0; i < num; i++)
		cin >> Tar.state[i];
	cout << "--------------------" << endl;

	if (!check_in(Ini, Tar)) {
		cout << "输入错误！" << endl;
		return 0;
	}
	if (!check_nixu(Ini, Tar)){
		cout << "始末状态逆序数奇偶性不同，无解!" << endl;
		return 0;
	}	
	open.push(Ini);//初始结点进入open表
	int max = 20000;//最多循环20000次
	int num_ = 0;
	while (1){
		//将open表中优先级最高的元素尾插入close表中，并在open表中删除该结点
		close.push_back(open.top()); 
		open.pop(); 
		//对比当前状态与目标状态，不相同则拓展当前结点，否则退出循环
		if (!judge(close.back(), Tar)) {
			creatNode(close.back(), Tar);
		}
		else break;
//		cout << max-- << endl;
		if (max == 0) {
			cout << "搜索失败！" << endl;
			break;
		}
	}
	// 打印移动过程
	cout << "至少要移动" << close.size() - 1 << "步!" << endl;//搜索步数为close表中元素个数-1
	for (auto it = close.begin(); it != close.end(); ++it) {
		for (int i = 0; i <= 8; i++) {
			cout << (*it).state[i] << " ";
			if ((i + 1) % 3 == 0)  cout << endl; 
		}
	    //利用不在位数计算	
		/*(*it).setDislocation((*it).cal_Dislocation(Tar));
		cout << "g: 当前深度：" << (*it).depth_() << endl;
		cout << "h: 启发函数：" << (*it).dislocation_() << endl;
		cout << "f=g+h=" << (*it).depth_() + (*it).dislocation_() << endl;
		cout << "\n";*/
		//利用哈密顿距离计算
		(*it).setHamilton((*it).cal_Hamilton(Tar));
		cout << "g: 当前深度：" << (*it).depth_() << endl;
		cout << "h: 启发函数：" << (*it).hamilton_() << endl;
		cout << "f=g+h= " << (*it).depth_() + (*it).hamilton_() << endl;
		cout << "open表长" << open.size() << endl;
		cout << "\n";
	}
	return 0;
	
}
/*测试数据

请输入初始状态
2 8 3 1 6 4 7 0 5
请输入目标状态?
1 2 3 8 0 4 7 6 5
*/

