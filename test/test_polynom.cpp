#include "polynom.h"
#include <gtest.h>
#include <vector>

TEST(monom, CanCreateMonom) {
	ASSERT_NO_THROW(Monom a);
}

TEST(monom, CanCreateMonomWithCoefAndDeg) {
	Monom m(2, 111);
	EXPECT_EQ(2, m.getCoef());
	EXPECT_EQ(111, m.getPower());
}

TEST(monom, CorreclyGetDegreeX) {
	Monom m(1, 345);
	EXPECT_EQ(3, m.getPowerX());
}

TEST(monom, CorreclyGetDegreeY) {
	Monom m(1, 345);
	EXPECT_EQ(4, m.getPowerY());
}

TEST(monom, CorreclyGetDegreeZ) {
	Monom m(1, 345);
	EXPECT_EQ(5, m.getPowerZ());
}

TEST(monom, CorrectlyAddMonoms) {
	Monom m1(12, 345);
	Monom m2(5, 345);
	Monom m3 = m1 + m2;

	EXPECT_EQ(17, m3.getCoef());
}

TEST(monom, ThrowWhenAddMonomsWithDifferentDegrees) {
	Monom m1(12, 123);
	Monom m2(5, 345);

	EXPECT_ANY_THROW(Monom m3 = m1 + m2);
}

TEST(monom, CorrectlyAddAssignMonoms) {
	Monom m1(12, 345);
	Monom m2(5, 345);
	m1 += m2;

	EXPECT_EQ(17, m1.getCoef());
}

TEST(monom, ThrowWhenAddAssignMonomsWithDifferentDegrees) {
	Monom m1(12, 123);
	Monom m2(5, 345);

	EXPECT_ANY_THROW(m1 += m2);
}

//----------------------------------------//

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

TEST(polynom, CorrectlySubPolynomsWithDifDegrees) {
	Polynom p1("1x^1y^1z^1");
	Polynom p2("5x^1y^5z^2");
	Polynom p3 = p1 - p2;

	EXPECT_EQ(1, p3[0].getCoef());
	EXPECT_EQ(-5, p3[1].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
	EXPECT_EQ(152, p3[1].getPower());
}

TEST(polynom, CorrectlySubPolynomsWithSameDegrees) {
	Polynom p1("1x^1y^1z^1");
	Polynom p2("5x^1y^1z^1");
	Polynom p3 = p1 - p2;

	EXPECT_EQ(-4, p3[0].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
}

TEST(polynom, CorrectlySubEmptyPolynom1) {
	Polynom p1("1x^1y^1z^1");
	Polynom p2;
	Polynom p3 = p1 - p2;

	EXPECT_EQ(1, p3[0].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
}

TEST(polynom, CorrectlySubEmptyPolynom2) {
	Polynom p1;
	Polynom p2("1x^1y^1z^1");
	Polynom p3 = p1 - p2;

	EXPECT_EQ(-1, p3[0].getCoef());
	EXPECT_EQ(111, p3[0].getPower());
}

TEST(polynom, CorrectlyMulPolynoms) {
	Polynom p1("2x^1y^1z^1");
	Polynom p2("5x^1y^5z^2");
	Polynom p3 = p1 * p2;

	EXPECT_EQ(10, p3[0].getCoef());
	EXPECT_EQ(263, p3[0].getPower());
}

TEST(polynom, CorrectlyMulEmptyPolynom1) {
	Polynom p1("1x^1y^1z^1");
	Polynom p2;
	Polynom p3 = p1 * p2;

	EXPECT_EQ(0, p3[0].getCoef());
}

TEST(polynom, CorrectlyMulEmptyPolynom2) {
	Polynom p1;
	Polynom p2("1x^1y^1z^1");
	Polynom p3 = p1 * p2;

	EXPECT_EQ(0, p3[0].getCoef());
}

TEST(polynom, CorrectlyAddingMonomsAfterMultiplying) {
	Polynom p1("2x^1y^2z^3+5x^4y^4z^4");
	Polynom p2("3x^3y^2z^1+6x^0y^0z^0");
	Polynom p3 = p1 * p2;

	EXPECT_EQ(12, p3[0].getCoef());
	EXPECT_EQ(123, p3[0].getPower());
	EXPECT_EQ(36, p3[1].getCoef());
	EXPECT_EQ(444, p3[1].getPower());
	EXPECT_EQ(15, p3[2].getCoef());
	EXPECT_EQ(765, p3[2].getPower());

}

TEST(polynom, MonomsWithSameDegGetAdded) {
	Polynom p("x^1y^1z^1+4x^1y^1z^1");
	EXPECT_EQ(5, p[0].getCoef());
	EXPECT_EQ(111, p[0].getPower());
}

TEST(polynom, DegreesCantBeMoreThan9WhenMul) {
	Polynom p1("2x^9y^9z^9");
	Polynom p2("5x^0y^1z^0");

	ASSERT_ANY_THROW(Polynom p3 = p1 * p2);
}