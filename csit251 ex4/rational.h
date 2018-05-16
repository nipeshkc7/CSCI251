/*************************************************************************
 * CSCI251 Ex4 - rational.h: Declaration of Rational class
 * <Student Name>, <login>, <date completed>
 *************************************************************************/
#ifndef _RATIONAL_H_
#define _RATIONAL_H_
#include <iostream>
using namespace std;

//int STDCONSTERROR_FLAG=1,DIVIDEBYZERO_FLAG=2,DIVIDEBYZERORATIONAL_FLAG=3;
class Rational {
  public:
	Rational();  // default constructor
	Rational(int, int); //std (initialisation) constructor
	Rational(int); //Only for testing purposes
	Rational(const Rational&); //copy constructor
	Rational addition(const Rational &);
	Rational subtraction(const Rational &);
	Rational multiplication(const Rational &);
	Rational division(Rational &);
	void printRational();
	void static getCount();
	bool isDenominatorZero();
		
	friend void printRationalAsFloating(const Rational &r);

  private:
	int numerator;
	int denominator;
	static int Count;
};


void printRationalAsFloating(const Rational &r);


#endif
