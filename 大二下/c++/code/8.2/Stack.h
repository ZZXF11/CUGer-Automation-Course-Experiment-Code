#pragma once
#include"node.h"

template<typename T>
class Stack {
	Node<T>* m_top = nullptr;
public:
	Stack() = default;
	Stack(const Stack&) = delete;
	Stack& operator = (const Stack&) = delete;
	~Stack();
	void clear();
	void push(const T& val);
	void pop();
	bool empty()const { return m_top == nullptr; }
	const T& top() { return m_top->m_data; }
};

template<typename T>
void Stack<T>::push(const T& val) {
	Node<T>* node = new Node<T>(val);
	node->m_next = m_top;
	m_top = node;
}

template<typename T>
void Stack<T>::pop() {
	if (empty())return;
	Node<T>* p = m_top;
	m_top = m_top->m_next;
	delete p;
}

template<typename T>
void Stack<T>::clear() {
	Node<T>* p = nullptr;
	while (m_top != nullptr) {
		p = nullptr;
		m_top = m_top->m_next;
		delete p;
	}
}

template<typename T>
Stack<T>::~Stack() {
	clear();
}