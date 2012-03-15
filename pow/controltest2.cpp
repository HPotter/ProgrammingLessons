#include "matrix/matrix.h"

using namespace std;

int main() {
	cout << "Pow test 2: calculating powers of given integer matrix" << endl;
	cout << "Matrix size: ";
	int x;
	cin >> x;
	cout << "Matrix data:" << endl;
	vector< vector<int> > data(x, vector<int>(x, 0));
	for(int i = 0; i < x; i++) {
		for(int j = 0; j < x; j++) {
			cin >> data[j][i];
		}
	}

	CMatrix<int> matrix(data);
	CMatrix<int> result(x);

	size_t power;
	cout << "Power: ";
	cin >> power;

	for(size_t i = 0; i < power; i++) {
		result *= data;
	}

	cout << "Result:" << endl << result << endl;

	return 0;
}
