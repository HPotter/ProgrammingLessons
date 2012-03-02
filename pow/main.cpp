#include <iostream>

using namespace std;

template <class T>
class Function {
public:
	T operator()(T a, T b) {
		return a * b;
	}
};

template <class T, template <class> class B>
T pow(T x, size_t n, B<T> f) {
	
	if(n == 1) {
		return x;
	} else if(n % 2 == 1) {
		return f(x, pow(x, n-1, f));
	} else {
		T tmp = pow(x, n/2, f);
		return f(tmp, tmp);
	}

/*
	if(n == 1) {
		return x;
	} else {
		return f(x, pow(x, n-1, f));
	}
*/
}

int main() {
	int result, x;
	size_t n;
	cin >> x >> n;

	if(n < 1) {
		cout << "Invalid n" << endl;
		return 1;
	}

	Function<int> f;

	cout << pow (x, n, f);

	return 0;
}
