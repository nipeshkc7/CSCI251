/*********************************************************************
 * CSCI251/851 - Exercise 3
 * list.cpp - Implementation of LinkedList class.
 * Arpan KC, akc992 and April 27, 2018.
 *
 *********************************************************************/

#include <iostream>
#include "list.h"
using namespace std;

// Default constructor
LinkedList::LinkedList()
{
	Head= NULL;
}

//Copy constructor for a deep copy
LinkedList::LinkedList(const LinkedList &obj){
	Head=NULL;
	LinkedList tempList;
	NodePtr crnt=obj.Head;
	
	while(crnt!=NULL){
		tempList.AddHead(crnt->Item);
		crnt=crnt->Next;
	}
	
	while(!tempList.IsEmpty()){
		int item=tempList.RemoveHead();
		AddHead(item);
	}
	
}

LinkedList& LinkedList::operator=(const LinkedList& obj){
	
	//First emptying the list
	while(Head!=NULL){
		RemoveHead();
	}	

	LinkedList tempList;
	NodePtr crnt=obj.Head;
	while(crnt!=NULL){
		tempList.AddHead(crnt->Item);
		crnt=crnt->Next;
	}
	
	while(!tempList.IsEmpty()){
		int item=tempList.RemoveHead();
		AddHead(item);
	}	
	
	return *this;
}

// Destructor
LinkedList::~LinkedList()
{
	NodePtr tmp;
	while( Head!=NULL){
		tmp=Head;
		Head=Head->Next;
		delete []tmp;
	}
}

// Adds item to head of list
void LinkedList::AddHead(int Item)
{ 
	NodePtr newNode;
	newNode=new Node;
	newNode->Item=Item;
	newNode->Next=Head;
	Head= newNode;
}

// Removes head node and returns item
int LinkedList::RemoveHead()
{
	if(IsEmpty()){
		cout<<"\n ERROR \n EXITING PROGRAM ...\n";
		exit(1);
	}
	int Item= Head->Item;
	NodePtr tempPtr=Head;
	Head=Head->Next;
	delete []tempPtr;
	
	return Item;
}

// Returns true if list is empty
bool LinkedList::IsEmpty()
{
	return Head==NULL;
}


// Prints contents of linked list
void LinkedList::Print()
{
	if(IsEmpty()){
		cout<<"empty\n";
		return;
	}
	
	NodePtr crntPtr=Head;
	while(crntPtr!=NULL){
		cout<< crntPtr->Item << " ";
		crntPtr=crntPtr->Next;
	}
	cout<<endl;
}


