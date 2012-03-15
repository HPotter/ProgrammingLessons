#include <iostream>

using namespace std;

template <class T, class B>
T pow(const T& x, size_t n, const B& f) {
	if(n == 0) {
		return f.unity();
	} else if(n % 2 == 1) {
		return f(x, pow(x, n-1, f));
	} else {
		T tmp = pow(x, n/2, f);
		return f(tmp, tmp);
	}
}
/*
int main() {
	int dim;
	cin >> dim;
	CMatrix<int> x(dim);
	size_t n;
	cin >> n;

	x.randomize();

	MatrixMultiplier<int> f(x);

	cout << pow (x, n, f);

	return 0;
}
*/
