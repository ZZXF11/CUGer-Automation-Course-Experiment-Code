//*******************
//����һ 
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
	cout<<"s1�ĳ����ǣ�"<<s1.size()<<endl;
	cout<<"s1�ĵ�10��Ԫ���ǣ� "<<s1[10]<<endl;
	int o = 53;
	s1.push_back(o);//��ֵ����pushback
	cout << "����pushback" <<'\n'<< s1 << endl;
	s1.push_back(60);//��ֵ����pushback
	cout << "����pushback" << '\n'<< s1 << endl;
	s2.insert(4,55);
	cout << "����insert" << '\n' << s2 << endl;
	s2.erase(30);
	cout <<"����erase" << '\n' << s2 << endl;
	s2.pop_back();
	cout << "����pop_back" << '\n' << s2 << endl;
	s2.sort();
	cout << "����sort" << '\n' << s2 << endl;
	cout << "����33��s2�е�λ��" << '\n' <<
		"33��s2�е�λ��Ϊ��  " << s2.binary_search(33) << endl;
	s2.clear();
	cout <<"����clear" << '\n' << s2 << endl;

}