#include "../include/app_polynom.h"

AppPolynom::AppPolynom() : Arr(new std::vector<TPolynom>) {}

AppPolynom::~AppPolynom() { delete Arr; }

void AppPolynom::AddPolynom(const string& in) {
	TPolynom tp;

	try { tp = in; }
	catch (...) { throw ""; }

	Arr->push_back(tp);
}

void AppPolynom::DelPolynom(int pos) {
	if (pos < 0 || pos >= this->GetSize() || this->GetSize() == MAXSIZE) throw "";

	for (int i = pos + 1; i < this->GetSize(); ++i) Arr[i - 1] = Arr[i];

	Arr->pop_back();
}

void AppPolynom::DelAll() { Arr->clear(); }

void AppPolynom::Perform(int l, char op, int r) {
	const size_t SIZE = Arr->size();

	if (l < 0 || l >= SIZE || r < 0 || r >= SIZE) throw "";
	if (SIZE == MAXSIZE) throw "";

	try {
		switch (op) {
		case '+': Arr->push_back(Arr->at(l) + Arr->at(r)); break;
		case '-': Arr->push_back(Arr->at(l) - Arr->at(r)); break;
		case '*': Arr->push_back(Arr->at(l) * Arr->at(r)); break;
		case '/':
			if (Arr->at(r).GetLength() != 1) throw "";
			Arr->at(r).Reset();
			Arr->push_back(Arr->at(l) / (Arr->at(r).GetCurr()->value));
			break;
		case '=': Arr->at(l) = Arr->at(r); break;
		default: throw "";
		}
	}
	catch (...) { throw ""; }
}