#pragma once

#include <string>
#include <vector>
#include "tpolynom.h"

static const size_t MAXSIZE = 99;

class AppPolynom {
	std::vector<TPolynom> Arr = {TPolynom(), TPolynom()};						// указатель на начало вектора
public:
	AppPolynom();
	~AppPolynom();

	void AddPolynom(const string&);
	void DelPolynom(int pos);
	void DelAll();

	void Perform(int l, char op, int r);

	size_t GetSize() const noexcept { return Arr.size(); }
	size_t GetMAXSIZE() const noexcept { return MAXSIZE; }
};