#include"Person.h"

int main() {
	Person Wang(100000);
	Wang.addInvest(Saving(50000));
	Wang.addInvest(Fund(20000));
	cout << Wang.settle() << endl;
}