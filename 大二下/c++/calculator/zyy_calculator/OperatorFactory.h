#ifndef OPERATORFACTORY_H
#define OPERATORFACTORY_H

#include"Operator.h"
#include"dialog.h"

#define REGISTRAR(T, Key)  Factory::RegisterClass<T> reg_##T(Key);
using namespace std;


class Factory{
public:
    template<typename T>
    struct RegisterClass {
        RegisterClass(string opr) {
            Factory::ms_operator.emplace(opr, []{return make_unique<T>();});
        }
    };

    static unique_ptr<Operator> create(string opr) {
        auto it = ms_operator.find(opr);
        if (it != ms_operator.end())
            return it->second();
    }
    static map<string, function<unique_ptr<Operator>()>> ms_operator;// 存储已注册运算符名及对应构建函数指针的map
};


#endif // OPERATORFACTORY_H
