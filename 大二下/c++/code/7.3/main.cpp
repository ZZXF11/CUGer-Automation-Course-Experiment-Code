//*******************
//张宇一 
//2021.5
//*******************
#include"MyVector.h"
int main() {
	int a[1000], b[1000];
	for (int i = 0; i <= 50; ++i) {
		a[i] = i;
	}
	for (int i=0; i<=50; ++i) {
		b[i] = 50 - i;
	}
	MyVector<int, 50> s1 = a;
	MyVector<int, 50> s2 = b;
	cout << s1 << endl;
	cout << s2 << endl;
	cout<<"s1的长度是："<<s1.size()<<endl;
	cout<<"s1的第10个元素是： "<<s1[10]<<endl;
	int o = 53;
	s1.push_back(o);//左值引用pushback
	cout << "测试pushback" <<'\n'<< s1 << endl;
	s1.push_back(60);//右值引用pushback
	cout << "测试pushback" << '\n'<< s1 << endl;
	s2.insert(4,55);
	cout << "测试insert" << '\n' << s2 << endl;
	s2.erase(30);
	cout <<"测试erase" << '\n' << s2 << endl;
	s2.pop_back();
	cout << "测试pop_back" << '\n' << s2 << endl;
	s2.sort();
	cout << "测试sort" << '\n' << s2 << endl;
	cout << "查找33在s2中的位置" << '\n' <<
		"33在s2中的位置为：  " << s2.binary_search(33) << endl;
	s2.clear();
	cout <<"测试clear" << '\n' << s2 << endl;

}