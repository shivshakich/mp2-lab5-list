#pragma once

#include <iostream>
#include "theadring.h"

using std::ostream;
using std::istream;
using std::string;

// monom: coeff * x^indx * y^indy * z*indz; index = indx * 100 + indy * 10 + indz
struct TMonom {
	double coeff;
	int indX = 0, indY = 0, indZ = 0;
};

// ������� �� ��� ����������: x, y, z (double ����������� � int �������); � ������������� �� ������� ����������
class TPolynom : public THeadRing<TMonom> {
private:
	const int MINDEGREE = 0;				// ���. ������� ��������� ���������� ������
	const int MAXDEGREE = 99;				// ����. ������� ��������� ���������� ������
	//const string VALIDCHARACTERS = " 0123456789+-*xyzXYZ.^";
public:
	TPolynom();
	TPolynom(double _coeff, int _x = 0, int _y = 0, int _z = 0);
	TPolynom(const TMonom& _monom);
	TPolynom(TPolynom& _polynom);
	TPolynom(const string& _str);
	~TPolynom();

	TPolynom& operator=(const TMonom& _monom);
	TPolynom& operator=(TPolynom& _polynom);
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
	TPolynom& operator-=(TPolynom&);
	TPolynom& operator*=(TPolynom&);
	TPolynom operator+(TPolynom&);
	TPolynom operator-(TPolynom&);
	TPolynom operator*(TPolynom&);

	bool operator==(TPolynom& _polynom);
	bool operator!=(TPolynom& _polynom);

	string ToString();

	friend ostream& operator<<(ostream& os, TPolynom& _polynom);
	friend istream& operator>>(istream& is, TPolynom& _polynom);
};