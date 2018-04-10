/**********************************************
* CardSet.cpp - Contains implementation of class CardSet
* <Arpan Kc, 5993568, akc992, April 11- 2018>
***********************************************/

#include <iostream>
#include <cstdlib>
#include "CardSet.h"
using namespace std;

CardSet::CardSet()
{
	//this is the default constructor which sets up a set of 0 cards
	nCards=0;
	Card=NULL;
}

CardSet::CardSet(int x)
{	//this is the initialising constructor which sets up a set of x cards not more than 51
	nCards=x;
	int i;
	Card= new int[nCards];
	for(i=0;i<nCards;i++){
		Card[i]=i%52; 		//Sets value inside Char as 0,1,2,3.....51,0,1,2....51 and so on
	}	
}


CardSet::~CardSet()
{	//this is the destructor to clean up dynamic memory used
	delete []Card;
}

int CardSet::Size() const
{
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
	cout << NameRank[Rank] << NameSuit[Suit] << " ";
}

void CardSet::Print() const
{
	int i=0;
	for(i=0;i<nCards;i++){
		PrintCard(Card[i]);		//sending the values inside 'Card' into the PrintCard Funcion 		
		if((i+1)%5==0){			//For line spacing after 5 items
			cout<<endl;
		}
		
	}
	cout<<"\n\n";
}

bool CardSet::IsEmpty() const
{
	if(nCards==0){
		return true;
	}else{
		return false;
	}
	
}

int CardSet::Deal()
{	
	if(IsEmpty()){
		cout<<"\n ERROR: Dealing an empty card" <<endl;
		exit(1);
	}
	int valueToReturn= Card[0];		
	int i;
	int *temp= new int[nCards-1];
	for(i=0;i<(nCards-1);i++){
		temp[i]=Card[i+1];
	}
	delete[] Card;
	Card=temp;	
	nCards--;
	return valueToReturn;
}

void CardSet::Deal(int numCardDealt,CardSet &Cardset1, CardSet &Cardset2)
{
	int i;
		if(nCards<numCardDealt*2){
		cout<<"\n The card doesn't have enough cards..\n";
		exit(1);
	}
	
	for(i=0;i<numCardDealt;i++){
		Cardset1.AddCard(Deal());
		Cardset2.AddCard(Deal());
	}
}

void CardSet::Deal(int numCardDealt,CardSet &Cardset1, CardSet &Cardset2, CardSet &Cardset3, CardSet &Cardset4)
{
	int i;
	
	if(nCards<numCardDealt*4){
		cout<<"\n The cardset doesn't have enough cards..\n";
		exit(1);
	}
	
	for(i=0;i<numCardDealt;i++){
		Cardset1.AddCard(Deal());
		Cardset2.AddCard(Deal());
		Cardset3.AddCard(Deal());
		Cardset4.AddCard(Deal());
	}
} 

void CardSet::AddCard(int CardValue)
{			
	int *temp= new int[nCards+1];
	int i;
	for(i=0;i<nCards;i++)
	{
		temp[i]=Card[i];
	}
	temp[nCards]=CardValue;			//Adding the card at the end
	delete[] Card;
	Card=temp;
	nCards++;
}



void CardSet::Shuffle()
{
	int temp;
	int i,j;
	for(i=0;i<nCards;i++){
		j= rand()%(nCards-1);		//random number from 0 to nCards-1
		
		if(i!=j){
			temp=Card[i];
			Card[i]=Card[j];
			Card[j]=temp;
			
		}
	}
}

void CardSet::MergeShuffle(CardSet &newCardSet)
{
	int *temp=new int[nCards+newCardSet.nCards];
	int i;
	
	for (i=0;i<nCards;i++){
		temp[i]=Card[i];
	}	
	
	
	//Merging the two Card arrays into a single temp array ::
	for(i=0;i<nCards;i++){
		temp[i]=Card[i];
	}
	for(i=nCards;i<(nCards+newCardSet.nCards);i++){
		temp[i]=newCardSet.Card[i-nCards];
	}

	delete [] Card;	
		
	
	Card= new int[nCards+ newCardSet.nCards];
	Card= temp;
	nCards=nCards+newCardSet.nCards;

	//Shuffling the Card array again:
	Shuffle();
	
	newCardSet.nCards=0;
	newCardSet.Card=NULL; // Emptying the argument cardset
	
}
