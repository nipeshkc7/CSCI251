/********************************************************************

 * CSCI251 - Ex2

 * <Arpan Kc - akc992>

 * ex2.cpp 

 ********************************************************************/
#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

// ============= User Defined types ==================================

// linked list record
struct PhoneRecord{
	long PhoneNo;
	char *Name;//char Name[20];
	char *Address;//char Address[40];
	PhoneRecord *Next; // pointer to next record in list
};


// ============= Global Data =========================================

const char cDataFileName[] = "phone.txt";
PhoneRecord *Head; // head of linked list


// ============= Function Prototypes =========================

void Initialise();
void ReadFile();
void AddRecord(long PhoneNo,char *Name,char *Address);
void FindRecord();
void RemoveRecord();
void DisplayAllRecs();
void DisplayRec(PhoneRecord *Rec);
void DeleteList();


// ============= Main Function ================================

int main(){
	cout << "Begin test" << endl << endl;
	Initialise();
	ReadFile();
	DisplayAllRecs();

	FindRecord();
	RemoveRecord();
	FindRecord();
	DeleteList();
	cout << endl << "End test" << endl;
	return 0;
}

// ============= Function Definitions =========================

//Initialises linked list
void Initialise(){
	Head = NULL;
}

// Reads data file into linked list
void ReadFile(){

	ifstream fin;
	int counter=0;
	long PhoneNo;
	char Name[20];
	char Address[40];
	fin.open(cDataFileName);
	if(!fin.good()){cout<<"Cannot open file"; exit(1);}
	
	while(!fin.eof()){
		//fin>>PhoneNo;
		if(!(fin>>PhoneNo)){
			break;
		}
		fin.ignore(200,'\n');	
		fin.getline(Name,20);
		fin.getline(Address,40);
		//cout<<PhnRcd.Name<<endl<<PhnRcd.Address<<endl<<PhnRcd.PhoneNo<<endl;
		counter++;
		AddRecord(PhoneNo,Name,Address);  //to the list
	}
	fin.close();
	cout<<counter <<" records read\n";  //TO:DO Count no of records
}


// Adds record to tail of linked list
void AddRecord(long PhoneNo, char *Name, char *Address){

	
	PhoneRecord *Tmp;
   	Tmp=new PhoneRecord;
   	Tmp->PhoneNo=PhoneNo;
   	Tmp->Name=new char[strlen(Name)+1];
   	Tmp->Address=new char[strlen(Address)+1];
	strcpy(Tmp->Name,Name);
   	strcpy(Tmp->Address,Address);
   	Tmp->Next=NULL;
   	if(Head==NULL){
   		Head=Tmp;
	}else{
	   PhoneRecord *Crnt = Head;	
	   while(Crnt->Next!=NULL){
	   		Crnt=Crnt->Next;
	   		}
	   	Crnt->Next=Tmp;	
	   }
}

// Finds record in linked list and displays it
void FindRecord(){
	
	long PhoneNo;
	cout<<"Enter phone number to find: ";
	cin>>PhoneNo;
	PhoneRecord *Crnt=Head;      					
	while(Crnt!=NULL && Crnt->PhoneNo !=PhoneNo){
		Crnt=Crnt->Next;
	}
	if (Crnt!=NULL){
		DisplayRec(Crnt);
	}
	else{
		cout<<"\nRecord not found"<<endl;
	}
	
}

// Removes record from head of linked list
void RemoveRecord(){

	if(Head==NULL){ cout<<"List is empty";}
	else{
		cout<< "Head record removed:";
		DisplayRec(Head);
		PhoneRecord *Tmp=Head;
		Head=Head->Next;
		delete[] Tmp->Name;
		delete[] Tmp->Address;
		delete Tmp;
	}
}

// Prints all records on screen one at a time
void DisplayAllRecs(){
	char Ans;
	PhoneRecord *Crnt;
	Crnt = Head;
	while(Crnt!=NULL){
		DisplayRec(Crnt);
		cout<<"Display next record: ";
		cin>>Ans;
		if(Ans=='n') break;
		Crnt=Crnt->Next;
	}
	cout << endl;
}

// Displays record on screen
void DisplayRec(PhoneRecord *RecPtr){
	cout<<RecPtr->Name<<endl;
	cout<<RecPtr->Address<<endl;
	cout<<RecPtr->PhoneNo<<endl;
	cout<<endl;
}

// Deletes memory in list
void DeleteList(){

	PhoneRecord *Crnt=Head;
	while(Head!=NULL){
		PhoneRecord *Tmp = Head;
		Head=Head->Next;
		delete[] Tmp->Name;
		delete[] Tmp->Address;
		delete Tmp;
		
	}
	cout<<"List deleted";
}

