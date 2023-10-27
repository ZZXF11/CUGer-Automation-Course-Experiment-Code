//*******************
//张宇一 
//2021.5
//*******************
#include<complex>
#include<vector>
#include<string>
#include<iostream>
using namespace std;
int o = 0;
class Complex {

private:
	double m_real;
	double m_imag;
public:
	Complex() = default;
	Complex(double real, double imag) :m_real(real), m_imag(imag) {};
	Complex(const Complex& rhs) {
		m_real = rhs.m_real;
		m_imag = rhs.m_imag;
	}
	~Complex() {}
	double real() { return m_real; }
	double imag() { return m_imag; }
	void set(double, double);
	friend ostream& operator<<(ostream& os, const Complex& rhs) {
		os << rhs.m_real << "+" << rhs.m_imag << "i" << endl;
		return os;
	}
	friend Complex operator+(const Complex& one, const Complex& two) {
		Complex z;

		z.m_real = one.m_real + two.m_real;
		z.m_imag = one.m_imag + two.m_imag;
		return z;
	}
	friend Complex operator-(const Complex& one, const Complex& two) {
		Complex x;

		x.m_real = one.m_real - two.m_real;
		x.m_imag = one.m_imag - two.m_imag;
		return x;
	}
	friend Complex operator*(const Complex& one, const Complex& two) {
		Complex c;

		c.m_real = one.m_real * two.m_real;
		c.m_imag = one.m_imag * two.m_imag;
		return c;
	}
	friend Complex operator/(const Complex& one, const Complex& two) {
		Complex v;

		v.m_real = one.m_real / two.m_real;
		v.m_imag = one.m_imag / two.m_imag;
		return v;
	}
	bool operator!=(const Complex& x) {
		if ((m_real != x.m_real) && (m_imag != x.m_imag))return true;
		else return false;
	}
	bool operator==(const Complex& x) {
		if ((m_real == x.m_real) && (m_imag == x.m_imag))return true;
		else return false;
	}
	void operator =(const Complex& two) {
		m_real = two.m_real;
		m_imag = two.m_imag;
	}

};


template<typename T>
class Set {
	vector<T> m_elems;
public:
	Set() = default;
	Set(const vector<T>& elem) :m_elems(elem) {};//构造函数

	int find(T a) {
		for (int i = 0; i <= m_elems.size() - 1; ++i) {
			void* p = &m_elems[i];
			if (a == m_elems[i])cout <<"元素在集合中的地址为："<< " "<<p<<'\n'<<"元素在集合中的位置为:"<<"第"<<i+1<<"位"<<endl;
		}
		return 0;//必须返回一个值
	};
	bool is_elem(T a);//是否为集合元素
	void clear() {m_elems.clear();}//清除集合中所有元素
	void erase(T a);
	int many();//返回集合中元素个数
	void insert(T a);//插入一个新的元素
	void swap(Set<T>& a);//交换集合中的元素
	Set<T> common(const T& s);
	friend ostream& operator<<(ostream& os, const Set& s)
	{
		for (int i = 0; i < s.m_elems.size(); ++i)
			os << s.m_elems[i] << " ";
		return os;
	}
};

template<typename T>
void Set<T>::swap(Set<T>& a) {
	vector<T>b1 = m_elems;
	vector<T>b2 = a.m_elems;
	m_elems.clear();
	a.m_elems.clear();
	for (int i = 0; i <= b1.size() - 1; ++i) {
		a.m_elems.push_back(b1[i]);
	}
	for (int j = 0; j <= b2.size() - 1; ++j) {
		m_elems.push_back(b2[j]);
	}
}
template<typename T>
int Set<T>::many() {
	int p = 0;
	for (int i = 0; i <= m_elems.size() - 1; ++i) {
		++p;
	}
	cout << "集合中元素的个数为： " << p << endl;
	return p;
}

template<typename T>
bool Set<T>::is_elem(T a)//是否为集合元素
{
	bool sign = 0;
	for (int i = 0; i <= m_elems.size() - 1; i++)
	{
		if (m_elems[i] == a)
		{
			sign = 1;
			break;
		}
	}
	return sign;
}

template<typename T>
void Set<T>::insert(T a) {
	m_elems.push_back(a);
}

template<typename T>
void Set<T>::erase(T a) {
	vector<T> b;
	vector<T> c;
	int i = 0;
	int o = 0;
	for (; i <= m_elems.size() - 1; ++i) {
		if (a != m_elems[i]) {
			b.push_back(m_elems[i]);
			++o;
		}
	}
	m_elems = c;
	for (int z = 0; z <= b.size() - 1; ++z) {
		m_elems.push_back(b[z]);
	}
	/*T b;
	for (int i = 0; i <= m_elems.size() - 1; ++i) {
		if (m_elems[i] != a) {
			b.push_back(m_elems[i]);
		}
	}
	m_elems = b;*/
}
template<typename T>
Set<T> Set<T>::common(const T& s) {
	T b;
	bool  sign = 0;
	for (int i = 0; i <= m_elems.size() - 1; ++i)
	{
		T a = m_elems[i];
		for (int j = 0; j <= s.m_elems.size() - 1; ++j) {
			sign = 1;
			break;
		}
		if (sign) {
			b.push_back(a);
		}
	}
	return Set(b);
}