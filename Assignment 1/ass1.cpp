/********************************************************************

 * CSCI251 - Ass1

 * <Arpan Kc - akc992>

 * ass1.cpp - Contains function definitions for student records database

 ********************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;



// ============== Constants ==========================================



const char cTextFileName[]   = "ass1.txt";
const char cBinaryFileName[] = "ass1.dat";

const int cMaxRecs = 100;
const int cMaxChars = 30;
const int cMaxSubjects = 8;



// ============= User Defined types ==================================



enum StatusType{eEnrolled,eProvisional,eWithdrawn};
struct SubjectType{ char Code[8]; StatusType Status; int Mark;};



struct StudentRecord{
	
	long StudentNo;
	char FirstName[cMaxChars];
	char LastName[cMaxChars];
	int NumSubjects;
	SubjectType Subjects[cMaxSubjects];

};


// ============= Global Data =========================================



StudentRecord gRecs[cMaxRecs];
int gNumRecs=0;



// ============= Private Function Prototypes =========================



void PrintRecord(int i);
int FindRecord(long StudentNum);
int findSubjectCode(char subjectCode[8],int studentRecordId);
bool ReadTextFile(const char *Filename); //reads text data from file to gRecs[] array
bool WriteTextFile(const char *Filename); //writes text data from gRecs[] to file
bool ReadBinaryFile(const char *Filename); //reads binary data from file to gRecs[] array
bool WriteBinaryFile(const char *Filename); //writes binary data from gRecs[] to file
void WriteBinaryRecord(const char *Filename, int Pos);


// ============= Public Function Definitions =========================


void ReadFile()

{// Reads data file into array

	
	if(ReadBinaryFile(cBinaryFileName)){
		cout<<"successfully read binary file\n";
	}else{
		cout<<"Unable to read binary file.. Reading Text file..\n";
		if(ReadTextFile(cTextFileName)){
			//WriteBinaryFile(cBinaryFileName);
			cout<<"Read text file\n";
		}else{
			cout<<"Unable to read text file and binary file.. \n";
			cout<<"exiting..\n";
			exit(EXIT_FAILURE);
		}
	}
}



void DisplayRecord()

{// Displays specified record on screen

	long studentNumber;
	int i;
	cout<< "Enter student number: ";
	cin>> studentNumber;
	i= FindRecord(studentNumber);
	if (i==-1){
		cout<<"Record not found";
	}
	else{
		PrintRecord(i);
	}
}



void SaveFile()

{// Writes array to files

	int i,j;
	
	if(WriteBinaryFile(cBinaryFileName)){
		cout<<"written to binary file\n";
	}
	else{
		
		cout<<"Unable to write to binary file...\nAttempting to write to text file...\n";
		//Saving data to text file
		
		WriteTextFile(cTextFileName);
		cout<<"Records Saved to text file\n";
	}
}



void UpdateRecord()

{
	//int Pos=0;
	long studentNumber;
	int studentRecordId;			//Stores the index of gNumRecs
	char subjectCode[8];
	char statusOrMark;
	int newMark;
	int newStatus;
	int foundSubjectCode;
	
	
	cout<< "Enter student number: ";
	cin>> studentNumber;
	
	studentRecordId=FindRecord(studentNumber);
	if(studentRecordId==-1){
		cout<<"Record not found !\n";
	}
	else{
		PrintRecord(studentRecordId);		//Displaying student record
		cout<<"\nEnter subject code :\n";
		cin>> subjectCode;
		foundSubjectCode=findSubjectCode(subjectCode,studentRecordId);
		if(foundSubjectCode!=-1){
			cout<<"\nchange status(s) or mark(m)? :";
			cin>> statusOrMark;	

			if(statusOrMark=='m'){
				cout<<"\nNew mark:: ";
				cin>>newMark;
				
				cout<<"\nChanging "<< gRecs[studentRecordId].Subjects[foundSubjectCode].Mark << " to ==> " << newMark<<endl;
				gRecs[studentRecordId].Subjects[foundSubjectCode].Mark=newMark;
				cout<<"changed mark";
			}else if (statusOrMark== 's'){
				cout<<"\nNew status:: 0-eEnrolled 1-eProvisional 2-eWithdrawn  ::";
				cin>> newStatus;
				
				cout<<"\nChanging "<< gRecs[studentRecordId].Subjects[foundSubjectCode].Status << " to ==> " << newStatus <<endl;
				
				gRecs[studentRecordId].Subjects[foundSubjectCode].Status=(StatusType)newStatus;  			
				cout<<"changed status";
			}
			
			WriteBinaryRecord(cBinaryFileName,studentRecordId);
			//SaveFile();
		}
		else{
			cout<<"subject code not found";
		}
	}
}


// ============= Private Function Definitions =========================


void PrintRecord(int i)

{ // Prints record i on screen

	int j;
	
	cout<<endl<<"Student Record::"<<endl;
	cout<<"Student No.    " <<gRecs[i].StudentNo<<endl;
	cout<<"Name  "<< gRecs[i].FirstName<<" ";	
	cout<< gRecs[i].LastName<<endl;	
	cout<<"Number of Subjects    " << gRecs[i].NumSubjects<<endl;
	cout<<"Subjects: \n";
	for (j=0;j<gRecs[i].NumSubjects;j++){
		cout<<"     " <<gRecs[i].Subjects[j].Code;
		switch(gRecs[i].Subjects[j].Status){
			case eEnrolled:
				cout<<" Enrolled";
				break;
				
			case eProvisional:
				cout<<" Provisional";
				break;

			case eWithdrawn:
				cout<<" Withdrawn";
				break;
		}

		cout<<" " <<gRecs[i].Subjects[j].Mark<<endl;

	}
	
	cout<<endl;

}



int FindRecord(long StudentNo)

{// returns index of matching record or -1 if not found

	int i;
	for (i=0;i<gNumRecs;i++){
		if (gRecs[i].StudentNo == StudentNo){
			return i;
		}
	}
	return -1;
}


int findSubjectCode(char subjectCode[8],int studentRecordId)
{ // finds subject code
	
	int j;
	int i=studentRecordId;
	for (j=0;j<gRecs[i].NumSubjects;j++){
		if(strcmp(gRecs[i].Subjects[j].Code,subjectCode)==0){
			cout<<"found subject code with index ::" << j;
			return j;
		}
	
	}
	return -1;
}


bool ReadTextFile(const char *Filename){ 
//reads text data from file to gRecs[] array
	int subjectStatus;
	ifstream fin;
	fin.open(Filename);
	if(!fin.good()){
		cout<<"Cant find text data file !\n";
		return 0;
	}
	
	int j;
	int i= 0;
	char NumSubjectsString;

	fin>> gRecs[i].StudentNo;

	while (!fin.eof()){
		fin>> gRecs[i].FirstName;
		fin>> gRecs[i].LastName;
		fin>> gRecs[i].NumSubjects;
		for (j=0;j<gRecs[i].NumSubjects;j++){
			fin>>subjectStatus;
			gRecs[i].Subjects[j].Status=(StatusType)subjectStatus;
			fin>>gRecs[i].Subjects[j].Mark;	
		}
		i++;
		fin>>gRecs[i].StudentNo;
	}

	gNumRecs=i;
	cout<< i<< " Records read"<<endl;	
	
	fin.close(); 
	return 1;
}


bool WriteTextFile(const char *Filename){
 //writes text data from gRecs[] to file
  
	int i,j;
	ofstream fout;
	fout.open(Filename);
	if(!fout.good()){
		cout<<"Cant find text data file for writing !\n";
			return 0;
		}
	for (i=0;i<gNumRecs;i++){
		fout<<gRecs[i].StudentNo<<endl;
		fout<<gRecs[i].FirstName<<" "<<gRecs[i].LastName<<endl;
		fout<<gRecs[i].NumSubjects<<endl;
		for(j=0;j<gRecs[i].NumSubjects;j++){
			fout<<gRecs[i].Subjects[j].Code<<" "<<gRecs[i].Subjects[j].Status<<" "<<gRecs[i].Subjects[j].Mark<<endl;
		}
		fout<<endl;
	}
	fout.close();
	cout<<"Records Saved\n";
	return 1;
}

bool ReadBinaryFile(const char *Filename){ 								//reads binary data from file to gRecs[] array

	int subjectStatus;
	int numberOfRecords;
	ifstream fin;
	fin.open(Filename,ios::in|ios::binary);
	if(!fin.good()){
		cout<<"Cant find binary data file !\n";
		return 0;
	}
	
	int j;
	int i= 0;
	char NumSubjectsString;
	fin.read((char*)&gNumRecs, sizeof(int)); 						// write number of records
	fin.read((char*)gRecs, sizeof(StudentRecord) * gNumRecs); 		// write records
	
	cout<< gNumRecs<< " Records read from binary file"<<endl;	
	
	fin.close(); 
	return 1;
	
}

bool WriteBinaryFile(const char *Filename){ 								//writes binary data from gRecs[] to file
	int i,j;
	ofstream fout;
	fout.open(Filename,ios::out|ios::binary);
	if(!fout.good()){
		cout<<"Cant find text data file for writing !\n";
			return 0;
		}
		
	fout.write((char*)&gNumRecs, sizeof(int)); 						// write number of records
	fout.write((char*)gRecs, sizeof(StudentRecord) * gNumRecs); 	// write records
	
	fout.close();
	cout<<"Records Saved in binary file\n";
	return 1;
}

void WriteBinaryRecord(const char *Filename, int Pos){
	ofstream fout;
	fout.open(Filename,ios::out|ios::binary);
	if(!fout.good()){
		cout<<"Cant find text data file for writing !\n";
			exit(1);
		}	
	fout.seekp(sizeof(int) + Pos * sizeof(StudentRecord), ios::beg); // seek to position
	fout.write((char*)&gRecs[Pos], sizeof(StudentRecord)); 			 // write record
}


