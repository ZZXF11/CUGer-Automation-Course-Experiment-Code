//*******************
//’≈”Ó“ª 
//2021.5
//*******************
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;
int main() {
	double pi = 3.1415926535;
	cout << showbase << uppercase;
	cout << "octal:" << oct << 300 << endl;
	cout << "decimal:" << dec << 300 << endl;
	cout << "hex:" << hex << 300 << endl;
	cout.precision(7);
	cout << "precision:" << cout.precision() << ",pi=" << pi << endl;
	cout.precision(9);
	cout << "precision:" << cout.precision() << ",pi=" << pi << endl;
	cout << "scientific:" << scientific << pi << endl;
	cout << "fixed decimal:" << fixed << pi << endl;
	ofstream out;
	out.open("result.txt");
	if (!out) {
		ofstream out("result.txt");
	}
	if (out) {
		out << showbase << uppercase;
		out << "octal:" << oct << 300 << endl;
		out << "decimal:" << dec << 300 << endl;
		out << "hex:" << hex << 300 << endl;
		out.precision(7);
		out << "precision:" << cout.precision() << ",pi=" << pi << endl;
		out.precision(9);
		out << "precision:" << cout.precision() << ",pi=" << pi << endl;
		out << "scientific:" << scientific << pi << endl;
		out << "fixed decimal:" << fixed << pi << endl;
	}
	out.close();
	ifstream in("result.txt");
	if (in) {
		string s;
		while (1) {
			getline(in, s);
			if (!in.eof()) {
				cout << s << endl;
			}
			else {
				break;
			}
		}
	}
	in.close();
	return 0;
}