#include "../gtest/gtest.h"
#include "../include/tpolynom.h"

//  онстанты и переменные дл€ проведени€ тестов

static const size_t SIZE1 = 40;
static const string S1[SIZE1] = {
	"",	"100", "-100", "0", "0.0",											/* 1-5 */
	"-0", "+0", "-0.0", "+0.0", "x",										/* 6-10 */
	" ", "y", "100.00000", "+100.2345", "-100.2345",						/* 11-15 */
	"x", "y", "z", "X", "Z",												/* 16-20 */
	"Z", "-x", "- Z", "10*y", "10*x",										/* 21-25 */
	"10*x*y", "-10.62*x*z", "x*y*z", "-10.23*x^4", "-10.12*X^2*y^6",		/* 26-30 */
	"5.2*x^1*Y^2*z^4", "x^0", "X^0*Y^0*Z^0", "x + y", "x- y",				/* 31-35 */
	"x^0*y - 50.4999*z", "x^2*y^2*z^2 - 5*x^2*y^2*z^2", " Y +y+y -Y +y- y-y- Y", "12.43*x^7 + x^8*y^0 - z^12", "z^2"	/* 36-40 */
};

static const size_t LEN1 = 33;
static const TMonom MON[LEN1] = {
	{0.0}, {100.0}, {-100.0}, {0.0}, {0.0},									/* 1-5 */
	{0.0}, {0.0}, {0.0}, {0.0}, {1.0, 1},									/* 6-10 */
	{0.0}, {1.0, 0, 1}, {100.0}, {100.2345}, {-100.2345},					/* 11-15*/
	{1.0, 1}, {1.0, 0, 1}, {1.0, 0,0,1}, {1.0, 1}, {1.0, 0,0,1},			/* 16-20 */
	{1.0, 0,0,1}, {-1.0, 1}, {-1.0, 0,0,1}, {10.0, 0,1}, {10.0, 1},			/* 21-25 */
	{10.0, 1,1}, {-10.62, 1,0,1}, {1.0,1,1,1}, {-10.23, 4}, {-10.12,2,6},	/* 26-30 */
	{5.2, 1,2,4}, {1.0}, {1.0}												/* 31-33 */
};

static const size_t LEN2 = 7;
static TPolynom POL[LEN2] = {
	TPolynom(1.0, 1) + TMonom{1.0, 0,1}, TPolynom(1.0, 1) - TMonom{1.0, 0,1},			/* 34-35 */
	TPolynom(1.0, 0, 1) - TMonom{50.4999, 0,0,1}, TPolynom(-4.0, 2,2,2),				/* 36-37 */
	TPolynom(), TPolynom(12.43, 7) + TMonom{1.0, 8} - TMonom{1.0, 0,0,12},				/* 38-39 */
	TPolynom(1.0, 0,0,1)																/* 40 */
};

static const size_t SIZE2 = 14;
static const string S2[SIZE2] = {
	"+", "-", "10.8+", "-10-",											/* 1-5 */
	"hello, world!", "^", "x^ ", "x^", "--",							/* 6-10 */
	"xy", "3.2 * 5.0", "x^2 +- y^3", "Xx", "3.5 * x^2*y^2*z^2 * x^3*y^3*z^3"	/* 11-14 */
};

// CONSTRUCTORS

TEST(TPolynom, can_create_polynom) {
	ASSERT_NO_THROW(TPolynom l);				// default constructor
	ASSERT_NO_THROW(TPolynom l(123.456));		// conversion constructor
	ASSERT_NO_THROW(TPolynom l(0.0));		

	TPolynom v;
	TPolynom l(123);
	ASSERT_NO_THROW(TPolynom list(v));		// copy constructor
	ASSERT_NO_THROW(TPolynom list(l));

	// conversion constructor
	for (int i = 0; i < SIZE1; ++i)
		ASSERT_NO_THROW(TPolynom p(S1[i]));

	for (int i = 0; i < SIZE2; ++i)
		ASSERT_ANY_THROW(TPolynom p(S2[i]));
}

TEST(TPolynom, polynom_created_by_default_constructor_has_only_head_vertex) {
	TPolynom list;
	ASSERT_EQ(list.GetLength(), 0);
}

TEST(TPolynom, polynom_created_by_conversion_constructor_has_correct_values) {
	double d = 59.76;
	TMonom mon = { d, 2, 3, 4 };

	TPolynom pol1(d);
	pol1.Reset();
	const TMonom* p1 = &pol1.GetCurr()->value;
	ASSERT_TRUE(pol1.GetLength() == 1);
	ASSERT_TRUE(p1->coeff == d);
	ASSERT_TRUE(p1->indX == 0);
	ASSERT_TRUE(p1->indY == 0);
	ASSERT_TRUE(p1->indZ == 0);

	TPolynom pol2(mon);
	pol2.Reset();
	const TMonom* p2 = &pol2.GetCurr()->value;
	ASSERT_TRUE(pol2.GetLength() == 1);
	ASSERT_TRUE(p2->coeff == d);
	ASSERT_TRUE(p2->indX == 2);
	ASSERT_TRUE(p2->indY == 3);
	ASSERT_TRUE(p2->indZ == 4);
}

TEST(TPolynom, polynom_created_by_string_conversion_constructor_has_correct_values) {
	for (int i = 0; i < LEN1; ++i) {
		TPolynom pol(S1[i]);
		ASSERT_EQ(pol.GetLength(), 1 - (MON[i].coeff == 0));

		pol.Reset();
		const TMonom* p = &pol.GetCurr()->value;

		ASSERT_EQ(p->coeff, MON[i].coeff);
		ASSERT_EQ(p->indX, MON[i].indX);
		ASSERT_EQ(p->indY, MON[i].indY);
		ASSERT_EQ(p->indZ, MON[i].indZ);
	}

	for (int i = LEN1; i < SIZE1; ++i) {
		//string sss = S1[i];
		TPolynom pol(S1[i]);
		//int n = pol.GetLength();
		//if (n == 1) { pol.Reset(); const TMonom* p = &pol.GetCurr()->value; }
		//POL[i - LEN1].Reset();
		//const TMonom* p = &POL[i - LEN1].GetCurr()->value;

		ASSERT_EQ(pol.GetLength(), POL[i-LEN1].GetLength());
		ASSERT_TRUE(pol == POL[i-LEN1]);
	}
}

TEST(TPolynom, polynom_created_by_string_conversion_constructor_has_correct_order) {
	for (int i = 0; i < SIZE1; ++i) {
		TPolynom pol(S1[i]);
		ASSERT_TRUE(CheckOrder(pol));
	}
}

TEST(TPolynom, polynom_created_by_copy_constructor_is_equivalent_to_original_one) {
	TPolynom voidPol;
	TPolynom _pol(voidPol);
	ASSERT_EQ(_pol.GetLength(), 0);

	for (int i = 0; i < LEN2; ++i) {
		TPolynom _copy(POL[i]);
		ASSERT_TRUE(_copy == POL[i]);
	}
}

// OPERATOR=

TEST(TPolynom, polynom_assigned_to_monom) {
	TPolynom pol;			// default constructor

	for (int i = 0; i < LEN1; ++i) {
		pol = MON[i];

		if (MON[i].coeff == 0.0) ASSERT_EQ(pol.GetLength(), 0);
		else {
			ASSERT_EQ(pol.GetLength(), 1);
			pol.Reset();
			const TMonom* p = &pol.GetCurr()->value;
			ASSERT_EQ(p->indX, MON[i].indX);
			ASSERT_EQ(p->indY, MON[i].indY);
			ASSERT_EQ(p->indZ, MON[i].indZ);
		}
	}
}

TEST(TPolynom, polynom_assigned_to_polynom) {
	TPolynom pol;			// default constructor

	for (int i = 0; i < LEN2; ++i) {
		pol = POL[i];
	
		ASSERT_TRUE(pol == POL[i]);
	}
}