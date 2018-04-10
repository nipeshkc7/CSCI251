/**********************************************
* CardSet.cpp - Contains implementation of class CardSet
* <name, studNo, login, date completed, etc>
***********************************************/

#include <iostream>
#include "CardSet.h"
using namespace std;

CardSet::CardSet()
{
	//this is the default constructor which sets up a set of 0 cards
	nCards=0;
	Card=NULL;
}

CardSet::CardSet(int x)
{
	//this is the initialising constructor which sets up a set of x cards not more than 51
	nCards=x;
	int i;
	Card= new int[nCards];
	for(i=0;i<nCards;i++){
		&(Card+i)=i%52; 
		//Card++;
	}	
}


CardSet::~CardSet()
{
	delete []card;
	//this is the destructor to clean up dynamic memory used
}

int CardSet::Size() const
{
	//Returns the value of nCards
	return nCards;
} 

void CardSet::PrintCard(int c) const
{
	// Private function to print out usual representation of playing card.
	// Input is integer from 0 to 51.  There is no error checking.
	int Rank = c%13;
	int Suit = c/13;
	const char NameSuit[5] = "SCDH";
	const char NameRank[14] = "23456789XJQKA";
	cout << NameRank[Rank] << NameSuit[Suit];
}
