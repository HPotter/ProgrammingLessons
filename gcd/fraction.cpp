#include <iostream>
#include "fraction.h"

//template <>
std::ostream& operator<< (std::ostream& result, const Fraction& fraction) {
	if(fraction.getDenominator() != 1) {
		return result << "(" << fraction.getNumerator() << "/" << fraction.getDenominator() << ")";
	} else {
		return result << fraction.getNumerator();
	}
}

int absolute(int a) {
	if(a < 0) {
		return -1*a;
	} else {
		return a;
	}
}

int gcd(int a, int b) {
	if(a < b) {
		return gcd(b, a);
	} else {
		if(b == 0) {
			return a;
		} else {
			return gcd(b, a % b);
		}
	}
}

Fraction::Fraction(int _numerator, int _denominator) : numerator(_numerator), denominator(_denominator) {
	//CHECK FOR denominator == 0 HERE
	shorten();
}

Fraction::Fraction(const Fraction& _another) {
	numerator = _another.numerator;
	denominator = _another.denominator;
}

Fraction& Fraction::operator = (const Fraction& _another) {
	numerator = _another.numerator;
	denominator = _another.denominator;

	return *this;
}

Fraction Fraction::operator + (const Fraction& _another) const {
	Fraction result = *this;
	result += _another;

	return result;
}

Fraction& Fraction::operator += (const Fraction& _another) {
	denominator *= _another.denominator;
	numerator *= _another.denominator;
	numerator += _another.numerator * denominator;

	shorten();

	return *this;
}

Fraction Fraction::operator - (const Fraction& _another) const {
	Fraction result = *this;
	result -= _another;

	return result;
}

Fraction& Fraction::operator -= (const Fraction& _another) {
	denominator *= _another.denominator;
	numerator *= _another.denominator;
	numerator -= _another.numerator * denominator;

	shorten();

	return *this;
}

Fraction Fraction::operator * (const Fraction& _another) const {
	Fraction result = *this;
	result *= _another;

	return result;
}

Fraction& Fraction::operator *= (const Fraction& _another) {
	numerator *= _another.numerator;
	denominator *= _another.denominator;

	shorten();

	return *this;
}

Fraction Fraction::operator / (const Fraction& _another) const {
	Fraction result = *this;
	result /= _another;

	return result;
}

Fraction& Fraction::operator /= (const Fraction& _another) {
	numerator *= _another.denominator;
	denominator *= _another.numerator;

	shorten();

	return *this;
}

bool Fraction::operator == (const Fraction& _another) const {
	return ( numerator == _another.numerator ) && ( denominator == _another.denominator );
}

bool Fraction::operator != (const Fraction& _another) const {
	return ( numerator != _another.numerator ) || ( denominator != _another.denominator );
}

bool Fraction::operator > (const Fraction& _another) const {
	return numerator * _another.denominator > denominator * _another.numerator;
}

bool Fraction::operator < (const Fraction& _another) const {
	return numerator * _another.denominator < denominator * _another.numerator;
}

bool Fraction::operator >= (const Fraction& _another) const {
	return numerator * _another.denominator >= denominator * _another.numerator;
}

bool Fraction::operator <= (const Fraction& _another) const {
	return numerator * _another.denominator <= denominator * _another.numerator;
}

int Fraction::getNumerator() const {
	return numerator;
}

int Fraction::getDenominator() const {
	return denominator;
}

void Fraction::shorten() {
	int divider = gcd(absolute(numerator), absolute(denominator));

	numerator /= divider;
	denominator /= divider;

	if(denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	}
}
