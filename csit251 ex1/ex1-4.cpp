#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;


struct NameType{
	
	char firstName[50];
	char lastName[50];
	char initial[50];
};

enum GenderType{ eMale,eFemale };

struct AddressType{
	int number;
	char street[50];
	char suburb[50];
	int postcode;
};

struct StudentType{
	NameType Name;
	GenderType Gender;
	AddressType Address;
};


void SaveStudentRecord(StudentType &StudentRec);
void LoadStudentRecord(StudentType &StudentRec);


int main(){
	StudentType StudentRec;
	
	//Start initializing values
	strncpy(StudentRec.Name.firstName,"Arpan",50);
	strncpy(StudentRec.Name.lastName,"KC",50);
	strncpy(StudentRec.Name.initial,"K",50);
	//StudentRec.Name.initial="K";
	StudentRec.Gender=eMale;
	StudentRec.Address.number=77;
	StudentRec.Address.postcode=2077;
	strncpy(StudentRec.Address.street,"Somerville Rd",50);
	strncpy(StudentRec.Address.suburb,"Hornsby Heights",50);
	//End initializing values
	
	SaveStudentRecord(StudentRec); //Saving student record
	LoadStudentRecord(StudentRec); //Retreiving and displaying student record
	
	return 0;
}

void SaveStudentRecord(StudentType &StudentRec){
		ofstream fout;
		
		fout.open("StudentRecord.txt");
		if(!fout.good()){
			cerr<<"File not found";
		}else{
				//fout<<StudentRec.id;
				//fout<<"\n";
				fout<<StudentRec.Name.firstName<<" "<<StudentRec.Name.initial<<" "<<StudentRec.Name.lastName<<endl;
				fout<<StudentRec.Address.number<<" "<<StudentRec.Address.street<<", "<<StudentRec.Address.suburb<<" "<<StudentRec.Address.postcode<<" "<<endl;
				
				switch(StudentRec.Gender){
					case eMale:
						fout<<"Male"<<endl;
						break;
						
					case eFemale:
						fout<<"Female"<<endl;
						break;
				}
		}
		
		fout.close();				
}

void LoadStudentRecord(StudentType &StudentRec){
		ifstream fin;
		string theOutput; 
		fin.open("StudentRecord.txt");
		if(!fin.good()){
			cerr<<"File not found";
		}else{
				cout<<"Contents of the file are:: \n\n";	
			while(getline(fin,theOutput) ){
				cout<<theOutput<<endl;
			}
	}
}
