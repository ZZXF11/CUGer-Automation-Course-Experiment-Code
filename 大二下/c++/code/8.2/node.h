#pragma once
#include<iostream>
#include<string>
#include<complex>
#include<math.h>
using namespace std;

static string opr1;
template<typename T> class Stack;

template<typename T>
class Node {
	friend class Stack<T>;
	T m_data;
	Node* m_next = nullptr;
public:
	Node(const T& val):m_data(val){ }
	const T& data()const { return m_data; }
	T& data() { return m_data; }
	Node* next() { return m_next; }
};
