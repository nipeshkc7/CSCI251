#include <iostream>
using namespace std;

	enum Month {
	Jan, Feb, Mar, Apr, May, Jun ,July, Aug, Sep, Oct, Nov, Dec};
	int monthNum;
	Month Mth;
	void GetMonth(Month &Mth);
	void PrintMonth(Month Mth);
	
	
int main(){ 
	cout<<"Enter a number between 1 to 12\n";
	cin>> monthNum;	
	GetMonth(Mth);
	PrintMonth(Mth);
	return 0;	
}

void GetMonth(Month &Mth){
	Mth= Month(monthNum);
}

void PrintMonth(Month Mth){
	
	switch(Mth){
		case 1: cout<<"Jan"; break;
		case 2: cout<<"Feb"; break;
		case 3: cout<<"Mar"; break;
		case 4: cout<<"Apr"; break;
		case 5: cout<<"May"; break;
		case 6: cout<<"Jun"; break;
		case 7: cout<<"Jul"; break;
		case 8: cout<<"Aug"; break;
		case 9: cout<<"Sep"; break;
		case 10: cout<<"Oct"; break;
		case 11: cout<<"Nov"; break;
		case 12: cout<<"Dec"; break;
	}
		
}
