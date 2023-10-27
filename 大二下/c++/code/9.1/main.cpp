//*******************
//’≈”Ó“ª 
//2021.5
//*******************
#include "shape.h"
int main() {
	{
		Color c(100);
		Point p1(2, 3, c);
		Point p2(p1);
		Point p3;
		}
	{
		Color c(100);
		Point p1(2, 3, c);
		Point p2(p1);
		Point p3;
		Circle c1(p1, 3);
		Circle c2(c1);
		c2 = c1; 
		}
	{
		Point p1(2, 3, Color(100));
		p1.draw();
		}
	return 0;
}