#include "polynom.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

const int MOD = 42;

Polynom random_polynom(int pow) {
	vector<int> v(pow + 1, 0);
	for(int i = 0; i < pow + 1; i++) {
		v[i] = random() % MOD + 1;
	}
	return Polynom(v);
}

bool mod_and_div_random_polynom_test(int pow1, int pow2) {
	Polynom a = random_polynom(pow1);
	Polynom b = random_polynom(pow2);

	Polynom c = a % b;
	Polynom d = a / b;

	Polynom e = (d * b) + c;

	return e == a;
}

int main() {
	const int tests = 20;
	const int pow1 = 3;
	const int pow2 = 2;

	srand(time(0));

	for(int i = 0; i < tests; i++) {
		cout << "Test " << i << " ";
		if(mod_and_div_random_polynom_test(pow1, pow2)) {
			cout << "passed";
		} else {
			cout << "failed";
		}
		cout << endl;
	}

	return 0;
}
