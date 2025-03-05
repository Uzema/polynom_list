#include "polynom.h"
#include <gtest.h>
#include <vector>

TEST(polynom, stuff) {
	Polynom thing("16x^1y^1z^1+15X^2y^5z^0-2x^1y^5z^2");
	ASSERT_NO_THROW();
}