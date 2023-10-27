#pragma once
#include"Stack.h"

class Calculator {
private:
	Stack<double>m_num;//操作数栈
	Stack<string>m_opr;//运算符栈
	int precedence(const string& it)const;//获取运算符优先级
	int precedencE(const string& t)const;
	double readNum(string::const_iterator& it);//读取操作数
	string readopr(string::const_iterator& it);//读出操作符，并改变it指针指向
	string readoprs(string::const_iterator& it);//只读出操作符，it指针不动
	void calculate();//取出运算符和操作数进行计算
	void calculates();
	bool isopr(string::const_iterator& c)const {
		return *c == '+' || *c == '-' || *c == '*' || *c == '/' || *c == '=' || *c == 'i' || *c == 'n' || *c == 'o' || *c == 'a'
			|| *c == '^' || *c == '%' || *c == 's' || *c == 'c' || *c == 't' || *c == 'q' || *c == 'r' || *c == 'p' || *c == 'i';
	}
	bool isNum(string::const_iterator& c)const {//内联函数 判断是否为数字
		return *c >= '0' && *c <= '9' || *c == '.';
	}
	bool isLet(string::const_iterator& c)const {
		return *c >= 'a' && *c <= 'z';
	}
public:
	Calculator() { m_opr.push("#"); }//运算符栈初始化
	double doIt(const string& exp);//表达式求值
};

string Calculator::readopr(string::const_iterator& it) {
	string t;
	while (isopr(it)) {
		if (*it == '+'||*it=='-' || *it == '*' || *it == '/' || *it == '%' || *it == '^') {
			t += *it++;
			break;
		}
		else if (*it == '=') {
			t = "=";
			/*++it;*/
			break;
		}
		else {
			while (isLet(it)) {
				t += *it++;
			}
		}
	}
	return t;
}

string Calculator::readoprs(string::const_iterator& it) {
	string t;
	int i = 0;
	while (isopr(it)) {
		if (t == "pi") {
			break;
		}
		if (*it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '%' || *it == '^') {
			t += *it++;
			++i;
			break;
		}
		else if (*it == '=') {
			t = "=";
			++it;
			break;
		}
		else {
			while (isLet(it)) {
				t += *it++;
				++i;
			}
		}
	}
	it -= i;

	return t;
}

int Calculator::precedencE(const string& t)const {
	if (t == "=") {
		return 0;
	}
	else if (t == "#") {
		return 1;
	}
	else if (t == "+" || t == "-" || t == "%") {
		return 2;
	}
	else if (t == "*" || t == "/") {
		return 3;
	}
	else if (t == "^") {
		return 4;
	}
	else if (t == "sin") {
		return 5;
	}
	else if (t == "cos") {
		return 5;
	}
	else if (t == "tan") {
		return 5;
	}
	else if (t == "sqrt") {
		return 5;
	}
	else if (t == "(") {
		return 6;
	}
	else if (t == ")") {
		return 6;
	}
}

int Calculator::precedence(const string& it)const {
	if (it == "=") {
		return 0;
	}
	else if (it == "#") {
		return 1;
	}
	else if (it == "+" || it == "-" || it == "%") {
		return 2;
	}
	else if (it == "*" || it == "/") {
		return 3;
	}
	else if (it == "^") {
		return 4;
	}
	else if (it == "sin" ) {
		return 5;
	}
	else if (it == "cos") {
		return 5;
	}
	else if (it == "tan") {
		return 5;
	}
	else if (it == "sqrt") {
		return 5;
	}
	else if (it == "(") {
		return 6;
	}
	else if (it == ")") {
		return 6;
	}
	/*switch (s) {
	case'=':return 0;
	case'#':return 1;
	case'+':case'-':case'%':return 2;
	case'*':case'/':return 3;
	case'^':return 4;
	}*/
}

double Calculator::readNum(string::const_iterator& it) {
	string t;
	while (isNum(it))
		t += *it++;
	return stod(t);
}

//void Calculator::calculates() {
//	double a = m_num.top();
//	m_num.pop();
//	if (m_opr.top() == "sin") {
//		m_num.push(sin(a));
//	}
//	if (m_opr.top() == "cos") {
//		m_num.push(cos(a));
//	}
//	if (m_opr.top() == "tan") {
//		m_num.push(tan(a));
//	}
//	if (m_opr.top() == "sqrt") {
//		m_num.push(sqrt(a));
//	}
//}

void Calculator::calculate() {
	string t = m_opr.top();
	if(t=="+"||t=="-" || t == "*" || t == "/" || t == "%" || t == "^"){
		double b = m_num.top();
		m_num.pop();
		double a = m_num.top();
		m_num.pop();
		if (m_opr.top() == "+") {
			m_num.push(a + b);
		}
		if (m_opr.top() == "-") {
			m_num.push(a - b);
		}
		if (m_opr.top() == "*") {
			m_num.push(a * b);
		}
		if (m_opr.top() == "/") {
			m_num.push(a / b);
		}
		if (m_opr.top() == "%") {
			m_num.push((int)a % (int)b);
		}
		if (m_opr.top() == "^") {
			m_num.push(pow(a, b));
		}
		m_opr.pop();
	}
	else if(t == "sin" || t == "cos" || t == "tan" || t == "sqrt" || t == "="){
		double a = m_num.top();
		m_num.pop();
		if (m_opr.top() == "sin") {
			m_num.push(sin(a));
		}
		if (m_opr.top() == "cos") {
			m_num.push(cos(a));
		}
		if (m_opr.top() == "tan") {
			m_num.push(tan(a));
		}
		if (m_opr.top() == "sqrt") {
			m_num.push(sqrt(a));
		}
		if (m_opr.top() == "=") {
			m_num.push(a);
		}
		m_opr.pop();
	}	
}

double Calculator::doIt(const string& exp) {
	m_num.clear();
	for (auto it = exp.begin(); it != exp.end();) {
		if (isNum(it)) {
			m_num.push(readNum(it));
		}
		else if (*it == '(') {
			m_opr.push("#");
			++it;
		}
		else if (*it == ')') {
			while (m_opr.top() != "#") {
				calculate();
			}
			m_opr.pop();
			++it;
		}
		//else if (*it=='p') {
		//	m_num.push(std::atan(1.0) * 4);
		//	++it;
		//	++it;
		//}
		else {
			
			 opr1 = readoprs(it);
			 if (opr1 == "pi") {
				 m_num.push(std::atan(1.0) * 4);
				 ++it;
				 ++it;
			}
			while (precedence(opr1) <= precedence(m_opr.top())) {
				/*				if (m_opr.top() == "sin" || m_opr.top() == "cos"
									|| m_opr.top() == "tan" || m_opr.top() == "sqrt") {
									calculates();
								}
								else */
				if (m_opr.top() == "#") {
					break;
				}
				calculate();
			}
			if (opr1 != "=") {
				if (opr1 != "pi") {
					readopr(it);
					m_opr.push(opr1);
				/*	++it;*/
				}
			}
			
		}
	}
	return m_num.top();
}