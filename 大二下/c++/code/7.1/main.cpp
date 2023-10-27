//*******************
//’≈”Ó“ª 
//2021.5
//*******************
#include<iostream>
using namespace std;
template<typename T>
T& Swap(T& a, T& b) {
	T c;
	c = a;
	a = b;
	b = c;
	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	return a;
}
int main() {
	double i, j;
	string i1, j1;
	cout << "please input two number" << endl;
	cin >> i >> j;
	Swap(i, j);
	cout << "please input two string" << endl;
	cin >> i1 >> j1;
	Swap(i1, j1);
	return 0;
}
