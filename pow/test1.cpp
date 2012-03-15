#include <iostream>

using namespace std;

int main() {
	cout << "Pow test 1: calculating powers of given integer" << endl;
	cout << "Number: ";
	int n;
	cin >> n;

	size_t power;
	cout << "Power: ";
	cin >> power;
	
	int result = 1;

	for(size_t i = 0; i < power; i++) {
		result *= n;
	}
	
	cout << "Result: " << result << endl;

	return 0;
}
