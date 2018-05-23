/*************************************************************************
 * CSCI251 Ex4 - main1.cpp: A simple main to test the Rational class
 * <Student Name>, <login>, <date completed>
 *************************************************************************/
#include <iostream>
#include <cstring>
#include "rational.h"
using namespace std;



int main()
{
	cout << "Begin Rational Class Tests\n\n";
	for(int i=0;i<4;i++){
		try{
			int testDenominator=2;
			int testNumerator=1;
			
			int secondTestNumerator=1;
			int secondTestDenominator=1;
			switch(i){
				case 0:
					cout<<"----Normal test(No errors)----\n\n";
					break;
					
				case 1:
					cout<<"----Test1 (Test for denominator assigned zero)---- \n\n";
					testDenominator=0;
					break;
				
				case 2:
					cout<<"----Test2(Test for division with zero rational)----\n\n";
					testNumerator=0;
					break;
					
				case 3:
					cout<<"----Test3(Test for PrintRationalAsFloating attempts a divide by zero)----\n\n";
					Rational n5(1);
					printRationalAsFloating(n5);
					break;
				}			
			cout<<"Testing default constructor: ";
			Rational n1;
			n1.printRational();
			cout << endl << endl;
	
			cout<<"Testing std constructor: ";
		   	Rational n2(testNumerator,testDenominator);
			n2.printRational();
			cout << endl << endl;
		
			cout<<"Testing copy constructor: ";
		   	Rational n3(n2);
			n3.printRational();
			cout << endl << endl;
		
			cout<<"Testing addition: ";
			n1 = n2.addition(n3);
			n2.printRational();
			cout <<" + ";
			n3.printRational();
			cout <<" = ";
			n1.printRational();
			cout << endl << endl;
		
			cout<<"Testing subtraction: ";
			n1 = n2.subtraction(n3);
			n2.printRational();
			cout <<" - ";
			n3.printRational();
			cout <<" = ";
			n1.printRational();
			cout << endl << endl;
		
			cout<<"Testing multiplication: ";
			n1 = n2.multiplication(n3);
			n2.printRational();
			cout <<" * ";
			n3.printRational();
			cout <<" = ";
			n1.printRational();
			cout << endl << endl;
		
			cout<<"Testing division: ";
			n1 = n2.division(n3);
			n2.printRational();
			cout <<" / ";
			n3.printRational();
			cout <<" = ";
			n1.printRational();
			cout << endl << endl;
				
			cout<<"Print Rational As Floating :: \n\n";
			printRationalAsFloating(n1);
			printRationalAsFloating(n2);
			printRationalAsFloating(n3);
			
			//For test3
			//Rational n4(secondTestNumerator,secondTestDenominator);
			//printRationalAsFloating(n4);
	
			Rational::getCount();		//Accessing the static member function
			
			cout<<"\n\n";
		}
		catch(string &err){
			cout<<err<<endl;				
		}
	}
	cout << "End Rational Class Tests\n\n";		
	return 0;
}


