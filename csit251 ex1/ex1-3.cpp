#include <iostream>
using namespace std;

struct NameType{
	char lastName[20];
	char initial;
	char firstName[20];
};

enum GenderType{ eMale,eFemale };

struct AddressType{
	int number;
	char street[20];
	char suburb[20];
	int postcode;
};

struct StudentType{
	NameType Name;
	GenderType Gender;
	AddressType Address;
};

void GetStudentDetails(StudentType &st);
void PrintStudentDetails(StudentType st);


int main(){
	StudentType st;
	GetStudentDetails(st);
	PrintStudentDetails(st);
	return 0;
}

void GetStudentDetails(StudentType &st){
	int x;
	cout<<"Enter student details::\n";
	cout<<"FirstName\n";
	cin>>st.Name.firstName;
	
	cout<<"\nInitial\n";
	cin>>st.Name.initial;
	
	cout<<"\nLastName\n";
	cin>>st.Name.lastName;
	
	cout<<"\n Gender Type, 1 for male, 2 for female\n";
	cin>> x;
	
	switch(x)
		{case 1:
			st.Gender=eMale;
		 	break;
		 case 2:
		 	st.Gender=eFemale;
			 break;	
		}
		
	
	cout<<"\nAddress number\n";
	cin>>st.Address.number;
	
	cout<<"\nStreet\n";
	cin>>st.Address.street;
	
	cout<<"\nSuburb\n";
	cin>>st.Address.suburb;
	
	cout<<"\nPostCode\n";
	cin>>st.Address.postcode;
		
}

void PrintStudentDetails(StudentType st){
	cout <<"\n\n\n:::STUDENT DETAILS ARE AS FOLLOWS::::\n\n";
	cout <<"NAME: "<<st.Name.firstName << " " <<st.Name.initial << "" <<st.Name.lastName;
	cout<<"\nADDRESS: "<<st.Address.number <<" "<<st.Address.street <<","<<st.Address.suburb<<","<<st.Address.postcode<<"\n";
	switch(st.Gender){
		case eMale:
			cout<<"\nMale\n";
			break;
		case eFemale:
			cout<<"\nFemale\n";
			break;
	}
}
