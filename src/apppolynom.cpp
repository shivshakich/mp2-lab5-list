#include "../include/apppolynom.h"

AppPolynom::AppPolynom() : vec(), pol(""), lnum(""), op(""), rnum("") {}

bool AppPolynom::SetPOL(const string& in)
{
	try {
		TPolynom(in);
	}
	catch (...) {
		return false;
	}

	pol = in;
	return true;
}

bool AppPolynom::SetLNUM(const string& in)
{
	int n;
	size_t len = -1;

	try {
		n = std::stoi(in, &len);
	}
	catch (...) {
		return false;
	}

	if (n - 1 < 0 || n-1 >= GetSize()) return false;
	lnum = in;
	return true;
}
bool AppPolynom::SetOP(const string& in) {
	if (in.size() != 1) return false;

	char c = in[0];
	bool res = (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '=');
	if (res) op = in;

	return res;
}
bool AppPolynom::SetRNUM(const string& in)
{
	if (in == zero) { rnum = in; return true; }

	int n;
	size_t len = -1;

	try {
		n = std::stoi(in, &len);
	}
	catch (...) {
		return false;
	}

	if (n - 1 < 0 || n - 1 > GetSize()) return false;
	rnum = in;
	return true;
}

bool AppPolynom::AddPolynom()
{
	bool res = true;
	try {
		vec.push_back(TPolynom(pol));
	}
	catch (...) {
		res = false;
	}

	return res;
}

bool AppPolynom::DelPolynom(int pos) {
	if (pos - 1 < 0 || pos - 1 >= GetSize()) return false;

	pos = pos - 1;

	if (pos == GetSize() - 1) {
		vec.pop_back();
		return true;
	}

	for (int i = pos + 1; i < GetSize(); ++i) {
		vec[i - 1] = vec[i];
	}
	vec.pop_back();
	return true;
}

bool AppPolynom::Perform()
{
	int l = std::stoi(lnum), r = std::stoi(rnum);
	try {
		switch (op[0]) {
		case '+': vec[l - 1] += vec[r - 1]; break;
		case '-': vec[l - 1] -= vec[r - 1]; break;
		case '*': vec[l - 1] *= vec[r - 1]; break;
		case '/':
			if (vec[r - 1].GetLength() != 1) throw "";
			const TMonom* p = &vec[r - 1].GetCurr()->value;
			vec[l - 1] /= *p;
			break;
		case '=': 
			if (rnum == zero) {
				DelPolynom(l); break;
			}
			vec[l - 1] = vec[r - 1]; break;
		}
	}
	catch (...) { return false; }
	
	return true;
}