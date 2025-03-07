#include "polynom.h"
#include <gtest.h>
#include <vector>

TEST(polynom, stuff) {
	Polynom thing("16x^1y^1z^1+15X^2y^5z^0-2x^1y^5z^2");
	cout << thing[0].getPower() << endl << thing[1].getPower() << endl << thing[2].getPower();
	ASSERT_NO_THROW();
}

TEST(polynom, stuff2) {
	Polynom p1("16x^1y^1z^1+15X^2y^5z^0-2x^1y^5z^2");
	Polynom p2("4x^1y^1z^1+5x^1y^5z^2+666x^1y^2z^3");
	Polynom p3 = p1 + p2;
	ASSERT_NO_THROW();
}

TEST(polynom, stuff3) {
	Polynom p1("16x^1y^1z^1+15X^2y^5z^0");
	Polynom p2("0x^0y^0z^0");
	Polynom p3 = p1 + p2;
	ASSERT_NO_THROW();
}

