#ifndef OPERATOR_H
#define OPERATOR_H

#include"stack.h"
#include"dialog.h"
#include"OperatorFactory.h"

using namespace std;
class Operator {
public:
    Operator(string c, int numOprd, int pre) :m_symbol(c), m_numOprand(numOprd), m_precedence(pre) { }
    string symbol() const { return m_symbol; }
    int numOprand() const { return m_numOprand; }
    int precedence() const { return m_precedence; }
    virtual double get(double a, double b) const = 0;
    virtual ~Operator() {}
protected:
    const string m_symbol; // 运算符符号
    const int m_numOprand;  // 运算符目数
    const int m_precedence;

};

class Plus : public Operator { // 运算符+
public:
    Plus() :Operator("+", 2, 2) {}
    double get(double a, double b) const {
        return a + b;
    }
};

class Minus :public Operator { // 运算符-
public:
    Minus() :Operator("-", 2, 2) {}
    double get(double a, double b) const {
        return a - b;
    }
};

class Multiply :public Operator { // 运算符*
public:
    Multiply() :Operator("*", 2, 3) {}
    double get(double a, double b) const {
        return a*b;
    }
};


class Divide :public Operator { // 运算符/
public:
    Divide() :Operator("/", 2, 3) {}
    double get(double a, double b) const {
        return a / b;
    }
};

class mode :public Operator { // 运算符/
public:
    mode() :Operator("%", 2, 3) {}
    double get(double a, double b) const {
        int c=a/b;
        return a-c*b;
    }
};

class power :public Operator { // 运算符/
public:
    power() :Operator("^", 2, 5) {}
    double get(double a, double b) const {
        return pow(a, b);
    }
};

class dealsqrt :public Operator { // 运算符/
public:
    dealsqrt() :Operator("sqrt", 1, 5) {}
    double get(double a, double b) const {
        return sqrt(b);
    }
};

class dealsin :public Operator { // 运算符/
public:
    dealsin() :Operator("sin", 1, 6) {}
    double get(double a, double b) const {
        return sin(b);
    }
};

class dealcos :public Operator { // 运算符/
public:
    dealcos() :Operator("cos", 1, 6) {}
    double get(double a, double b) const {
        return cos(b);
    }
};

class dealtan :public Operator { // 运算符/
public:
    dealtan() :Operator("tan", 1, 6) {}
    double get(double a, double b) const {
        return tan(b);
    }
};

class dealasin :public Operator { // 运算符/
public:
    dealasin() :Operator("asin", 1, 6) {}
    double get(double a, double b) const {
        return asin(b);
    }
};

class dealacos :public Operator { // 运算符/
public:
    dealacos() :Operator("acos", 1, 6) {}
    double get(double a, double b) const {
        return acos(b);
    }
};

class dealatan :public Operator { // 运算符/
public:
    dealatan() :Operator("atan", 1, 6) {}
    double get(double a, double b) const {
        return atan(b);
    }
};

class kleft :public Operator { // 运算符#
public:
    kleft():Operator("(", 1, 1) {}
    double get(double a, double b) const {
        return  b; // 本身#不需要进行任何运算, 但是仍然需要返回值
    }
};

class kright :public Operator { // 运算符#
public:
    kright():Operator(")", 1, 2) {}
    double get(double a, double b) const {
        return b; // 本身#不需要进行任何运算, 但是仍然需要返回值
    }
};

class negative :public Operator { // 运算符#
public:
    negative():Operator("$", 1, 2) {}
    double get(double a, double b) const {
        return -b; // 本身#不需要进行任何运算, 但是仍然需要返回值
    }
};

class bln :public Operator { // 运算符#
public:
    bln():Operator("ln", 1, 5) {}
    double get(double a, double b) const {
        return log(b); // 本身#不需要进行任何运算, 但是仍然需要返回值
    }
};

class blog :public Operator { // 运算符#
public:
    blog():Operator("log", 1, 5) {}
    double get(double a, double b) const {
        return log10(b); // 本身#不需要进行任何运算, 但是仍然需要返回值
    }
};

class reciprocal :public Operator { // 运算符#
public:
    reciprocal():Operator("1/x", 1, 5) {}
    double get(double a, double b) const {
        return 1/b; // 本身#不需要进行任何运算, 但是仍然需要返回值
    }
};

class factorial :public Operator { // 运算符#
public:
    factorial():Operator("!", 1, 3) {}
    double get(double a, double b) const {
        int result=1;
        for(int i=1;i<=b;i++)
        {
            result*=i;
        }
        return result;
    }
};

class dealexp :public Operator { // 运算符#
public:
    dealexp():Operator("em", 1, 5) {}
    double get(double a, double b) const {
        return exp(b);
    }
};

class Hash :public Operator { // 运算符#
public:
    Hash() :Operator("#", 1, 0) {}
    double get(double a, double b) const {
        return b; // 本身#不需要进行任何运算, 但是仍然需要返回值
    }
};


class Equal :public Operator { //表达式结束符=
public:
    Equal() :Operator("=", 2, -1) {}
    double get(double a, double b) const {
        return a;
    }
};

#endif // OPERATOR_H
