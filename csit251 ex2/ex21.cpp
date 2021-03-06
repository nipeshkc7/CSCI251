// put your name etc here...

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
	FindRecord();
//	RemoveRecord();
//	FindRecord();
//	DisplayAllRecs();
//	DeleteList();
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
/*
	declare ifstream and open file in cDataFileName
	if( file does not open display file not found msg and exit
	while not eof
		read PhoneNo
		if read fails break while loop
		ignore (eat) end of line left over from fin>>PhoneNo
		read whole name with getline()
		read whole address with getline()
		AddRecord(PhoneNo,Name,Address); // to the list
	end while
	close the file
	display the number of records read from the file
*/
	ifstream fin;
	int counter=0;
	long PhoneNo;
	char Name[20];
	char Address[40];
	fin.open(cDataFileName);
	if(!fin.good()){cout<<"Cannot open file"; exit(1);}
	
	while(!fin.eof()){
		fin>>PhoneNo;
		//TO:DO :: if read fails break while loop
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
/*
	declare a Tmp PhoneRecord pointer
	allocate new PhoneRecord to Tmp ptr
	set Tmp->PhoneNo to PhoneNo;
	string copy Name into Tmp->Name
	string copy Address into Tmp->Address
	set Tmp->Next to NULL
	if Head is NULL set Head = Tmp;
	else{
		declare PhoneRecord *Crnt and set to Head;
		while Crnt->Next is not NULL
			set Crnt to Crnt->Next
		end while
		set Crnt->Next to Tmp;
	end else
*/
	
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
/*
	declare long PhoneNo
	display "Enter phone number to find: "
	get PhoneNo from user
	declare PhoneRecord *Crnt  and set to Head
	while Crnt is not NULL AND Crnt->PhoneNo is not equal to PhoneNo
		Crnt = Crnt->Next;
	end while
	if Crnt is not NULL
		DisplayRec(Crnt)
	else
		display  "Record not found"
		*/
	
	long PhoneNo;
	cout<<"Enter phone number to find: ";
	cin>>PhoneNo;
	PhoneRecord *Crnt=Head;      					//  <== Possible error here?
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
/*
	if Head is NULL display "List is empty"
	else
		display  "Head record removed:
		DisplayRec(Head)
		declare PhoneRecord *Tmp  and set to Head;
		set Head to Head->Next
		delete Tmp;
	end else
*/

	if(Head==NULL){ cout<<"List is empty";}
	else{
		cout<< "Head record removed:";
		DisplayRec(Head);
		PhoneRecord *Tmp=Head;
		Head=Head->Next;
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
/*
	declare PhoneRecord *Crnt and set to  Head
	while Head is not NULL
		declare PhoneRecord *Tmp and set to Head
		set Head to Head->Next
		delete Tmp
	end while
	display "List deleted"
*/

	PhoneRecord *Crnt=Head;
	while(Head!=NULL){
		PhoneRecord *Tmp = Head;
		Head=Head->Next;
		delete Tmp->Name;
		delete Tmp->Address;
		delete Tmp;
		
	}
	cout<<"List deleted";
}

