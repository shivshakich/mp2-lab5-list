#pragma once

#include <iostream>
#include "theadring.h"

using std::ostream;
using std::istream;
using std::string;

// monom: coeff * x^indx * y^indy * z^indz
struct TMonom {
	double coeff = 0.0;
	int indX = 0, indY = 0, indZ = 0;
};

// полином от трёх переменных: x, y, z (double коэффиценты и int степени); с ограничениями на степени переменных
class TPolynom : public THeadRing<TMonom> {
private:
	const int MINDEGREE = 0;				// мин. степень некоторой переменной монома
	const int MAXDEGREE = 99;				// макс. степень некоторой переменной монома
	//const string VALIDCHARACTERS = " 0123456789+-*xyzXYZ.^";
public:
	TPolynom();
	TPolynom(double _coeff, int _x = 0, int _y = 0, int _z = 0);
	TPolynom(const TMonom& _monom);
	TPolynom(TPolynom& _polynom);
	TPolynom(const TPolynom& _polynom);
	TPolynom(TPolynom&& _polynom) noexcept;
	TPolynom(const string& _str);
	//~TPolynom();

	TPolynom& operator=(const TMonom& _monom);
	TPolynom& operator=(TPolynom& _polynom);
	TPolynom& operator=(TPolynom&& _polynom) noexcept;
	TPolynom& operator=(const string& _str);

	TPolynom& operator+=(const TMonom&);
	TPolynom& operator-=(const TMonom&);
	TPolynom& operator*=(const TMonom&);
	TPolynom& operator/=(const TMonom&);
	TPolynom operator+(const TMonom&);
	TPolynom operator-(const TMonom&);
	TPolynom operator*(const TMonom&);
	TPolynom operator/(const TMonom&);

	TPolynom& operator+=(TPolynom&);
	TPolynom& operator+=(TPolynom&&);
	TPolynom& operator-=(TPolynom&);
	TPolynom& operator*=(TPolynom&);
	TPolynom operator+(TPolynom&);
	TPolynom operator-(TPolynom&);
	TPolynom operator*(TPolynom&);

	bool operator==(TPolynom& _polynom);
	bool operator!=(TPolynom& _polynom);

	string ToString();
	friend bool CheckOrder(TPolynom& _pol);

	friend ostream& operator<<(ostream& os, TPolynom& _polynom);
	friend istream& operator>>(istream& is, TPolynom& _polynom);
};