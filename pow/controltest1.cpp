#include "pow.h"

class IntegerMultiplier {
public:
	IntegerMultiplier() {}
	int operator()(const int a, const int b) const {
		return a * b;
	}
	int unity() const {
		return 1;
	}
};

using namespace std;

int main() {
	cout << "Pow test 1: calculating powers of given integer" << endl;
	cout << "Number: ";
	int n;
	cin >> n;

	size_t power;
	cout << "Power: ";
	cin >> power;
	
	IntegerMultiplier f;

	cout << "Result: " << pow(n, power, f) << endl;

	return 0;
}
