#pragma once
#include"Operator.h"

#define REGISTRAR(T, Key)  Factory::RegisterClass<T> reg_##T(Key);

class Factory {
public:
	template<typename T>
	struct RegisterClass {
		RegisterClass(char opr) {
			Factory::ms_operator.emplacr(opr, [] {return make_unique<T>(); })
		}
	};
	static unique_ptr<Operator>create(char opr) {
		auto it = ms_operator.find(opr);
		if (it != ms_operator.end()) {
			return it->second();
		}
	}
private:
	static map<char, function<unique_ptr<Operator>()>>ms_operator;
};


