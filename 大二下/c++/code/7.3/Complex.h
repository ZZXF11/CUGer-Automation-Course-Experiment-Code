
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