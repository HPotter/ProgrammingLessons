#ifndef __POLYNOM_H
#define __POLYNOM_H
#include <vector>
#include <utility>
#include <ostream>
#include "fraction.h"

using namespace std;

class Polynom {
public:
	Polynom();
	Polynom(const Polynom& _another);
	Polynom(vector<int>& _a);
	Polynom(int a);
	int pow() const;
	Polynom& operator = (const Polynom& _another);
	Polynom operator + (const Polynom& _another) const;
	Polynom& operator += (const Polynom& _another);
	Polynom operator - (const Polynom& _another) const;
	Polynom& operator -= (const Polynom& _another);
	Polynom operator * (const Polynom& _another) const;
	Polynom& operator *= (const Polynom& _another);
	Polynom operator / (const Polynom& _another) const;
	Polynom& operator /= (const Polynom& _another);
	Polynom operator % (const Polynom& _another) const;
	Polynom& operator %= (const Polynom& _another);
	bool operator == (const Polynom& _another) const;
	bool operator != (const Polynom& _another) const;
	bool operator > (const Polynom& _another) const;
	bool operator < (const Polynom& _another) const;
	bool operator >= (const Polynom& _another) const;
	bool operator <= (const Polynom& _another) const;
	const Fraction& operator [] (int i) const;
private:
	vector<Fraction> a;
	pair<Polynom, Polynom> divide(const Polynom& _another) const;
	Polynom(const Polynom& _another, unsigned int begin, unsigned int end);
	void simplify();
};

//template<>
std::ostream& operator<< (std::ostream& result, const Polynom& polynom);

#endif
