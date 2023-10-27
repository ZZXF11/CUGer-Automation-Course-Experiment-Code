#include "dialog.h"
#include"OperatorFactory.h"
#include"Operator.h"
#include <QApplication>
using namespace std;

map<string, function<unique_ptr<Operator>()>> Factory::ms_operator; // 定义存储ObjectCreator的静态map

// 使用宏对Operator进行注册
REGISTRAR(Plus, "+");
REGISTRAR(Minus, "-");
REGISTRAR(Multiply, "*");
REGISTRAR(Divide, "/");
REGISTRAR(Equal, "=");
REGISTRAR(mode, "%");
REGISTRAR(power, "^");
REGISTRAR(dealsqrt, "sqrt");
REGISTRAR(dealsin, "sin");
REGISTRAR(dealcos, "cos");
REGISTRAR(dealtan, "tan");
REGISTRAR(dealasin, "asin");
REGISTRAR(dealacos, "acos");
REGISTRAR(dealatan, "atan");
REGISTRAR(kleft, "(");
REGISTRAR(kright, ")");
REGISTRAR(negative, "$");
REGISTRAR(bln, "ln");
REGISTRAR(blog, "log");
REGISTRAR(reciprocal, "ds");
REGISTRAR(factorial, "!");
REGISTRAR(dealexp, "em");

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
