#include "polynom.h"
#include <ostream>

int max(int a, int b) {
	if(a > b) {
		return a;
	} else {
		return b;
	}
}

//template<>
std::ostream& operator<< (std::ostream& result, const Polynom& polynom) {
	bool notFirst = false;
	for(int i = polynom.pow(); i >= 0; i--) {
		if(polynom[i] != Fraction(0, 1)) {
			if(polynom[i] > Fraction(0, 1) && notFirst) {
				result << "+";
			}
			if(polynom[i] != Fraction(1, 1)) {
				result << polynom[i] << "*";
			}
	
			result << "x^" << i << " ";
		}
		notFirst = true;
	}

	return result;
}

Polynom::Polynom(const Polynom& _another) {
	a = _another.a;

	simplify();
}

Polynom::Polynom() {
	a.resize(1, Fraction(0, 1));
}

Polynom::Polynom(vector<int>& _a) {
	a.resize(_a.size(), Fraction(0, 1));

	for(unsigned int i = 0; i < _a.size(); i++) {
		a[i] = Fraction(_a[i], 1);
	}

	simplify();
}

Polynom::Polynom(const Polynom& _another, unsigned int begin, unsigned int end) {
	a = _another.a;
	for(unsigned int i = 0; i < a.size(); i++) {
		if( (i < begin) || (i > end) ) {
			a[i] = Fraction(0, 1);
		}
	}

	simplify();
}

int Polynom::pow() const {
	return a.size() - 1;
}

Polynom& Polynom::Polynom::operator = (const Polynom& _another) {
	a = _another.a;

	simplify();

	return *this;
}

Polynom Polynom::operator + (const Polynom& _another) const {
	Polynom result = *this;
	result += _another;

	return result;
}

Polynom& Polynom::operator += (const Polynom& _another) {
	Polynom result;
	result.a.resize(max(pow(), _another.pow()) + 1, Fraction(0, 1));

	for(int i = 0; i <= pow(); i++) {
		result.a[i] += a[i];
	}
	for(int i = 0; i <= _another.pow(); i++) {
		result.a[i] += _another.a[i];
	}

	a = result.a;

	simplify();

	return *this;
}

Polynom Polynom::operator - (const Polynom& _another) const {
	Polynom result = *this;
	result -= _another;

	return result;
}

Polynom& Polynom::operator -= (const Polynom& _another) {
	Polynom result;
	result.a.resize(max(pow(), _another.pow()) + 1, Fraction(0, 1));

	for(int i = 0; i <= pow(); i++) {
		result.a[i] += a[i];
	}
	for(int i = 0; i <= _another.pow(); i++) {
		result.a[i] -= _another.a[i];
	}

	a = result.a;

	simplify();

	return *this;
}

Polynom Polynom::operator * (const Polynom& _another) const {
	Polynom result;
	result.a.resize(pow() + _another.pow() + 1, Fraction(0, 1));
	for(int i = 0; i <= pow(); i++) {
		for(int j = 0; j <= _another.pow(); j++) {
			result.a[i+j] += a[i] * _another.a[j];
		}
	}

	return result;
}

Polynom& Polynom::operator *= (const Polynom& _another) {
	Polynom result;
	result = *this * _another;

	a = result.a;

	simplify();

	return *this;
}

Polynom Polynom::operator / (const Polynom& _another) const {
	return divide(_another).first;
}

Polynom& Polynom::operator /= (const Polynom& _another) {
	Polynom result = divide(_another).first;

	a = result.a;

	simplify();

	return *this;
}

Polynom Polynom::operator % (const Polynom& _another) const {
	return divide(_another).second;
}

Polynom& Polynom::operator %= (const Polynom& _another) {
	Polynom result = divide(_another).second;
	a = result.a;

	return *this;
}

bool Polynom::operator == (const Polynom& _another) const {
	if(pow() != _another.pow()) {
		return false;
	}

	for(int i = 0; i < pow(); i++) {
		if(a[i] != _another.a[i]) {
			return false;
		}
	}

	return true;
}

bool Polynom::operator != (const Polynom& _another) const {
	return ! (*this == _another);
}

bool Polynom::operator > (const Polynom& _another) const {
	return pow() > _another.pow();
}

bool Polynom::operator < (const Polynom& _another) const {
	return pow() < _another.pow();
}

bool Polynom::operator >= (const Polynom& _another) const {
	return pow() >= _another.pow();
}

bool Polynom::operator <= (const Polynom& _another) const {
	return pow() <= _another.pow();
}

pair<Polynom, Polynom> Polynom::divide(const Polynom& _another) const {
	pair<Polynom, Polynom> result(Polynom(), *this); //result and remainder
	result.first.simplify();
	result.second.simplify();

	while(result.second.pow() >= _another.pow()) {
		Polynom t;
		unsigned int i = result.second.pow() - _another.pow();
		t.a.resize(i + 1, Fraction(0, 1));
		t.a[i] = result.second[result.second.pow()] / _another[_another.pow()];

		result.first += t;
		result.second -= t * _another;
	}

	return result;
}

const Fraction& Polynom::operator [] (int i) const {
	return a[i];
}

void Polynom::simplify() {
	while(a.back() == Fraction(0, 1) && a.size() > 1) {
		a.pop_back();
	}
}

