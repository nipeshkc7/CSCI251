/**********************************************************************
 * main.cpp - CSCI251/851 - Ass4- main() tester for class BillSystem
 * <Your name> <your login> <date last modified>
 **********************************************************************/
#include <iostream>
#include <iomanip>
#include "BillSystem.h"
using namespace std;
 
char Menu();

int main(){

	BillSystem BS;

	cout << "Begin tests for BillSystem\n\n";

	if(!BS.ReadFile("usage.txt")){
		cout << "File not found!\n\n";
		exit(1);
	}
	int n = BS.GetNumRecs();

	cout << "Num records read: " << n << endl << endl;
	
	

	cout<<setw(3)<< "#" << setw(15)<< "Bill Type" << setw(10) << "Supplier" <<setw(15)<< "Name" << setw(25)<< "Address" << setw(25)<< "Account Balance" << setw(10)<< "Days"<<endl<<endl;
	for(int i=0; i<n && i<5; i++){
		BS.DisplayRec(i);
		cout << endl;
	}
	
	BS.CalDiscounts(); // uncoment when step 3 complete
	
	BS.CalBills();     // uncoment when step 4 complete
	BS.PrintReport();  // uncoment when step 4 complete

	cout << endl << "End tests for BillSystem\n";

	return 0;
}

