/*************************************************************************
 * CSCI124 Ex4 - rational.cpp: Implementation file for Rational Class
 * <Student Name>, <login>, <date completed>
 *************************************************************************/
#include <iostream>
#include "rational.h"
using namespace std;


int Rational::Count=0;
Rational::Rational() 
{
   numerator = 1;
   denominator = 1;
   Count++;
}

Rational::Rational(int numr,int den)
{
	numerator=numr;
	denominator=den;
	if (denominator==0)
		throw string("\nERROR: Denominator is assigned zero \n");
	Count++;
}

//This Constructor is for testing purposes
Rational::Rational(int numr)
{
	numerator=numr;
	denominator=0;
	if (denominator==0)
		throw string("\nERROR: Denominator is assigned zero \n");
	Count++;
}

Rational::Rational(const Rational& R)
{
	numerator=R.numerator;
	denominator=R.denominator;
	Count++;
}

Rational Rational::addition(const Rational& R)
{
	Rational sum;
	sum.numerator=(numerator*R.denominator + denominator*R.numerator);
	sum.denominator=(denominator * R.denominator);
	return sum;
}

Rational Rational::subtraction(const Rational& R)
{
	Rational difference;
	difference.numerator=(numerator*R.denominator- denominator*R.numerator);
	difference.denominator=( denominator *R.denominator);
	return difference;
	
}

Rational Rational::division(Rational& R)
{
	if (R.numerator==0)
		throw string("\nERROR: Division attempts to divide Rational with a Zero Rational \n");
	Rational div;
	div.numerator=numerator*R.denominator;
	div.denominator=denominator*R.numerator;
	return div; 
}


Rational Rational::multiplication(const Rational& R)
{
	Rational mul;
	mul.numerator=numerator*R.numerator;
	mul.denominator=denominator*R.denominator;
	return mul;
}

void Rational::printRational(){
	cout<< numerator<<"/"<<denominator;
}


void Rational::getCount(){		//For accessing Count variable
	cout<<endl<< "Count is :" << Count;
}

bool Rational::isDenominatorZero(){
	return denominator==0;
}

void printRationalAsFloating(const Rational &r)
{
	if(r.denominator==0)
		throw string("\nERROR: Attempt to divide by zero \n");
	cout<<r.numerator<<" / "<<r.denominator<<" = " <<float(r.numerator)/float(r.denominator) <<endl<<endl;
}
