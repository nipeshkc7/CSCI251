/**********************************************************************
 * BillSystem.cpp - CSCI251/851 - Ass4 - BillSystem class definition
 * <Your name> <your login> <date last modified>
 **********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include "BillSystem.h"
#include <vector>
#include <map>
using namespace std;


// ========== class BillSystem Public Function definitions ==========

// Destructor
BillSystem::~BillSystem()
{
	//Iterate BRecs vector and delete each ptr
	
	for(vector <BillRecord*>:: iterator it = BRecs.begin(); it != BRecs.end(); it++ ) {
		delete *it;
	}
}

// Reads data in "usage.txt" into BRecs vector
bool BillSystem::ReadFile(char *fname)
{
	ifstream fin;
	fin.open(fname);
	if(!fin.good()){
		cout<<"File not found ..\n";
		return 0;
	}
	
	while(!fin.eof()){
		BillRecord *temp;
		string s;
		fin>> s;
		if(fin.fail())
			break;
		
		if(s.compare("Elect")==0){temp= new ElectBillRecord;}
		if(s.compare("Phone")==0){temp= new PhoneBillRecord;}
		if(s.compare("Gas")==0){temp= new GasBillRecord;}
		temp->setBillType(s); 
		if(!temp->ReadCustDetails(fin))
			break;
		if(!temp->ReadUsageInfo(fin))
			break;
		BRecs.push_back(temp);
	}
	
	fin.close();
	return true;
}

// Returns the number of records in BRecs
int BillSystem::GetNumRecs()
{
	return BRecs.size();
}

 // Displays ith record on screen
void BillSystem::DisplayRec(int i)
{
	BRecs[i]->DisplayCustDetails();
	cout<<endl;
	BRecs[i]->DisplayUsageInfo();
	cout<<endl;
}

void BillSystem::CalDiscounts() 
{
	multimap<string,BillRecord*> Users;
	
	for(vector <BillRecord*>:: iterator it = BRecs.begin(); it != BRecs.end(); it++ ) {
		BillRecord *br= *it;
		string concatInfo= br->getName() + br->getAddress() +br->getSupplier();
		Users.insert(Users.begin(),pair<string,BillRecord*>(concatInfo,br));
	}
	int dodoDiscounts=0;
	int alintaDiscounts=0;
	for(multimap <string,BillRecord*>:: iterator it = Users.begin(); it != Users.end(); it++ ) {
		string userDetails= it->first;
		
		if(Users.count(userDetails)==3){
			BillRecord *br= it->second;
			string Supplier=br->getSupplier();
			if(Supplier.compare("Dodo")==0){
				br->SetDiscount(0.85);
				dodoDiscounts++;
			}
			
			if(Supplier.compare("Alinta")==0){
				br->SetDiscount(0.80);
				alintaDiscounts++;
			}
		}	
	}
	
	cout<<"number of Dodo Discounts::"<<dodoDiscounts/3<<endl;
	cout<<"number of Alinta Discounts::"<<alintaDiscounts/3<<endl;	
	cout<<endl<<endl;
}

void BillSystem::CalBills(){
	for(vector <BillRecord*>:: iterator it = BRecs.begin(); it != BRecs.end(); it++ ) {
		BillRecord *br= *it;
		br->UpdateBalance();
	}		
}
void BillSystem::PrintReport(){
	int i=0;
	
	map <string,string> discountCustomers;
	cout<<setw(10)<< "#" << setw(20)<< "Bill Type" << setw(20) << "Supplier" <<setw(20)<< "Name" << setw(25)<< "Address" << setw(25)<< "Bill Amount"<<endl<<endl;
	for(vector <BillRecord*>:: iterator it = BRecs.begin(); i<5; it++,i++ ) {
		BillRecord *br= *it;
		br->DisplayUpdatedDetails();
		cout<<endl;
	}
	
	//Displaying discounted customers
	for(vector <BillRecord*>:: iterator it = BRecs.begin(); it!=BRecs.end(); it++ ) {
		BillRecord *br= *it;
		if(br->hasDiscount())
			discountCustomers.insert(discountCustomers.begin(),pair<string,string>(br->getName(),br->getSupplier()));
	}
	
	cout<<"\nDiscounted customers:: "<<discountCustomers.size()<<"\n\n";
	for(map<string,string>:: iterator it=discountCustomers.begin();it!=discountCustomers.end();it++){
		cout<< it->first<<" : "<<it->second<<endl;
	}
}

// ========== class BillSystem Private Function definitions ==========

