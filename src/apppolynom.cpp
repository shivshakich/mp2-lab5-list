#include "../include/apppolynom.h"

// преобразует строку pol в полином и добавляет её в конец
bool AddPol(AppPolynom& app)
{
	TPolynom tp;

	try { tp = app.pol; }
	catch (...) { return false; }

	app.vec.push_back(tp);

	return true;
}

// удаляет полином на выбранной позиции
bool DelPol(AppPolynom& app, int pos)
{
	const int SIZE = GetSize(app);

	if (pos < 0) return false;
	if (pos < SIZE) {
		for (int i = pos + 1; i < SIZE; ++i) app.vec[i - 1] = app.vec[i];
		app.vec.pop_back();
	}

	return true;
}

bool DelAll(AppPolynom& app)
{
	const int SIZE = GetSize(app);

	for (int i = 0; i < SIZE; ++i) app.vec.pop_back();

	return true;
}

bool SetPol(AppPolynom& app, const string& in)
{
	try { TPolynom tp(in); }
	catch (...) { return false; }

	app.pol = in;

	return true;
}

// в левом окне может быть только цифра
bool SetLeft(AppPolynom& app, const string& in)
{
	bool res = true;

	try {
		size_t len;
		int n = std::stoi(in, &len);

		if (len != in.length()) throw "";
		if (n <= 0 || n > GetSize(app)) throw "";

		app.left = in;
	}
	catch (...) { res = false; }

	return res;
}

// допустимые символы: + - * / =
bool SetOp(AppPolynom& app, const string& in)
{
	bool res = false;
	char c = in[0];

	if (in.length() != 1) res = false;
	else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=') { app.op = in; res = true; }
	else res = false;

	return res;
}

// в правом окне может быть только цифра
bool SetRight(AppPolynom& app, const string& in)
{
	bool res = true;

	try {
		size_t len;
		int n = std::stoi(in, &len);

		if (len != in.length()) throw "";
		if (n <= 0 || n > GetSize(app)) throw "";

		app.right = in;
	}
	catch (...) { res = false; }

	return res;
}

bool Perform(AppPolynom& app)
{
	bool res = SetLeft(app, app.left) && SetOp(app, app.op) && SetRight(app, app.right);

	try {
		if (res) {
			int l = stoi(app.left) - 1, r = stoi(app.right) - 1;

			char c = app.op[0];

			switch (c) {
			case '+': app.vec[l] += app.vec[r]; break;
			case '-': app.vec[l] -= app.vec[r]; break;
			case '*': app.vec[l] *= app.vec[r]; break;
			case '/':
				if (app.vec[r].GetLength() != 1) throw "";
				app.vec[r].Reset();
				app.vec[l] /= app.vec[r].GetCurr()->value;
				break;
			case '=':
				app.vec[l] = app.vec[r];
			}
		}
	}
	catch (...) { res = false; }

	return res;
}

bool GetPol(AppPolynom& app, int pos, TPolynom* tp) {
	bool res;

	if (pos < 0 || pos >= GetSize(app)) res = false;
	else {
		tp = &app.vec[pos];
		res = true;
	}

	return true;
}