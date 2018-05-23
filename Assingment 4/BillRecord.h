/**********************************************************************
 * BillRecord.h - CSCI251/851 - Ass4 - BillRecord class declaration
 * <Your name> <your login> <date last modified>
 **********************************************************************/
#ifndef BILLRECORD_H
#define BILLRECORD_H

#include <string>
using namespace std;

enum BillType {eElect, eGas, ePhone };

// base class...

class BillRecord {
  public:
	BillRecord();
	bool ReadCustDetails(ifstream &fin);
	virtual bool ReadUsageInfo(ifstream &fin);
	void DisplayCustDetails();
	virtual void DisplayUsageInfo();
	void SetDiscount(float d);
	virtual void UpdateBalance()=0;
	void setBillType(string s);
	void DisplayUpdatedDetails();
	bool hasDiscount();
	//getters
	string getName();
	string getAddress();
	string getSupplier();

  private:
  	BillType BType;
	string Supplier; // Supplier's name
	string Name, Address; // Customer's name and address
	
  protected:
  		double AccountBalance; // Customer's account balance
		int DaysSinceLastReading; // Days since last reading
		float Discount;
		double BillAmount;// Amount in dollars and cents of this bill


};

class ElectBillRecord:public BillRecord{
	private:	
		int PreviousReading;
		int CurrentReading;
		double Rate1;
		int Rate1ThresHold;
		double Rate2;
		double SupplyCharge;
		
	public:
		bool ReadUsageInfo(ifstream &fin);
		void DisplayUsageInfo();
		void UpdateBalance();
};

class PhoneBillRecord:public BillRecord{
	private:
		int NumberOfLocalCalls;
		double LocalCallRate;
		int LongDistCallTime;
		double LongDistCallRate;
		double Rental;
	
	public:
		bool ReadUsageInfo(ifstream &fin);
		void DisplayUsageInfo();
		void UpdateBalance();
};

class GasBillRecord:public BillRecord{
	private:	
		int PreviousReading;
		int CurrentReading;
		double HeatingValue;
		double Rate;
		double SupplyCharge;
	
	public:
		bool ReadUsageInfo(ifstream &fin);
		void DisplayUsageInfo();
		void UpdateBalance();
			
};



#endif

