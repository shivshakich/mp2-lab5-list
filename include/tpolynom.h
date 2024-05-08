#pragma once

#include "theadring.h"

// monom: coeff * x^indx * y^indy * z*indz
struct TMonom {
	double coeff;
	int indx, indy, indz;
};

// ������� �� ��� ����������: x, y, z (double ����������� � int �������); � ������������� �� ������� ����������
class TPolynom : public THeadRing<TMonom> {
private:
	const int MINDEGREE = 0;				// ���. ������� ��������� ���������� ������
	const int MAXDEGREE = 9;				// ����. ������� ��������� ���������� ������
public:
	TPolynom(double _coeff, int _x = 0, int _y = 0, int _z = 0);
};