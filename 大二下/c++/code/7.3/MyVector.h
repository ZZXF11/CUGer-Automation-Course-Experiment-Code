
#include<iostream>
#include<vector>
#include<string>
#include<complex>
using namespace std;


template<typename T>
struct Less {
	bool operator()(const T& a, const T& b) {
		return a < b;
	}
};


template<typename T,int N>
class MyVector {
	T m_arr[1000];
	int m_N = N;
public:
	MyVector() = default;
	MyVector(const T* s);//带参构造
	MyVector(const MyVector& s);//复制构造
	int& operator[](const int& s) {
		return m_arr[s];
	};
	void pop_back();
	int size();
	void at(int s);//用于输出某个元素
	void clear();
	T front();
	T back();
	void erase(T s);
	void push_back(T& s);//左值
	void push_back(T&& s);//右值
	void insert(int a,T s);
	void swap(int i, int j);
	template<typename F=Less<T>>
	void sort(F f = F());
	int binary_search(const T&, int left = 0, int right = N - 1);
	MyVector& operator=(const MyVector& rhs) {
		for (int i = 0; i <= rhs.m_N - 1; ++i) {
			m_arr[i] = rhs.m_arr[i];
		}
	};
	friend ostream& operator<<(ostream& os, const MyVector& s)
	{
		for (int i = 0; i < s.m_N; ++i)
			os << s.m_arr[i] << " ";
		return os;
	}
};

template<typename T, int N>
int MyVector<T, N>::binary_search(const T& s, int left, int right) {
	while (left <= right) {
		int middle = (left + right) / 2;
		if (m_arr[middle] == s)
			return middle;
		else if (m_arr[middle] > s)
			right = middle - 1;
		else
			left = middle - 1;
	}
	return -1;
}

template<typename T, int N>
void MyVector<T, N>::swap(int i, int j) {
	T t = m_arr[i];
	m_arr[i] = m_arr[j];
	m_arr[j] = t;
}

template<typename T, int N>
void MyVector<T, N>::pop_back() {
	T c[1000];
	T o = m_arr[m_N - 1];
	int z = 0;
	for (int i = 0; i <= m_N - 1; ++i) {
		if (o != m_arr[i]) {
			c[i] = m_arr[i];
			++z;
		}
	}
	T d[1000];
	m_N = 1000;
	m_arr[m_N] = d[1000];
	m_N = z;
	for (int i = 0; i <= m_N - 1; ++i) {
		m_arr[i] = c[i];
	}
}

template<typename T, int N>
template<typename F>
void MyVector<T, N>::sort(F f) {
	for (int i = m_N - 1; i > 0; --i) {
		for (int j = 0; j <= i - 1; ++j) {
			if (f(m_arr[j + 1], m_arr[j])) {
				swap(j, j + 1);
			}
		}
	}
}

template<typename T, int N>
void MyVector<T, N>::erase(T s) {
	T c[1000];
	int o = 0;
	for (int i = 0; i <= m_N - 1; ++i) {
		if (m_arr[i] != s) {
			c[o] = m_arr[i];
			++o;
		}
	}
	int d[1000];
	m_N = 1000;
	m_arr[m_N] = d[1000];
	m_N = o;
	for (int i = 0; i <= m_N - 1; ++i) {
		m_arr[i] = c[i];
	}
}
template<typename T, int N>
void MyVector<T, N>::clear() {
	T c[1000];
	m_N = 1000;
	m_arr[m_N] = c[1000];
}

template<typename T, int N>
void MyVector<T, N>::insert(int a,T s) {
	++m_N;
	T c[1000];
	int i = 0;
	for (; i <= a-2; ++i) {
		c[i] = m_arr[i];
	}
	c[i] = s;
	++i;
	for (; i <= m_N - 1; ++i) {
		c[i] = m_arr[i-1];
	}
	for (int o = 0; o <= m_N - 1; ++o) {
		m_arr[o] = c[o];
	}
}

template<typename T, int N>
void MyVector<T, N>::push_back(T&& s) {
	++m_N;
	int& o = m_arr[m_N - 1];
	o = s;
}
template<typename T, int N>
void MyVector<T, N>::push_back(T& s) {
	++m_N;
	int& o = m_arr[m_N-1];
	o = s;
}

template<typename T, int N>
T MyVector<T, N>::front() {
	return m_arr[0];
}
template<typename T, int N>
T MyVector<T, N>::back() {
	return m_arr[m_N - 1];
}
template<typename T, int N>
void MyVector<T, N>::at(int s) {
	if (s <= m_N) {
		cout << "第" << s << "个元素是： " << m_arr[s] << endl;
	}
	else cout << "超过数组大小" << endl;
}

template<typename T, int N>
int MyVector<T,N>::size() {
	return m_N;
}

template<typename T,int N>//带参构造
MyVector<T, N>::MyVector(const T* s) {
	int i;
	for (i = 0; i <= m_N - 1; ++i) {
		m_arr[i] = s[i];
	}
}
template<typename T, int N>//复制构造
MyVector<T, N>::MyVector(const MyVector& s) {
	int i = 0;
	for (i = 0; i <= s.m_N - 1; ++i) {
		m_arr[i] = s.m_arr[i];
	}
	N = s.m_N;
}