#include <string>
#include <exception>
#include "../include/tpolynom.h"

// допустимые символы для написания полинома
static const string VALIDCHARACTERS = "*^.-+0123456789xXyYzZ";

// проверка на принадлежность символа _letter строке _str
static bool InStr(const string& _str, const char& _letter)
{
	bool res = false;
	const int SIZE = _str.size();

	for (int i = 0; i < SIZE && !res; ++i)
		res = _letter == _str[i];

	return res;
}

// преобразование строки в моном; возращает true при успешном преобразовании
static bool ToMonom(const string& _str, int firstPos, int lastPos, TMonom* _monom) 
{

}

// сравнение тройки чисел (x1,y1,z1) с тройкой чисел (x2,y2,z2)
static char CompareThree(int x1, int y1, int z1, int x2, int y2, int z2)
{
	char res;

	if (x1 == x2 && y1 == y2 && z1 == z2) res = '=';
	else if (x1 < x2 || x1 == x2 && y1 < y2 || x1 == x2 && y1 == y2 && z1 < z2) res = '<';
	else res = '>';

	return res;
}


// CONSTRUCTORS & DESTRUCTOR

TPolynom::TPolynom()
{
	this->THeadRing::THeadRing();
	pHead->value = { 0.0 };
}

TPolynom::TPolynom(double _c, int _x, int _y, int _z)
{
	const int COUNT = 3;
	int degree[COUNT] = { _x, _y, _z };

	for (int i = 0; i < COUNT; ++i) 
		if (degree[i] < MINDEGREE || degree[i] > MAXDEGREE) {
			std::exception exc("constructor TPolynom(double, int, int, int) : Степень для переменной выходит за рамки допустимых значений для степеней");
			throw exc;
		}

	TMonom addMonom = { _c, _x, _y, _z};
	this->THeadRing::THeadRing(addMonom);

	pHead->value = { 0.0 };
}

TPolynom::TPolynom(const TMonom& _monom)
{
	const int COUNT = 3;
	int degree[COUNT] = { _monom.indX, _monom.indY, _monom.indZ };

	for (int i = 0; i < COUNT; ++i)
		if (degree[i] < MINDEGREE || degree[i] > MAXDEGREE) {
			std::exception exc("constructor TPolynom(const TMonom&) : index входящего монома имеет неправильное значение");
			throw exc;
		}

	this->THeadRing::THeadRing(_monom);

	pHead->value = { 0.0 };
}

TPolynom::TPolynom(TPolynom& _polynom)
{
	this->THeadRing::THeadRing(_polynom);

	pHead->value = { 0.0 };
}

TPolynom::TPolynom(const string& _str)
{
	// "0123456789+-*^.xXyYzZ" - допустимые символы

	this->TPolynom::TPolynom();

	const int SIZE = _str.size();

	const int NOVALUE = -1;
	int firstPos = NOVALUE, lastPos = NOVALUE;
	int pos;
	char op = '\0';

	for (pos = 0; pos < SIZE; ++pos) {
		char letter = _str[pos];

		if (letter == ' ') continue;

		if (letter == '-' || letter == '+') 
			op = letter;
		else if (InStr(VALIDCHARACTERS.substr(5), letter)) 	// VALIDCHARACTERS.substr(5) == "0123456789xXyYzZ"
			op = '+';
		else {
			std::exception exc("TPolynom(const string&) : неправильная входящая строка");
		}

		++pos;
		firstPos = pos;
		break;
	}

	for (; pos < SIZE; ++pos) {
		char letter = _str[pos];

		if (letter == ' ') continue;

		if (letter == '-' || letter == '+') {
			TMonom mon;
			lastPos = pos - 1;
			bool res = ToMonom(_str, firstPos, lastPos, &mon);

			if (!res) {
				std::exception exc("constructor Tpolynom(const string&) : не удалось преобразовать подстроку в моном");
				throw exc;
			}

			if (op == '-') mon.coeff = -mon.coeff;

			TPolynom pol(mon);
			this->operator+=(pol);

			firstPos = pos + 1;
			lastPos = NOVALUE;
			op = letter;
		}
	}

	if (firstPos != NOVALUE) {
		TMonom mon;
		lastPos = SIZE - 1;
		bool res = ToMonom(_str, firstPos, lastPos, &mon);

		if (!res) {
			std::exception exc("constructor Tpolynom(const string&) : не удалось преобразовать подстроку в моном");
			throw exc;
		}

		if (op == '-') mon.coeff = -mon.coeff;

		TPolynom pol(mon);
		this->operator+=(pol);
	}
}

TPolynom::~TPolynom() {}

// OPERATOR=

TPolynom& TPolynom::operator=(const TMonom& _monom) 
{
	const int COUNT = 3;
	int degree[COUNT] = { _monom.indX, _monom.indY, _monom.indZ };
	for (int i = 0; i < COUNT; ++i)
		if (degree[i] < MINDEGREE || degree[i] > MAXDEGREE) {
			std::exception exc("TPolynom::operator=(const TMonom&) : неправильная степень монома");
			throw exc;
		}

	this->THeadRing::operator=(_monom);
	return *this;
}

TPolynom& TPolynom::operator=(TPolynom& _polynom)
{
	this->THeadRing::operator=(_polynom);
	return *this;
}

TPolynom& TPolynom::operator=(const string& _str)
{
	TPolynom pol(_str);
	return (*this = pol);
}

// ARITHMETIC METHODS WITH TMONOM

TPolynom& TPolynom::operator+=(const TMonom& _monom)
{
	const int COUNT = 3;
	int degree[COUNT] = { _monom.indX, _monom.indY, _monom.indZ };
	for (int i = 0; i < COUNT; ++i)
		if (degree[i] < MINDEGREE || degree[i] > MAXDEGREE) {
			std::exception exc("TPolynom::operator+=(const TMonom&) : неправильная степень монома");
			throw exc;
		}

	int xm = _monom.indX, ym = _monom.indY, zm = _monom.indZ;

	for (this->Reset(); !this->IsEnd(); this->GoNext()) {
		int x = this->pCurr->value.indX, y = this->pCurr->value.indY, z = this->pCurr->value.indZ;

		char compare = CompareThree(xm, ym, zm, x, y, z);

		if (compare == '=') {
			this->pCurr->value.coeff += _monom.coeff;
			break;
		}
		else if (compare == '<') {
			this->InsCurr(_monom);
			break;
		}
	}

	// либо this изначально пустой, либо _monom нужно вставлять в конец
	if (this->IsEnd()) this->InsLast(_monom);

	return *this;
}

TPolynom& TPolynom::operator-=(const TMonom& _monom) 
{
	TMonom oppositeMonom = { -_monom.coeff, _monom.indX, _monom.indY, _monom.indZ };
	*this += oppositeMonom;
	return *this;
}

TPolynom& TPolynom::operator*=(const TMonom& _monom) 
{
	double coeffM = _monom.coeff;
	int xM = _monom.indX, yM = _monom.indY, zM = _monom.indZ;

	for (this->Reset(); !this->IsEnd(); this->GoNext()) {
		TMonom* p = &this->pCurr->value;

		const int COUNT = 3;
		int degreeNew[COUNT] = { p->indX + xM, p->indY + yM, p->indZ + zM };

		for (int i = 0; i < COUNT; ++i)
			if (degreeNew[i] < MINDEGREE || degreeNew[i] > MAXDEGREE) {
				std::exception exc("TPolynom::operator*=(const TMonom&) : степень переменной одного из мономов получающегося полинома принимает неправильное значение");
				throw exc;
			}

		*p = { p->coeff * coeffM, degreeNew[0], degreeNew[1], degreeNew[2] };
	}

	return *this;
}

TPolynom& TPolynom::operator/=(const TMonom& _monom)
{
	double coeffM = _monom.coeff;
	int xM = _monom.indX, yM = _monom.indY, zM = _monom.indZ;

	for (this->Reset(); !this->IsEnd(); this->GoNext()) {
		TMonom* p = &this->pCurr->value;

		const int COUNT = 3;
		int degreeNew[COUNT] = { p->indX - xM, p->indY - yM, p->indZ - zM };

		for (int i = 0; i < COUNT; ++i)
			if (degreeNew[i] < MINDEGREE || degreeNew[i] > MAXDEGREE) {
				std::exception exc("TPolynom::operator*=(const TMonom&) : степень переменной одного из мономов получающегося полинома принимает неправильное значение");
				throw exc;
			}

		*p = { p->coeff / coeffM, degreeNew[0], degreeNew[1], degreeNew[2] };
	}

	return *this;
}

TPolynom TPolynom::operator+(const TMonom& _monom)
{
	TPolynom res(*this);
	res += _monom;
	return res;
}

TPolynom TPolynom::operator-(const TMonom& _monom)
{
	TPolynom res(*this);
	res -= _monom;
	return res;
}

TPolynom TPolynom::operator*(const TMonom& _monom)
{
	TPolynom res(*this);
	res *= _monom;
	return res;
}

TPolynom TPolynom::operator/(const TMonom& _monom)
{
	TPolynom res(*this);
	res /= _monom;
	return res;
}

// ARITHMETIC METHODS WITH TPOLYNOM

/*
TPolynom& TPolynom::operator+=(TPolynom& _polynom) 
{
	if (_polynom.GetLength() == 0)		return *this;

	int x1, y1, z1;		// степени монома 1-го полинома
	int x2, y2, z2;		// степени монома 2-го полинома

	_polynom.Reset();
	x2 = _polynom.pCurr->value.indX, y2 = _polynom.pCurr->value.indY, z2 = _polynom.pCurr->value.indZ;

	for (this->Reset(); !this->IsEnd(); this->GoNext()) {
		x1 = this->pCurr->value.indX, y1 = this->pCurr->value.indY, z1 = this->pCurr->value.indZ;

		char compare = CompareThree(x1, y1, z1, x2, y2, z2);

		if (compare == '=') {
			this->pCurr->value.coeff += _polynom.pCurr->value.coeff;

			_polynom.GoNext();
			if (_polynom.IsEnd()) break;
			x2 = _polynom.pCurr->value.indX, y2 = _polynom.pCurr->value.indY, z2 = _polynom.pCurr->value.indZ;
		}

		else if (compare == '<') continue;

		else {// compare == '>'
			do {		
				this->InsCurr(_polynom.pCurr->value);

				_polynom.GoNext();
				if (_polynom.IsEnd()) break;

				x2 = _polynom.pCurr->value.indX, y2 = _polynom.pCurr->value.indY, z2 = _polynom.pCurr->value.indZ;
				compare = CompareThree(x1, y1, z1, x2, y2, z2);
			} while (compare == '>');

			if (_polynom.IsEnd()) break;
		}
	}

	// возжможна ситуация, когда this полином полностью пробежали, но осталась непройденная часть _polynom полинома
	for (; _polynom.IsEnd(); _polynom.GoNext()) 
		this->InsLast(_polynom.pCurr->value);

	return *this;
}
*/

/*
TPolynom& TPolynom::operator-=(TPolynom& _polynom)
{
	for (_polynom.Reset(); !_polynom.IsEnd(); _polynom.GoNext())
		_polynom.pCurr->value.coeff *= -1.0;

	*this += _polynom;

	for (_polynom.Reset(); !_polynom.IsEnd(); _polynom.GoNext())
		_polynom.pCurr->value.coeff *= -1.0;

	return *this;
}
*/

TPolynom& TPolynom::operator+=(TPolynom& _polynom)
{
	for (_polynom.Reset(); !_polynom.IsEnd(); _polynom.GoNext()) 
		*this += _polynom.GetCurr()->value;
	
	return *this;
}

TPolynom& TPolynom::operator-=(TPolynom& _polynom)
{
	for (_polynom.Reset(); !_polynom.IsEnd(); _polynom.GoNext())
		*this -= _polynom.GetCurr()->value;

	return *this;
}

TPolynom& TPolynom::operator*=(TPolynom& _polynom)
{
	TPolynom copyPol(*this);

	this->DelList();

	for (copyPol.Reset(); !copyPol.IsEnd(); copyPol.GoNext()) {
		TMonom mon = copyPol.GetCurr()->value;

		*this += _polynom * mon;
	}
}