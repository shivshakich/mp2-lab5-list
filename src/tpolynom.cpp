#include <string>
#include <exception>
#include "../include/tpolynom.h"

// допустимые символы для написания полинома
//static const string VALIDCHARACTERS = "*^.-+0123456789xXyYzZ";		// зачем это нужно?

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
	double c = 1.0;
	int x = 0, y = 0, z = 0;
	bool wasX = false, wasY = false, wasZ = false;

	const char NOTHING = '\0';
	const char DIGIT = '1';
	const char MULT = '*';
	const char VAR = 'a';
	char lastLetter = NOTHING;

	// избавляемся от пробелов в начале
	for (; firstPos <= lastPos && _str[firstPos] == ' '; ++firstPos)
		;

	size_t len;

	if ('0' <= _str[firstPos] && _str[firstPos] <= '9') {
		c = std::stod(_str.substr(firstPos, lastPos - firstPos + 1), &len);
		firstPos = firstPos + len;
		lastLetter = DIGIT;
	}

	for (int i = firstPos; i <= lastPos; ++i) {
		char letter = _str[i];

		if (letter == ' ') continue;

		if (letter == 'x' || letter == 'X') {
			if (lastLetter != NOTHING && lastLetter != '*') return false;
			else if (wasX) return false;

			wasX = true;

			if (i + 1 <= lastPos && _str[i + 1] == '^') {
				if (i + 2 > lastPos) return false;

				int n = std::stoi(_str.substr(i + 2, lastPos - i - 1), &len);
				// получили число (int)n, занимающее len символов в строке str;

				if (len == 0) return false;
				i += len+1;
				x = n;
				lastLetter = DIGIT;
			}
			else {
				lastLetter = VAR;
				x = 1;
			}
		}

		else if (letter == 'y' || letter == 'Y') {
			if (lastLetter != NOTHING && lastLetter != '*') return false;
			else if (wasY) return false;

			wasY = true;

			if (i + 1 <= lastPos && _str[i + 1] == '^') {
				if (i + 2 > lastPos) return false;

				int n = std::stoi(_str.substr(i + 2, lastPos - i - 1), &len);
				// получили число (int)n, занимающее len символов в строке str;

				if (len == 0) return false;
				i += len+1;
				y = n;
				lastLetter = DIGIT;
			}
			else {
				lastLetter = VAR;
				y = 1;
			}
		}

		else if (letter == 'z' || letter == 'Z') {
			if (lastLetter != NOTHING && lastLetter != '*') return false;
			else if (wasZ) return false;

			wasZ = true;

			if (i + 1 <= lastPos && _str[i + 1] == '^') {
				if (i + 2 > lastPos) return false;

				int n = std::stoi(_str.substr(i + 2, lastPos - i - 1), &len);
				// получили число (int)n, занимающее len символов в строке str;

				if (len == 0) return false;
				i += len+1;
				z = n;
				lastLetter = DIGIT;
			}
			else {
				lastLetter = VAR;
				z = 1;
			}
		}

		else if (letter == '*') {
			if (lastLetter != DIGIT && lastLetter != VAR) return false;
			lastLetter = MULT;
		}

		else return false;
	}

	if (lastLetter != DIGIT && lastLetter != VAR) return false;
	else if (lastLetter == NOTHING) *_monom = { 0.0, 0, 0, 0 };
	else *_monom = { c, x, y, z };

	return true;
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
	this->THeadRing<TMonom>::THeadRing();
	pHead->value = { 0.0 };
}

TPolynom::TPolynom(double _c, int _x, int _y, int _z)
{
	this->TPolynom::TPolynom();

	const int COUNT = 3;
	int degree[COUNT] = { _x, _y, _z };

	for (int i = 0; i < COUNT; ++i) 
		if (degree[i] < MINDEGREE || degree[i] > MAXDEGREE) {
			std::exception exc("constructor TPolynom(double, int, int, int) : Степень для переменной выходит за рамки допустимых значений для степеней");
			throw exc;
		}

	if (_c != 0.0) {
		TMonom addMonom = { _c, _x, _y, _z };
		this->InsLast(addMonom);
	}
}

TPolynom::TPolynom(const TMonom& _monom)
{
	this->TPolynom::TPolynom();

	const int COUNT = 3;
	int degree[COUNT] = { _monom.indX, _monom.indY, _monom.indZ };

	for (int i = 0; i < COUNT; ++i)
		if (degree[i] < MINDEGREE || degree[i] > MAXDEGREE) {
			std::exception exc("constructor TPolynom(const TMonom&) : index входящего монома имеет неправильное значение");
			throw exc;
		}

	if (_monom.coeff != 0.0) this->InsLast(_monom);
}

TPolynom::TPolynom(TPolynom& _polynom)
{
	this->THeadRing<TMonom>::THeadRing(_polynom);

	pHead->value = { 0.0 };
}

TPolynom::TPolynom(const TPolynom& _polynom) {
	this->TPolynom::TPolynom();

	if (_polynom.GetLength() == 0) return;

	const TNode<TMonom>* ph = _polynom.pHead;

	for (TNode<TMonom> *p = _polynom.pFirst; p != ph; p = p->pNext) 
		this->InsLast(p->value);
}

TPolynom::TPolynom(TPolynom&& _polynom) noexcept
{
	this->TPolynom::TPolynom();
	std::swap(this->pHead, _polynom.pHead);
	std::swap(this->pStop, _polynom.pStop);
	std::swap(this->pFirst, _polynom.pFirst);
	std::swap(this->pLast, _polynom.pLast);
	std::swap(this->pCurr, _polynom.pCurr);
	std::swap(this->pPrev, _polynom.pPrev);
	std::swap(this->length, _polynom.length);
	std::swap(this->pos, _polynom.pos);
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

		if (letter == '-' || letter == '+') {
			op = letter;
			++pos;
		}
		else if (InStr("0123456789xXyYzZ", letter)) 	// VALIDCHARACTERS.substr(5) == "0123456789xXyYzZ"
			op = '+';
		else {
			std::exception exc("TPolynom(const string&) : неправильная входящая строка");
			throw exc;
		}

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
			for (int i : {mon.indX, mon.indY, mon.indZ}) 
				if (i < MINDEGREE || i > MAXDEGREE) {
					std::exception exc("TPolynom(const string&) : степень одной из переменной принимает не правильное значение");
					throw exc;
				}

			if (op == '-') mon.coeff = -mon.coeff;

			*this += mon;
			
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
		for (int i : {mon.indX, mon.indY, mon.indZ})
			if (i < MINDEGREE || i > MAXDEGREE) {
				std::exception exc("TPolynom(const string&) : степень одной из переменной принимает не правильное значение");
				throw exc;
			}

		if (op == '-') mon.coeff = -mon.coeff;

		*this += mon;
	}
}

//TPolynom::~TPolynom() { this->THeadRing::~THeadRing(); }

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

	if (_monom.coeff != 0.0) this->THeadRing<TMonom>::operator=(_monom);
	else this->DelList();

	return *this;
}

TPolynom& TPolynom::operator=(TPolynom& _polynom)
{
	this->THeadRing<TMonom>::operator=(_polynom);
	return *this;
}

TPolynom& TPolynom::operator=(TPolynom&& _polynom) noexcept
{
	std::swap(this->pHead, _polynom.pHead);
	std::swap(this->pStop, _polynom.pStop);
	std::swap(this->pFirst, _polynom.pFirst);
	std::swap(this->pLast, _polynom.pLast);
	std::swap(this->pCurr, _polynom.pCurr);
	std::swap(this->pPrev, _polynom.pPrev);
	std::swap(this->length, _polynom.length);
	std::swap(this->pos, _polynom.pos);

	return *this;
}

TPolynom& TPolynom::operator=(const string& _str)
{
	return (*this = TPolynom(_str));
}

// ARITHMETIC METHODS WITH TMONOM

TPolynom& TPolynom::operator+=(const TMonom& _monom)
{
	if (_monom.coeff == 0.0) return *this;

	const int COUNT = 3;
	int degree[COUNT] = { _monom.indX, _monom.indY, _monom.indZ };
	for (int i = 0; i < COUNT; ++i)
		if (degree[i] < MINDEGREE || degree[i] > MAXDEGREE) {
			std::exception exc("TPolynom::operator+=(const TMonom&) : неправильная степень монома");
			throw exc;
		}

	int xm = _monom.indX, ym = _monom.indY, zm = _monom.indZ;

	bool wasAdd = false;

	for (this->Reset(); !this->IsEnd(); ) {
		int x = this->pCurr->value.indX, y = this->pCurr->value.indY, z = this->pCurr->value.indZ;

		char compare = CompareThree(xm, ym, zm, x, y, z);

		if (compare == '=') {
			double c = (this->pCurr->value.coeff += _monom.coeff);
			if (c == 0.0) this->DelCurr();
			wasAdd = true;
			break;
		}
		else if (compare == '<') {
			this->InsCurr(_monom);
			wasAdd = true;
			break;
		}
		else GoNext();
	}

	// либо this изначально пустой, либо _monom нужно вставлять в конец
	if (!wasAdd) 
		this->InsLast(_monom);

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
	if (_monom.coeff == 0.0) {
		this->DelList();
		return *this;
	}

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
	if (_monom.coeff == 0.0) {
		std::exception exc("TPolynom::operator*=(const TMonom&) : деление на ноль");
		throw exc;
	}

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

TPolynom& TPolynom::operator+=(TPolynom&& _polynom)
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

		*this += _polynom * mon;			// здесь, (_polynom * mon) - rvalue объект, поэтому необходим метод operator+=(TPolynom&&)
	}

	return *this;
}

TPolynom TPolynom::operator+(TPolynom& _polynom)
{
	TPolynom res(*this);
	res += _polynom;
	return res;
}

TPolynom TPolynom::operator-(TPolynom& _polynom)
{
	TPolynom res(*this);
	res -= _polynom;
	return res;
}

TPolynom TPolynom::operator*(TPolynom& _polynom)
{
	TPolynom res(*this);
	res *= _polynom;
	return res;
}

// COMPARE METHODS

bool TPolynom::operator==(TPolynom& _polynom)
{
	if (this == &_polynom) return true;

	bool res = this->GetLength() == _polynom.GetLength();

	if (!res) return false;

	for (this->Reset(), _polynom.Reset(); !this->IsEnd() && res; this->GoNext(), _polynom.GoNext()) {
		const TMonom	*p1 = &this->GetCurr()->value, 
						*p2 = &_polynom.GetCurr()->value;

		res = (p1->coeff == p2->coeff) && (p1->indX == p2->indX) && (p1->indY == p2->indY) && (p1->indZ == p2->indZ);
	}

	return res;
}

bool TPolynom::operator!=(TPolynom& _polynom)
{
	return !this->operator==(_polynom);
}

// OHTER METHODS : TOSTRING

string TPolynom::ToString()
{
	if (this->GetLength() == 0) 
		return "0.0";

	double c;
	int x, y, z;
	string res = "";

	for (this->Reset(); !this->IsEnd(); this->GoNext()) {
		const TMonom* p = &this->GetCurr()->value;

		c = p->coeff;
		x = p->indX;
		y = p->indY;
		z = p->indZ;

		if (c > 0.0) res += '+';
		res += std::to_string(c);
		
		if (x < 0) res += "*x^(" + std::to_string(x) + ")";
		else if (x == 1) res += "*x";
		else if (x > 0) res += "*x^" + std::to_string(x);

		if (y < 0) res += "*y^(" + std::to_string(y) + ")";
		else if (y == 1) res += "*y";
		else if (y > 0) res += "*y^" + std::to_string(y);

		if (z < 0) res += "*z^(" + std::to_string(x) + ")";
		else if (z == 1) res += "*z";
		else if (z > 0) res += "*z^" + std::to_string(z);

		res += "";
	}

	return res;
}

bool CheckOrder(TPolynom& _pol) 
{
	if (_pol.GetLength() == 0) return true;

	bool res = true;
	const int COUNT = 3;
	int prevDegree[COUNT], currDegree[COUNT];

	_pol.Reset();
	TMonom* p = &_pol.pCurr->value;
	prevDegree[0] = p->indX; 
	prevDegree[1] = p->indY; 
	prevDegree[2] = p->indZ;
	_pol.GoNext();

	for (; !_pol.IsEnd() && res; _pol.GoNext()) {
		p = &_pol.pCurr->value;
		currDegree[0] = p->indX;
		currDegree[1] = p->indY;
		currDegree[2] = p->indZ;

		char compare = CompareThree(prevDegree[0], prevDegree[1], prevDegree[2], currDegree[0], currDegree[1], currDegree[2]);
		res = compare == '<';

		prevDegree[0] = p->indX;
		prevDegree[1] = p->indY;
		prevDegree[2] = p->indZ;
	}

	return res;
}

// OPERATOR<< & OPERATOR>>

ostream& operator<<(ostream& os, TPolynom& pol) 
{
	os << pol.ToString();
	return os;
}

istream& operator>>(istream& is, TPolynom& pol)
{
	string str = "";
	char letter;

	for (is >> letter; letter != '\0' && letter != '\t' && letter != '\n' && letter != EOF; is >> letter)
		str += letter;

	pol = TPolynom(str);

	return is;
}