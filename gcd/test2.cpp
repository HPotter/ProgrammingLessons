#include "polynom.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
	std::vector<int> a(3, 0);
	std::vector<int> b(2, 0);
/*
	int size;
	cout << "First polynom's power:" << endl;
	cin >> size;
	a.resize(size, 0);
	cout << "First polynom:" << endl;
	for(int i = 0; i < size; i++) {
		cin >> a[i];
	}
	cout << "Second polynom's power:" << endl;
	cin >> size;
	b.resize(size, 0);
	cout << "Second polynom:" << endl;
	for(int i = 0; i < size; i++) {
		cin >> b[i];
	}
*/
	
	a[0] = 1;
	a[1] = 2;
	a[2] = 1;
	b[0] = 1;
	b[1] = 1;

	Polynom pa(a);
	Polynom pb(b);

	cout << pa << " % " << pb << " = " << pa % pb << endl;
	cout << pa << " / " << pb << " = " << pa / pb << endl;

	return 0;
}
