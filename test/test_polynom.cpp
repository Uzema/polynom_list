#include "polynom.h"
#include <gtest.h>
#include <vector>

TEST(polynom, CanCreatePolynom) {
	ASSERT_NO_THROW(Polynom p);
}

TEST(polynom, CorrectlyCreateWithStr) {
	Polynom p("x^1y^1z^1");
	EXPECT_EQ(1, p[0].getCoef());
	EXPECT_EQ(111, p[0].getPower());
}

TEST(polynom, CorrectlyCreateWithMonom) {
	Polynom p(Monom(1, 111));
	EXPECT_EQ(1, p[0].getCoef());
	EXPECT_EQ(111, p[0].getPower());
}

TEST(polynom, CorrectInsert) {
	Polynom p;
	p.insert(1.5, 123);
	EXPECT_EQ(1.5, p[0].getCoef());
	EXPECT_EQ(123, p[0].getPower());
}

TEST(polynom, InsertAtCorrectPlace) {
	Polynom p;
	p.insert(1.4, 333);
	p.insert(1.4, 111);
	p.insert(1.4, 222);

	EXPECT_EQ(111, p[0].getPower());
	EXPECT_EQ(222, p[1].getPower());
	EXPECT_EQ(333, p[2].getPower());
}

TEST(polynom, CorrectInsertMonomsWithSameDegree) {
	Polynom p;
	p.insert(1, 111);
	p.insert(1, 111);
	p.insert(1, 111);

	EXPECT_EQ(111, p[0].getPower());
	EXPECT_EQ(3, p[0].getCoef());
}

TEST(polynom, CorrectlyAddPolynomsWithDifDegrees) {
	Polynom p1("1x^1y^1z^1");
	Polynom p2("5x^1y^5z^2");
	Polynom p3 = p1 + p2;

	EXPECT_EQ(1, p3[0].getCoef());
	EXPECT_EQ(5, p3[1].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
	EXPECT_EQ(152, p3[1].getPower());
}

TEST(polynom, CorrectlyAddPolynomsWithSameDegrees) {
	Polynom p1("1x^1y^1z^1");
	Polynom p2("5x^1y^1z^1");
	Polynom p3 = p1 + p2;

	EXPECT_EQ(6, p3[0].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
}

TEST(polynom, CorrectlyAddEmptyPolynom1) {
	Polynom p1("1x^1y^1z^1");
	Polynom p2;
	Polynom p3 = p1 + p2;

	EXPECT_EQ(1, p3[0].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
}

TEST(polynom, CorrectlyAddEmptyPolynom2) {
	Polynom p1;
	Polynom p2("1x^1y^1z^1");
	Polynom p3 = p1 + p2;

	EXPECT_EQ(1, p3[0].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
}


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

TEST(polynom, stuff4) {
	Polynom p1("16x^1y^1z^1+15X^2y^5z^0");
	Polynom p2("4x^1y^1z^1+5x^1y^5z^2+666x^1y^2z^3");
	Polynom p3 = p1 + p2;
	ASSERT_NO_THROW();
}

TEST(polynom, 2additionsOfSameDegree) {
	Polynom p1("16x^1y^1z^1+15X^1y^5z^2");
	Polynom p2("4x^1y^1z^1+5x^1y^5z^2");
	Polynom p3 = p1 + p2;
	ASSERT_NO_THROW();
}

TEST(polynom, additionsOfEmptyPolynom1) {
	Polynom p1("16x^1y^1z^1+15X^1y^5z^2");
	Polynom p2;
	Polynom p3 = p1 + p2;

	EXPECT_EQ(16, p3[0].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
	EXPECT_EQ(15, p3[1].getCoef());
	EXPECT_EQ(152, p3[1].getPower());
}

TEST(polynom, additionsOfEmptyPolynom2) {
	Polynom p1;
	Polynom p2("16x^1y^1z^1+15X^1y^5z^2");
	Polynom p3 = p1 + p2;

	EXPECT_EQ(16, p3[0].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
	EXPECT_EQ(15, p3[1].getCoef());
	EXPECT_EQ(152, p3[1].getPower());
}

TEST(polynom, subtractionOfEmptyPolynom1) {
	Polynom p1("16x^1y^1z^1");
	Polynom p2;
	Polynom p3 = p1 - p2;
	ASSERT_NO_THROW();
}

TEST(polynom, subtractionOfEmptyPolynom2) {
	Polynom p1;
	Polynom p2("16x^1y^1z^1");
	Polynom p3 = p1 - p2;
	ASSERT_NO_THROW();
}

TEST(polynom, multip1) {
	Polynom p1("2x^1y^1z^1");
	Polynom p2("3x^1y^1z^1");
	Polynom p3 = p1 * p2;
	ASSERT_NO_THROW();
}

TEST(polynom, multip2) {
	Polynom p1("2x^1y^1z^1+5x^1y^2z^3");
	Polynom p2("3x^1y^1z^1+6x^2y^2z^2");
	Polynom p3 = p1 * p2;
	ASSERT_NO_THROW();
}

TEST(polynom, multip3) {
	Polynom p1("2x^1y^1z^1");
	Polynom p2;
	Polynom p3 = p1 * p2;
	ASSERT_NO_THROW();
}

TEST(polynom, multip4) {
	Polynom p1("2x^1y^2z^3+5x^4y^4z^4");
	Polynom p2("3x^3y^2z^1+6x^0y^0z^0");
	Polynom p3 = p1 * p2;
	ASSERT_NO_THROW();
}

TEST(polynom, multip5) {
	Polynom p1;
	Polynom p2("2x^1y^1z^1");
	Polynom p3 = p1 * p2;
	ASSERT_NO_THROW();
}

