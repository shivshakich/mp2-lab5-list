#pragma once

#include <string>
#include <vector>
#include "tpolynom.h"

struct AppPolynom {
	std::vector<TPolynom> vec;
	std::string pol = "", left = "", op = "", right = "";
};

bool AddPol(AppPolynom&);
bool DelPol(AppPolynom&, int);
bool DelAll(AppPolynom&);

bool SetPol(AppPolynom&, const string&);
bool SetLeft(AppPolynom&, const string&);
bool SetOp(AppPolynom&, const string&);
bool SetRight(AppPolynom&, const string&);
bool Perform(AppPolynom&);

int GetSize(const AppPolynom& app) { return app.vec.size(); }
bool GetPol(AppPolynom&, int, TPolynom*);