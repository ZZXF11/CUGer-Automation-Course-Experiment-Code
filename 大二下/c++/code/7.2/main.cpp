//*******************
//张宇一 
//2021.5
//*******************
#include "set.h"

int main() {
	vector<char> a({ 'a','b','c','r','w','t' }), b({ 'a','v' });
	vector<string> c = { "ZZXF","FFXZ" };
	vector<int> d = { 123,321,132 }, e = { 456,654,465 };
	Complex one(12,33);
	Complex two(32, 35);
	Complex three(13, 23);
	vector<Complex>g = { one,two,three };
	vector<Complex>z = { three,one,two };
	vector<complex<double>>f = { {1,2},{3,4},{5,6} };
	vector<complex<double>>h = { {2,6},{7,3},{2,5},{9,3} };
	Set<Complex>s7 = g;
	Set<Complex>s9 = z;
	Set<complex<double>>s8 = h;
	Set<string> s1 = c;
	Set<char>s4 = a;
	Set<char>s5 = b;
	Set<int>s2 = d;
	Set<int>s3 = e;
	Set<complex<double>>s6 = f;
	cout << "测试is_elem" << endl;
	if (s1.is_elem("ZZXF")) {
		cout << "ZZXF是集合内元素" << endl;
	};
	if (s1.is_elem("ZZF")) {
		cout << "ZZF是集合内元素" << endl;
	};
	cout << "测试find" << endl;
	s6.find((5, 6));
	s1.find("ZZXF");
	s1.find("FFXZ");
	s7.find(two);


	cout << "test insert" << endl;
	cout << s1 << endl;
	s1.insert("ZF");
	cout << s1 << endl;


	cout << "test erase" << endl;
	cout << s1 << endl;
	s1.erase("ZZXF");
	cout << s1 << endl;


	cout << "测试many" << endl;
	cout << "测试int类" << endl;
	s2.many();//查看集合中元素的个数
	s3.many();
	cout << "测试string类" << endl;
	s1.many();
	cout << "测试Complex类" << endl;
	s7.many();
	cout << s2 << endl;
	cout << s3 << endl;
	s2.swap(s3);//交换
	cout << "s2与s3交换" << endl;
	cout << s2 << endl;
	cout << s3 << endl;

	cout << s8 << endl;
	cout << s6 << endl;
	cout << "s8与s6交换" << endl;
	s8.swap(s6);//交换
	cout << s8 << endl;
	cout << s6 << endl;

	cout << s7 << endl;
	cout << s9 << endl;
	cout << "s7与s9交换" << endl;
	s7.swap(s9);//交换
	cout << s7 << endl;
	cout << s9 << endl;

	cout << "测试clear" << endl;
	s2.clear();
	s3.clear();
	s6.clear();
	s7.clear();
	cout << s2 << endl;
	cout << s3 << endl;

}