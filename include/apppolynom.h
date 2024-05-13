#pragma once

#include <vector>
#include <string>
#include "../include/tpolynom.h"

using std::vector;
using std::string;

class AppPolynom {
	vector<TPolynom> vec;
	string pol, lnum, op, rnum;
	const string zero = "NULL";
public:
	AppPolynom();

	bool SetPOL(const string&);
	bool SetLNUM(const string&);
	bool SetOP(const string&);
	bool SetRNUM(const string&);

	bool AddPolynom();
	bool DelPolynom(int pos);
	bool Perform();

	size_t GetSize() const noexcept { return vec.size(); }
};