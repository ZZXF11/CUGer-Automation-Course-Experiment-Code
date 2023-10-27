//*******************
//张宇一 
//2021.5
//*******************

#include"MyVector.h"
#include"Complex.h"

int main() {
	Complex a(1, 2), b(3,4), c(5, 1),d(1,6);
	MyVector<string> s1 = { "ZZXF","FFXZ","ZYY","QY" };
	MyVector<string> s2;
	MyVector<Complex>s3 = { a,b,c };
	MyVector<Complex>s4;
	cout << s1 << endl;
	cout << s3 << endl;
	s2 = s1;
	s4 = s3;
	cout << s2 << endl;
	cout << s4 << endl;
	cout << '\n';
	cout << "测试size函数" << '\n'<< "s1的长度为" << s1.size() << endl;
	cout << '\n';
	cout << "test []" << endl;
	cout <<"s1的第二个元素是 "<< s1[1] << endl;
	cout << '\n';
	cout << "test push_back" << endl;
	string a1 = "ZZZ";
	s1.push_back(a1);
	s3.push_back(d);
	cout << s1 << endl;
	cout << s3 << endl;
	cout << '\n';
	cout << "test pop_back" << endl;
	s1.pop_back();
	s3.pop_back();
	cout << s1 << endl;
	cout << s3 << endl;
	cout << '\n';
	cout << "test insert" << endl;
	s1.insert(2, a1);
	s3.insert(2, d);
	cout << s1 << endl;
	cout << s3 << endl;
	cout << '\n';
	cout << "test erase" << endl;
	s1.erase(2);
	s3.erase(2);
	cout << s1 << endl;
	cout << s3 << endl;
	cout << '\n';
	cout << "test clear" << endl;
	s1.clear();
	s3.clear();
	cout << s1 << endl;
	cout << s3 << endl;
	cout << '\n';
}