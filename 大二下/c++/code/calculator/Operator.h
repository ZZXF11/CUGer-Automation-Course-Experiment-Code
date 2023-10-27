#pragma once
#include"Stack.h"

class Operator {
protected:
	const string m_symbol;
	const int m_numOprand;
	const int m_precedence;
	const int m_num;
public:
	Operator(string c, int numOprd, int pre,int num)
		:m_symbol(c), m_numOprand(numOprd), m_precedence(pre),m_num(num) {};
	string symbol()const { return m_symbol; }
	int numOprand()const { return m_numOprand; }
	int precedence()const { return m_precedence; }
	int num()const { return m_num; }
	virtual double get(double a, double b)const = 0;
	virtual ~Operator(){}
};

class Plus :public Operator {
public:
	Plus():Operator("+", 2, 2, 1){}
	double get(double a, double b)const { return a + b; }
};

class Minus :public Operator {
public:
	Minus() :Operator("-", 2, 2, 1) {}
	double get(double a, double b)const { return a - b; }
};

class Multiply :public Operator {
public:
	Multiply() :Operator("*", 2, 3, 1) {}
	double get(double a, double b)const { return a * b; }
};

class Divide :public Operator {
public:
	Divide() :Operator("/", 2, 3, 1) {}
	double get(double a, double b)const { return a / b; }
};

class Hash :public Operator {
public:
	Hash() :Operator("#", 2, 0, 1) {}
	double get(double a, double b)const { return a; }
};

class Equal :public Operator {
public:
	Equal() :Operator("=", 2, -1, 1) {}
	double get(double a, double b)const { return a; }
};

class Sin :public Operator {
public:
	Sin():Operator("sin", 2, 6, 3){}
	double get(double a, double b)const { return sin(b); }
};

class Cos :public Operator {
public:
	Cos() :Operator("cos", 2, 6, 3) {}
	double get(double a, double b)const { return cos(b); }
};

class Tan :public Operator {
public:
	Tan() :Operator("tan", 2, 6, 3) {}
	double get(double a, double b)const { return tan(b); }
};

class aSin :public Operator {
public:
	aSin() :Operator("asin", 2, 6, 4) {}
	double get(double a, double b)const { return asin(b); }
};

class aCos :public Operator {
public:
	aCos() :Operator("acos", 2, 6, 4) {}
	double get(double a, double b)const { return acos(b); }
};

class aTan :public Operator {
public:
	aTan() :Operator("atan", 2, 6, 4) {}
	double get(double a, double b)const { return atan(b); }
};

class Log :public Operator {
public:
	Log() :Operator("log", 2, 5, 3) {}
	double get(double a, double b)const { return log(b); }
};