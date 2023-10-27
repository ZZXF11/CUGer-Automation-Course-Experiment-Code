#ifndef PERSON_H
#define PERSON_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;


class Investment {
protected:
	double m_capital;
public:
	Investment(const double s=0) :m_capital(s) {};
	~Investment() = default;
	double capital(const double& s) {
		return m_capital;
	}
	virtual double addin() {
		return 0;
	}
	virtual double settle()const {
		return 0;
	}
};

class Saving :public Investment {
public:
	Saving(double money=0):Investment(money){}
	double settle() const {
		return m_capital * (1 + 1.78 / 100);
	}
	double addin() {
		return m_capital;
	}
};

class Fund :public Investment {
public:
	Fund(double s=0):Investment(s){}
	double settle()const {
		return m_capital * (rand() % 20 + 90) / 100;
	}
	double addin() {
		return m_capital;
	}
};

class Person {
protected:
	double m_principal;
	vector<Investment*> m_investment;
public:
	Person(const double& s):m_principal(s){}
	void addInvest(Investment&& s) {
		m_investment.push_back(&s);
		int i = m_investment.size() - 1;
		m_principal = m_principal - m_investment[i]->addin();
	}
	double settle() {
		double earn = m_principal;
		for (int i = 0; i <= m_investment.size() - 1; ++i) {
			earn = m_investment[i]->settle() + earn;
		}
		return earn;
	}
}; 


#endif // !PERSON_H