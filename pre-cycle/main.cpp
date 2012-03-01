#include <iostream>

using namespace std;

template <class T>
class Function {
public:
	Function(T _n) : n(_n) {}
	T operator()(T x) {
		return x*x % n;
	}
private:
	T n;
};

template <class T>
class FunctionWrapper {
public:
	FunctionWrapper(Function<T>& _func) : func(_func) {}
	T operator()(T x) {
		return func(x);
	}
	T operator()(unsigned int pow, T x) {
		return myfunc(pow, x);
	}
private:
	T myfunc(unsigned int pow, T x) {
		T result = 0;
		if(pow > 0) {
			result = myfunc(pow-1, func(x));
		} else if(pow == 0) {
			result = x;
		}
		return result;
	}
	Function<T> func;
};

int main() {
	unsigned int n = 0;
	cout << "Modulus:" << endl;
	cin >> n;
	Function<unsigned int> func(n);
	FunctionWrapper<unsigned int> f(func);

	unsigned int initial = 0;
	cout << "Initial number:" << endl;
	cin >> initial;

	unsigned int in_cycle = f(2*n, initial);

	unsigned int counter = 0;
	unsigned int pointer = in_cycle;
	do {
	pointer = f(pointer);
	counter++;
	} while(pointer != in_cycle);

	unsigned int result = 0;
	unsigned int initial_value = initial;
	unsigned int counter_value = f(counter, initial);
	while(initial_value != counter_value) {
	result++;
	initial_value = f(initial_value);
	counter_value = f(counter_value);
	}

	cout << "Result: " << result << endl;

	return 0;
}
