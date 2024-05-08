#include <iostream>
#include "../include/headersamples.h"

using std::cout;
using std::endl;

int main() {
	const std::string line = "==========";

	cout << line << " BEGIN - SAMPLE LIST \t" << line << endl;
	sample_list();
	cout << line << " END - SAMPLE LIST \t" << line << endl;

	cout << endl;

	cout << line << " BEGIN - SAMPLE LIST \t" << line << endl;
	sample_headlist();
	cout << line << " END - SAMPLE LIST \t" << line << endl;

	return 0;
}
