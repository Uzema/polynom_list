#ifndef __POLYNOM_H__
#define __POLYNOM_H__

#include "list.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

enum class State {
	S0,
	Q1,
	Q2,
	Q3,
	Q4,
	Q5,
	Q6,
	Q7,
	Q8,
	Q9,
	X,
	Y,
	Z,
	ERROR
};

class Monom {

	double coef;
	int power;

public:

	Monom() {
		coef = 0;
		power = 0;
	}

	Monom(double coef1, int power1) {
		this->coef = coef1;
		this->power = power1;
	}

	double getCoef() {
		return coef;
	}

	int getPower() {
		return power;
	}

	int getPowerX() {
		return power / 100;
	}
	
	int getPowerY() {
		return (power / 10) % 10;
	}
	
	int getPowerZ() {
		return power % 10;
	}

	Monom operator+(Monom m) {
		if (this->getPower() != m.getPower()) {
			throw "different degrees";
		}
		return Monom(this->coef + m.coef, power);
	}

	Monom& operator+=(const Monom& m) {
		if (this->power != m.power) {
			throw "Degree are different";
		}
		coef += m.coef;
		return *this;
	}
};

class Polynom {

	List<Monom> polynom;

public:

	Polynom() {
		List<Monom> polynom;
	}

	Polynom(string str) {
		bool isCorrect = stringAnalyze(str);
		if (!isCorrect) {
			throw "incorrect string";
		}
	}

	Polynom(Monom m) {
		polynom.insert_front(m);
	}

	void insert(double newCoef, int newDeg) {
		Monom m(newCoef, newDeg);
		List<Monom>::iterator it = polynom.begin();

		if (polynom.begin() == polynom.end() || newDeg < it->getPower()) {
			polynom.insert_front(Monom(newCoef, newDeg));
		}
		else if (newDeg == it->getPower()) {
			*it = *it + m;
			return;
		}
		else {
			List<Monom>::iterator prev(nullptr);
			while (it != polynom.end() && newDeg > it->getPower()) {
				prev = it;
				++it;
			}
			if (prev != List<Monom>::iterator(nullptr)) {
				polynom.insert(Monom(newCoef, newDeg), prev.getNode());
			}
		}
	}

	Monom operator[](int index) {
		return polynom[index];
	}

	bool stringAnalyze(string givenStr) {
		if (givenStr.size() == 0) {
			throw "empty string";
		}

		State ka = State::S0;
		string strCoef;
		string strDeg;

		for (int i = 0; i < givenStr.size(); i++) {

			switch (ka) {

				case State::S0:
					if (givenStr[i] == '+' || givenStr[i] == '-') {
						ka = State::Q1;
						strCoef = "";
						strDeg = "";
						strCoef += givenStr[i];
					}
					else if (givenStr[i] >= '0' && givenStr[i] <= '9') {
						ka = State::Q2;
						strCoef += givenStr[i];
					}
					else if (givenStr[i] == 'x' || givenStr[i] == 'X') {
						ka = State::X;
						strCoef = '1';
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q1:
					if (givenStr[i] >= '0' && givenStr[i] <= '9') {
						ka = State::Q2;
						strCoef += givenStr[i];
					}
					else if (givenStr[i] == 'x' || givenStr[i] == 'X') {
						ka = State::X;
						strCoef += '1';
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q2:
					if (givenStr[i] >= '0' && givenStr[i] <= '9') {
						ka = State::Q2;
						strCoef += givenStr[i];
					}
					else if (givenStr[i] == '.') {
						ka = State::Q3;
						strCoef += givenStr[i];
					}
					else if (givenStr[i] == 'x' || givenStr[i] == 'X') {
						ka = State::X;
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q3:
					if (givenStr[i] >= '0' && givenStr[i] <= '9') {
						ka = State::Q3;
						strCoef += givenStr[i];
					}
					else if (givenStr[i] == 'x' || givenStr[i] == 'X') {
						ka = State::X;
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::X:
					if (givenStr[i] == '^') {
						ka = State::Q4;
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q4:
					if (givenStr[i] >= '0' && givenStr[i] <= '9') {
						ka = State::Q5;
						strDeg += givenStr[i];
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q5:
					if (givenStr[i] == 'y' || givenStr[i] == 'Y') {
						ka = State::Y;
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Y:
					if (givenStr[i] == '^') {
						ka = State::Q6;
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q6:
					if (givenStr[i] >= '0' && givenStr[i] <= '9') {
						ka = State::Q7;
						strDeg += givenStr[i];
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q7:
					if (givenStr[i] == 'z' || givenStr[i] == 'Z') {
						ka = State::Z;
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Z:
					if (givenStr[i] == '^') {
						ka = State::Q8;
					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q8:
					if (givenStr[i] >= '0' && givenStr[i] <= '9') {
						ka = State::Q9;
						strDeg += givenStr[i];

						List<Monom>::iterator it = polynom.begin();
						double newDeg = stod(strDeg);
						double newCoef = stod(strCoef);
						Monom m(newCoef, newDeg);

						if (polynom.begin() == polynom.end() || newDeg < it->getPower()) {
							polynom.insert_front(Monom(newCoef, newDeg));
						}
						else if (newDeg == it->getPower()) {
							*it = *it + m;
						}
						else {
							List<Monom>::iterator prev(nullptr);
							while (it != polynom.end() && newDeg >= it->getPower()) {
								prev = it;
								++it;
							}

							if (prev != List<Monom>::iterator(nullptr)) {
								polynom.insert(Monom(newCoef, newDeg), prev.getNode());
							}
						}

					}
					else {
						ka = State::ERROR;
					}
					break;

				case State::Q9:
					if (givenStr[i] == '+' || givenStr[i] == '-') {
						ka = State::Q1;
						strCoef = "";
						strDeg = "";
						strCoef += givenStr[i];
					}
					else {
						ka = State::ERROR;
					}
					break;
				
				case State::ERROR:
					break;

				default: ka = State::ERROR;
					break;
			}

		}//for
		return (ka == State::Q9);
	}

	Polynom operator+(Polynom other) {

		Polynom result;

		List<Monom>::iterator it = result.polynom.begin();
		List<Monom>::iterator it1 = polynom.begin();
		List<Monom>::iterator it2 = other.polynom.begin();
		while ((it1 != polynom.end()) || (it2 != other.polynom.end())) {
			if ((it1 != polynom.end()) && (it2 == other.polynom.end())) {
				if (result.polynom.begin() == result.polynom.end()) {
					it = List<Monom>::iterator(result.polynom.insert_front(Monom(it1->getCoef(), it1->getPower())));
					it1++;
				}
				while (it1 != polynom.end()) {
					result.polynom.insert(Monom(it1->getCoef(), it1->getPower()), it.getNode());
					it++;
					it1++;
				}
			}
			else if ((it1 == polynom.end()) && (it2 != other.polynom.end())) {
				if (result.polynom.begin() == result.polynom.end()) {
					it = List<Monom>::iterator(result.polynom.insert_front(Monom(it2->getCoef(), it2->getPower())));
					it2++;
				}
				while (it2 != polynom.end()) {
					result.polynom.insert(Monom(it2->getCoef(), it2->getPower()), it.getNode());
					it++;
					it2++;
				}
			}
			else {
				if (it1->getPower() == it2->getPower()) {
					double resCoef = it1->getCoef() + it2->getCoef();
					if (result.polynom.begin() == result.polynom.end()) {
						it = List<Monom>::iterator(result.polynom.insert_front(Monom(resCoef, it1->getPower())));
						it1++;
						it2++;
					}
					else {
						result.polynom.insert(Monom(resCoef, it1->getPower()), it.getNode());
						it1++;
						it2++;
						it++;
					}

				}
				else if (it1->getPower() < it2->getPower()) {
					if (result.polynom.begin() == result.polynom.end()) {
						 it = List<Monom>::iterator(result.polynom.insert_front(Monom(it1->getCoef(), it1->getPower())));
						it1++;
					}
					else {
						result.polynom.insert(Monom(it1->getCoef(), it1->getPower()), it.getNode());
						it1++;
						it++;
					}
				}
				else {
					if (result.polynom.begin() == result.polynom.end()) {
						it = List<Monom>::iterator(result.polynom.insert_front(Monom(it2->getCoef(), it2->getPower())));
						it2++;
					}
					else {
						result.polynom.insert(Monom(it2->getCoef(), it2->getPower()), it.getNode());
						it2++;
						it++;
					}
				}
			}
		}
		return result;
	}

	Polynom operator-(Polynom other) {

		Polynom result;

		List<Monom>::iterator it = result.polynom.begin();
		List<Monom>::iterator it1 = polynom.begin();
		List<Monom>::iterator it2 = other.polynom.begin();
		while ((it1 != polynom.end()) || (it2 != other.polynom.end())) {
			if ((it1 != polynom.end()) && (it2 == other.polynom.end())) {
				if (result.polynom.begin() == result.polynom.end()) {
					it = List<Monom>::iterator(result.polynom.insert_front(Monom(it1->getCoef(), it1->getPower())));
					it1++;
				}
				while (it1 != polynom.end()) {
					result.polynom.insert(Monom(it1->getCoef(), it1->getPower()), it.getNode());
					it++;
					it1++;
				}
			}
			else if ((it1 == polynom.end()) && (it2 != other.polynom.end())) {
				if (result.polynom.begin() == result.polynom.end()) {
					it = List<Monom>::iterator(result.polynom.insert_front(Monom(-(it2->getCoef()), it2->getPower())));
					it2++;
				}
				while (it2 != polynom.end()) {
					result.polynom.insert(Monom(-(it2->getCoef()), it2->getPower()), it.getNode());
					it++;
					it2++;
				}
			}
			else {
				if (it1->getPower() == it2->getPower()) {
					double resCoef = it1->getCoef() - it2->getCoef();
					if (result.polynom.begin() == result.polynom.end()) {
						it = List<Monom>::iterator(result.polynom.insert_front(Monom(resCoef, it1->getPower())));
						it1++;
						it2++;
					}
					else {
						result.polynom.insert(Monom(resCoef, it1->getPower()), it.getNode());
						it1++;
						it2++;
						it++;
					}
				}
				else if (it1->getPower() < it2->getPower()) {
					if (result.polynom.begin() == result.polynom.end()) {
						it = List<Monom>::iterator(result.polynom.insert_front(Monom(it1->getCoef(), it1->getPower())));
						it1++;
					}
					else {
						result.polynom.insert(Monom(it1->getCoef(), it1->getPower()), it.getNode());
						it1++;
						it++;
					}
				}
				else {
					if (result.polynom.begin() == result.polynom.end()) {
						it = List<Monom>::iterator(result.polynom.insert_front(Monom(-(it2->getCoef()), it2->getPower())));
						it2++;
					}
					else {
						result.polynom.insert(Monom(-(it2->getCoef()), it2->getPower()), it.getNode());
						it2++;
						it++;
					}
				}
			}
		}
		return result;
	}

	Polynom operator*(Monom monom) {
		Polynom result;
		List<Monom>::iterator it = result.polynom.begin();
		for (List<Monom>::iterator it1 = polynom.begin(); it1 != polynom.end(); ++it1) {

			if (it1->getPowerX() + monom.getPowerX() > 9 ||
				it1->getPowerY() + monom.getPowerY() > 9 ||
				it1->getPowerZ() + monom.getPowerZ() > 9) {
				throw "Degree cant exceed 9";
			}

			if (result.polynom.begin() == result.polynom.end()) {
				it = List<Monom>::iterator(result.polynom.insert_front(Monom(it1->getCoef() * monom.getCoef(), it1->getPower() + monom.getPower())));
			}
			else {
				result.polynom.insert(Monom(it1->getCoef() * monom.getCoef(), it1->getPower() + monom.getPower()), it.getNode());
			}
		}
		return result;
	}

	Polynom operator*(Polynom other) {
		Polynom result;
		if (this->polynom.size() == 0 || other.polynom.size() == 0) {
			result.insert(0, 0);
			return result;
		}
		for (int i = 0; i < other.polynom.size(); i++) {
			result = result + (*this * other[i]);
		}
		return result;
	}
};

#endif