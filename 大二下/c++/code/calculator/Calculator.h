#pragma once
#include"Operator.h"
#include"OperatorFactory.h"

class Calculator {
private:
	Stack<double>m_num;
	Stack<unique_ptr<Operator>>m_opr;
	void calculate();
	bool isNum(string::const_iterator& c)const {//内联函数 判断是否为数字
		return *c >= '0' && *c <= '9' || *c == '.';
	}
	double readNum(string::const_iterator& it);//读取操作数
public:
	Calculator() { m_opr.push(make_unique<Hash>()); }
	double doIt(const string& exp);
};

double Calculator::readNum(string::const_iterator& it) {
	string t;
	while (isNum(it))
		t += *it++;
	return stod(t);
}

void Calculator::calculate() {
	double a[2] = { 0 };
	for (auto i = 0; i < m_opr.top()->numOprand(); ++i) {
		a[i] = m_num.top();
		m_num.pop();
	}
	m_num.push(m_opr.top()->get(a[1], a[0]));
	m_opr.pop();
}