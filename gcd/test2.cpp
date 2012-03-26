#include "polynom.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
	std::vector<int> a(4, 1);
	std::vector<int> b(2, 1);

	a[0] = -42;
	a[1] = 0;
	a[2] = -12;
	a[3] = 1;

	b[0] = -3;
	b[1] = 1;

	Polynom pa(a);
	Polynom pb(b);

	cout << pa << endl << pb << endl;
	cout << endl << pa / pb << endl;
	cout << pa % pb << endl;
	//cout << pa + pb << endl;
	//cout << pa - pb << endl;

	return 0;
}
