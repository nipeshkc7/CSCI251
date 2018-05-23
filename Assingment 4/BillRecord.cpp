/**********************************************************************
 * BillRecord.cpp - CSCI251/851 - Ass5 - BillRecord class definition
 * <Your name> <your login> <date last modified>
 **********************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include "BillRecord.h"
using namespace std;

// ========== class BillRecord function definitions ==========

// Default constructor
BillRecord::BillRecord()
{
	//Set discount here
	Discount=1;
	 
}

bool BillRecord::hasDiscount(){
	return Discount!=1;
}

// Reads customer details part of record from file
bool BillRecord::ReadCustDetails(ifstream &fin)
{
	//put code here for reading the customer details part of file record only into the private data members
//	string BlType;
	//fin.ignore(200,'\n');
	//cout<<endl;
	
	getline(fin,Supplier);
	getline(fin,Name);
	getline(fin,Address);
	fin>>AccountBalance;
//	fin.ignore(200,'\n');
	fin>>DaysSinceLastReading;
	//fin.ignore(200,'\n');
	return true;	
}

// Displays customer details part of record on screen
void BillRecord::DisplayCustDetails()
{
	//display customer details (only) from private data members
	string BlType;
	switch(BType){
		case ePhone:
			BlType="Phone";
			break;
		case eGas:
			BlType="Gas";
			break;
		case eElect:
			BlType="Electricity";
			break;
	}
	cout<<setw(3)<< "#" << setw(15)<< BlType << setw(10) << Supplier <<setw(15)<< Name << setw(25)<< Address << setw(25)<< AccountBalance << setw(10)<< DaysSinceLastReading;
}

void BillRecord::DisplayUpdatedDetails(){
	string BlType;
	switch(BType){
		case ePhone:
			BlType="Phone";
			break;
		case eGas:
			BlType="Gas";
			break;
		case eElect:
			BlType="Electricity";
			break;
	}
	cout<<setw(10)<< "#" << setw(20)<< BlType << setw(20) << Supplier <<setw(20)<< Name << setw(25)<< Address << setw(25)<< BillAmount<<setw(5)<<Discount;
	
}


// Virtual fn for reading usage info part of record from file in derived classes
bool BillRecord::ReadUsageInfo(ifstream &fin)
{
	//the code here should jusy test BillType and read (eat) the usage info from file and discard it
	int skipAmount=0;
	if(BType==ePhone || BType==eGas){
		skipAmount=4;
	}
	if(BType==eElect){
		skipAmount=5;
	}
	float skip;
	for(int i=0;i<skipAmount;i++){
		fin>>skip;
		fin.ignore(200,'\n');
	}
	return true;
}


// virtual fn for displays usage info part of record in derived classes
void BillRecord::DisplayUsageInfo()
{
	// does nothing - later we will override this fn to display the appropriate billing info in the derived classes
}

void BillRecord::SetDiscount(float d)
{
	Discount=d;
}

string BillRecord::getAddress(){
	return Address;
}
string BillRecord::getName(){
	return Name;
}
string BillRecord::getSupplier(){
	return Supplier;
}

void BillRecord::setBillType(string s){
	if(s.compare("Gas")==0)
		BType=eGas;
	if(s.compare("Elect")==0)
		BType=eElect;
	if(s.compare("Phone")==0)
		BType=ePhone;
}

// ========== Derived Class function definitions ==========


// write the function definitions of the derived classes here

bool ElectBillRecord::ReadUsageInfo(ifstream &fin)
{
	fin>>PreviousReading;
	fin>>CurrentReading;
	fin>>Rate1;
	fin>>Rate1ThresHold;
	fin>>Rate2;
	fin>>SupplyCharge;
	fin.ignore(200,'\n');
	return true;
}
void ElectBillRecord::DisplayUsageInfo()
{	
	cout<<"("<<"PR: "<< PreviousReading<<" CR: "<<CurrentReading<< " Rate1: "<< Rate1 <<" Rate1TH: "<< Rate1ThresHold<< " SC: "<<SupplyCharge<<")"<<endl;
}

void ElectBillRecord::UpdateBalance(){
	float C=CurrentReading-PreviousReading;
	float P= SupplyCharge * DaysSinceLastReading;
	if (C<=Rate1ThresHold)	
		BillAmount=(Rate1ThresHold * Rate1 + (C-Rate1ThresHold)*Rate2+P) *Discount-AccountBalance;
	else
		BillAmount=(Rate1ThresHold *Rate1 +(C-Rate1ThresHold)*Rate2+P)* Discount- AccountBalance;

	AccountBalance=0;
}
bool GasBillRecord::ReadUsageInfo(ifstream &fin)
{
	fin>>PreviousReading;
	fin>>CurrentReading;
	fin>>HeatingValue;
	fin>>Rate;
	fin>>SupplyCharge;
	fin.ignore(200,'\n');
	return true;
}

void GasBillRecord::DisplayUsageInfo()
{
	cout<<"("<<"PR: "<< PreviousReading<<" CR: "<<CurrentReading<< " HeatingValue: "<< HeatingValue <<" Rate: "<< Rate<< " SC: "<<SupplyCharge<<")"<<endl; 
}


void GasBillRecord::UpdateBalance(){
	float C=CurrentReading-PreviousReading;
	float P= SupplyCharge * DaysSinceLastReading;
	BillAmount=(C*HeatingValue * Rate) *Discount - AccountBalance;
	AccountBalance=0;
}

bool PhoneBillRecord::ReadUsageInfo(ifstream &fin)
{	
	fin>>NumberOfLocalCalls;
	fin>>LocalCallRate;
	fin>>LongDistCallTime;
	fin>>LongDistCallRate;
	fin>>Rental;
	fin.ignore(200,'\n');
	return true;
}

void PhoneBillRecord::DisplayUsageInfo()
{
	cout<<"("<<"NL: "<< NumberOfLocalCalls<<" CR: "<<LocalCallRate<< " CT: "<< LongDistCallTime <<" Rate: "<< LongDistCallRate<< " Rental: "<<Rental<<")"<<endl;
}


void PhoneBillRecord::UpdateBalance(){
	float L=LocalCallRate*NumberOfLocalCalls;
	float D=LongDistCallRate *LongDistCallTime;
	float P=Rental * DaysSinceLastReading;
	BillAmount=(L+D+P)* Discount - AccountBalance;
	AccountBalance=0;
}

