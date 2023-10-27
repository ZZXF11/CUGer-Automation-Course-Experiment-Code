
#include<iostream>
//#include<vector>
#include<string>
#include<complex>
using namespace std; 

template<typename T>
class MyVector {
	T* m_arr;
	int m_N;
public:
	MyVector() { m_N = 0; };
	//MyVector(const T*arr=nullptr);//默认构造
	MyVector(const std::initializer_list<T>& l);
	MyVector(const MyVector& rhs);//复制构造
	~MyVector() { delete[] m_arr; };//析构函数
	MyVector(MyVector&& rhs);//移动构造函数
	MyVector<T>& operator=(const MyVector& rhs);
	MyVector<T>& operator=(MyVector&& rhs);
	T& operator[](size_t i);
	int size();
	void push_back(T& s);
	void at(int s);
	T front();
	T back();
	void pop_back();
	void insert(int a, T s);
	void erase(int a);
	void clear();
	template<typename T>
	friend ostream& operator<<(ostream& os, MyVector<T>& s);

private:
	static int strlen(const T* ptr);
	static void strncpy(T* dest, const T* src, int n);
};

template<typename T>
void MyVector<T>::clear() {
	while (m_N) {
		for (int i = 0; i < m_N; ++i) {
			T* p;
			p = m_arr;
			m_arr = new T[--m_N];
			for (int o = 0; o < m_N; ++o) {
				m_arr[o] = p[o];
			}
			delete[] p;
		}
	}
}

template<typename T>
void MyVector<T>::erase(int a) {
	int i = 0;
	T* p;
	p = m_arr;
	m_arr = new T[--m_N];
	for (; i < a-1; ++i) {
		m_arr[i] = p[i];
	}
	for (; i < m_N; ++i) {
		m_arr[i] = p[i+1];
	}
	delete[] p;
}

template<typename T>
void MyVector<T>::insert(int a,T s) {
	int i = 0;
	T* p;
	p = m_arr;
	m_arr = new T[++m_N];
	for (; i < a - 1; ++i) {
		m_arr[i] = p[i];
	}
	m_arr[i] = s;
	++i;
	for (; i < m_N; ++i) {
		m_arr[i] = p[i - 1];
	}
	delete[] p;
}

template<typename T>
T MyVector<T>::back() {
	return m_arr[m_N - 1];
}

template<typename T>
T MyVector<T>::front(){
	return m_arr[0];
}

template<typename T>
void MyVector<T>::at(int s) {
	if (s < m_N) {
		cout << "第" << s << "个元素是 " << m_arr[s] << endl;
	}
	else {
		cout << "超过数组大小" << endl;
	}
}

template<typename T>
T& MyVector<T>::operator[](size_t i) {
	return m_arr[i];
}

template<typename T>
MyVector<T>::MyVector(const std::initializer_list<T>& l) {
	m_N = l.size();
	m_arr = m_N > 0 ? new T[m_N] : nullptr;
	for (int i = 0; i < m_N; i++) {
		m_arr[i] = *(l.begin() + i);
	}
}

template<typename T>
MyVector<T>::MyVector(const MyVector& rhs) :
	m_N(rhs.m_N), m_arr(m_N > 0 ? new T[m_N] : nullptr) {
	for (int i = 0; i <= m_N - 1; ++i) {
		m_arr[i] = rhs.m_arr[i];
	}
}

template<typename T>
MyVector<T>::MyVector(MyVector&& rhs):m_N(rhs.m_N),m_arr(rhs.m_arr) {
	rhs.m_arr = nullptr;
	rhs.m_N = 0;
}

template<typename T>
void MyVector<T>::strncpy(T* dest, const T* src, int n) {
	for (int i = 0; i < n; ++i) {
		dest[i] = src[i];
	}
}

//template<typename T>
//int MyVector<T>::strlen(const T *ptr) {
//	int i = 0;
//	while (ptr && *ptr++ != '\0')++i;
//	return i;
//}

//template<typename T>
//MyVector<T>::MyVector(const T* arr) :
//	m_N(strlen(arr)), m_arr(m_N > 0 ? new T[m_N]() : nullptr) {
//	strncpy(m_arr, arr, m_N);
//}

template<typename T>
int MyVector<T>::size() {
	return m_N;
}

template<typename T>
void MyVector<T>::pop_back() {
	T* p;
	p = m_arr;
	m_arr = new T[--m_N];
	for (int i = 0; i < m_N; ++i) {
		m_arr[i] = p[i];
	}
	delete[] p;
}

template<typename T>
void MyVector<T>::push_back(T& s) {
	T* p;
	p = m_arr;

	m_arr = new T[++m_N];
	for (int i = 0; i < m_N - 1; ++i) {
		m_arr[i] = p[i];
	}
	m_arr[m_N - 1] = s;
	delete[] p;
}

template<typename T>
ostream& operator<<(ostream& os, MyVector<T>& s) {
	if (s.m_N != 0) {
		for (int i = 0; i < s.m_N; ++i) {
			os << s.m_arr[i];
			os << " ";
		}
	}
	if (s.m_N == 0)os << "集合为空";
	return os;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& rhs) {
	if (this != &rhs) {
		delete[] m_arr;
		m_N = rhs.m_N;
		m_arr = new T[m_N];
		strncpy(m_arr, rhs.m_arr, m_N);
	}
	return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& rhs) {
	if (this != &rhs) {
		delete[] m_arr;
		m_N = rhs.m_N;
		m_arr = rhs.m_arr;
		rhs.m_arr = nullptr;
		rhs.m_N = 0;
	}
	return *this;
}