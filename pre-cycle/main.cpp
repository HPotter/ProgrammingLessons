#include <iostream>

using namespace std;

const unsigned int defaultCardinality = 42;

template <class T>
class Function {
public:
	T operator()(T x) const {
		return x*x;
	}
};

template <int modulus>
class ModulusInteger {
public:
	ModulusInteger(int _value) : value(_value % modulus) {}
	unsigned int operator * (ModulusInteger another) const {
		return value*another.value % modulus;
	}
	void operator = (ModulusInteger another) {
		value = another.value;
	}
	bool operator == (ModulusInteger another) const {
		return value == another.value;
	}
	bool operator != (ModulusInteger another) const {
		return value != another.value;
	}
	unsigned int domainCardinality() const {
		return modulus;
	}
private:
	unsigned int value;
};

template <class T, template <class> class F>
class FunctionWrapper {
public:
	FunctionWrapper(const F<T>& _func) : func(_func) {}
	T operator()(const T& x) const {
		return func(x);
	}
	T operator()(const unsigned int pow, const T& x) const {
		return myfunc(pow, x);
	}
private:
	T myfunc(const unsigned int pow, const T& x) const {
		T result = 0;
		if(pow > 0) {
			result = myfunc(pow-1, func(x));
		} else if(pow == 0) {
			result = x;
		}
		return result;
	}
	F<T> func;
};

template <class T, template <class> class F>
unsigned int preCycleLength(const T& initial, const F<T>& function) {
	FunctionWrapper< T, F > f(function);
	unsigned int cardinality = initial.domainCardinality();
	T inCycle = f(2*cardinality, initial);

	unsigned int cycleLength = 0;
	T pointer = inCycle;
	do {
		pointer = f(pointer);
		cycleLength++;
	} while(pointer != inCycle);

	unsigned int result = 0;
	T leftValue = initial;
	T rightValue = f(cycleLength, initial);
	while(leftValue != rightValue) {
		result++;
		leftValue = f(leftValue);
		rightValue = f(rightValue);
	}

	return result;
}

int main() {
	int init;
	cin >> init;

	const int mod = 6;

	ModulusInteger<mod> initial(init);
	Function< ModulusInteger<mod> > func;

	unsigned int result =  preCycleLength(initial, func);
	cout << "Result: " << result << endl;

	return 0;
}
