#ifndef SHAPE_H
#define SHAPE_H
#include<iostream>
using namespace std;

struct Color {
	int m_red = 0, m_green = 0, m_blue = 0;
	Color(int r = 0, int g = 0, int b = 0) :m_red(r), m_green(g), m_blue(b) {
		cout << "constructor of Color" << endl;
	}
	Color(const Color & rhs) : m_red(rhs.m_red), m_green(rhs.m_green),
		m_blue(rhs.m_blue) {
		cout << "copy constructor of Color" << endl;
	}
	~Color() {
		cout << "destructor of Color" << endl;
	}
	Color & operator=(const Color & rhs) {
		if (this != &rhs) {
			m_red = rhs.m_red;
			m_green = rhs.m_green;
			m_blue = rhs.m_blue;
		}
		return *this;
	}
};
class Shape {
protected:
	Color m_color;
public:
	Shape(const Color & c = Color()) :m_color(c) {
		cout << "constructor of Shape" << endl;
	}
	Shape(const Shape & rhs) : m_color(rhs.m_color) {
		cout << "copy constructor of Shape" << endl;
	}
	~Shape() {
		cout << "destructor of Shape" << endl;
	}
	Shape & operator=(const Shape & rhs) {
		if (this != &rhs) {
			m_color = rhs.m_color;
		}
		return *this;
	}
};
class Point :public Shape {
protected:
	double m_x = 0, m_y = 0;
public:
	Point(double x = 0, double y = 0, const Color & c = Color()) :Shape(c),
		m_x(x), m_y(y) {
		cout << "constructor of Point" << endl;
	}
	Point(const Point & rhs) : Shape(rhs), m_x(rhs.m_x), m_y(rhs.m_y) {
		cout << "copy constructor of Point" << endl;
	}
	~Point() { cout << "destructor of Point" << endl; }
	Point & operator=(const Point & rhs) {
		if (this != &rhs) {
			Shape::operator=(rhs);
			m_x = rhs.m_x;
			m_y = rhs.m_y;
		}
		return *this;
	}
	void draw() {
		cout << "draw point with color (" << m_color.m_red << "," <<
			m_color.m_green << "," << m_color.m_blue << ")" << endl;
	}
};
class Circle :public Shape {
protected:
	Point m_center;
	double m_radius;
public:
	Circle(const Point & p, double r, const Color & c = Color()) :Shape(c),
		m_center(p), m_radius(r) {
		cout << "constructor of Circle" << endl;
	}
	Circle(const Circle & rhs) : Shape(rhs), m_center(rhs.m_center),
		m_radius(rhs.m_radius) {
		cout << "copy construct of Circle" << endl;
	}
	~Circle() { cout << "destructor of Circle" << endl; }
	Circle & operator=(const Circle & rhs) {
		if (this != &rhs) {
			Shape::operator=(rhs);
			m_center = rhs.m_center;
			m_radius = rhs.m_radius;
		}
		return *this;
	}
};
#endif