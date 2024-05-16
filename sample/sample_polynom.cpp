#include "../include/headersamples.h"
#include "../include/tpolynom.h"

void sample_polynom() {
	TPolynom pol1;
	TPolynom pol2("x^2*z + y");
	std::string str1 = pol1.ToString();
	std::string str2 = pol2.ToString();

	std::cout << "pol1 = " << str1 << std::endl;
	std::cout << "pol2 = " << str2 << std::endl;
}