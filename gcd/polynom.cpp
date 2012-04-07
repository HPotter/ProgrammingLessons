#include "polynom.h"
#include <iostream>

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

	for(int i = polynom.pow(); i > 1; i--) {
		if(polynom[i] != 0) {
			if(polynom[i] > 0 && notFirst) {
				result << "+";
			}
			if(polynom[i] != 1) {
				result << polynom[i] << "*";
			}
	
			result << "x^" << i << " ";
		}
		notFirst = true;
	}

	if(polynom.pow() > 0) {
		if(polynom[1] > 0 && notFirst) {
			result << "+";
		}
		if(polynom[1] != 1) {
			result << polynom[1] << "*";
		}
		result << "x ";
	}

	if(polynom[0] > 0) {
		result << "+" << polynom[0];
	} else if(polynom[0] < 0) {
		result << polynom[0];
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

Polynom::Polynom(int _a) {
	a.resize(1, Fraction(_a, 1));
}

Polynom::Polynom(vector<int>& _a) {
	a.resize(_a.size(), 0);

	for(unsigned int i = 0; i < _a.size(); i++) {
		a[i] = _a[i];
	}

	simplify();
}

Polynom::Polynom(const Polynom& _another, unsigned int begin, unsigned int end) {
	a = _another.a;
	for(unsigned int i = 0; i < a.size(); i++) {
		if( (i < begin) || (i > end) ) {
			a[i] = 0;
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
	result.a.resize(max(pow(), _another.pow()) + 1, Fraction(0, 1)); //0 instead of Fraction(0,1) gives really strange results

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

	Polynom tmp;
	if(a[pow()] != _another[_another.pow()]) {
		if(_another[_another.pow()] == 0) {
			return a[pow()] == 0;
		}
		tmp.a[0] = a[pow()] / _another[_another.pow()];
	}
	tmp *= _another;

	for(int i = 0; i < pow(); i++) {
		if(a[i] != tmp.a[i]) {
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
	//cout << "i am divide(...)" << endl;
	pair<Polynom, Polynom> result(Polynom(), *this); //result and remainder
	result.first.simplify();
	result.second.simplify();

	while(result.second.pow() >= _another.pow() && (result.second.pow() != 0 || result.second[0] != 0)) {
		//cout << "result: " << result.first << endl;
		//cout << "reminder: " << result.second << endl;
		//cout << "divider: " << _another << endl;

		Polynom t;
		unsigned int i = result.second.pow() - _another.pow();
		t.a.resize(i + 1, 0);
		t.a[i] = result.second[result.second.pow()] / _another[_another.pow()];
		
		//cout << "multiplier: " << t << endl;
		//cout << "let's decrease on: " << t * _another << endl;
		//cout << endl << endl;

		result.first += t;
		result.second -= t * _another;
	}

	//cout << "Summary:" << endl;
	//cout << "result: " << result.first << endl;
	//cout << "reminder: " << result.second << endl;


	return result;
}

const Fraction& Polynom::operator [] (int i) const {
	return a[i];
}

void Polynom::simplify() {
	while(a.back() == 0 && a.size() > 1) {
		a.pop_back();
	}
}

