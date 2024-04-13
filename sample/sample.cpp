#include <iostream>
#include <locale>
#include "../include/tlist.h"

using std::cout;
using std::endl;

void sample_list();

int main() {
	setlocale(LC_CTYPE, "Russian");

	const std::string line = "==========";

	cout << line << " BEGIN - SAMPLE LIST \t" << line << endl;
	sample_list();
	cout << line << " END - SAMPLE LIST \t" << line << endl;


	return 0;
}

void sample_list() {
	const int SIZE = 5;
	double D[SIZE] = { 345.66, -12.55645, 10000.099, 98.00, -5763.59018 };

	TList<double> list;
	for (int i = 0; i < SIZE; ++i)
		list.InsLast(D[i]);


	cout << "длина списка:\t" << (SIZE == list.GetLength()) << endl;

	cout << "правильный порядок:\t";
	int i = 0;
	for (list.Reset(); !list.IsEnd(); list.GoNext()) {
		cout << (list.GetCurr()->value == D[i]) << ' ';
		++i;
	}
	cout << endl;
}