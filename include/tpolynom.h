#pragma once

#include "theadring.h"

// monom: coeff * x^indx * y^indy * z*indz
struct TMonom {
	double coeff;
	int indx, indy, indz;
};

// полином от трёх переменных: x, y, z (double коэффиценты и int степени); с ограничениями на степени переменных
class TPolynom : public THeadRing<TMonom> {
private:
	const int MINDEGREE = 0;				// мин. степень некоторой переменной монома
	const int MAXDEGREE = 9;				// макс. степень некоторой переменной монома
public:
	TPolynom(double _coeff, int _x = 0, int _y = 0, int _z = 0);
};