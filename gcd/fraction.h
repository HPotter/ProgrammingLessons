#ifndef __FRACTION_H
#define _FRACTION_H
#include <ostream>

class Fraction {
public:
	Fraction(int _numerator, int _denominator);
	Fraction(const Fraction& _another);
	Fraction(const int _another);
	Fraction& operator = (const Fraction& _another);
	Fraction operator + (const Fraction& _another) const;
	Fraction& operator += (const Fraction& _another);
	Fraction operator - (const Fraction& _another) const;
	Fraction& operator -= (const Fraction& _another);
	Fraction operator * (const Fraction& _another) const;
	Fraction& operator *= (const Fraction& _another);
	Fraction operator / (const Fraction& _another) const;
	Fraction& operator /= (const Fraction& _another);
	bool operator == (const Fraction& _another) const;
	bool operator != (const Fraction& _another) const;
	bool operator > (const Fraction& _another) const;
	bool operator < (const Fraction& _another) const;
	bool operator >= (const Fraction& _another) const;
	bool operator <= (const Fraction& _another) const;

	Fraction& operator = (int _another);
	Fraction operator + (int _another) const;
	Fraction& operator += (int _another);
	Fraction operator - (int _another) const;
	Fraction& operator -= (int _another);
	Fraction operator * (int _another) const;
	Fraction& operator *= (int _another);
	Fraction operator / (int _another) const;
	Fraction& operator /= (int _another);
	bool operator == (int _another) const;
	bool operator != (int _another) const;
	bool operator > (int _another) const;
	bool operator < (int _another) const;
	bool operator >= (int _another) const;
	bool operator <= (int _another) const;

	int getNumerator() const;
	int getDenominator() const;
private:
	int numerator;
	int denominator;
	void shorten();
};

//template <>
std::ostream& operator<< (std::ostream& result, const Fraction& fraction);

#endif
