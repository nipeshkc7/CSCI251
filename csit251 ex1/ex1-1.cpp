#include <iostream>
#include <string.h>
using namespace std;

void PrintReverseString(char[]);
void PrintReverseWord(char[]);

int main(){
	char StringToBeReversed[50];
	cout<<"Enter the string\n";	
	cin.getline(StringToBeReversed,20);
	PrintReverseString(StringToBeReversed);
	PrintReverseWord(StringToBeReversed);
	return 0;
}

void PrintReverseString(char word[])
{
	int i=0;
	char reversed[50];
	
	cout<<"Reversed string is:";
	for(i=strlen(word);i>=0;i--){
		cout<< word[i];	
	}
}

void PrintReverseWord(char word[])
{
	cout<<"\n\nReversed word is:: ";
	int start=0,end=0;
    do{
        while(word[end]!=' ' && word[end]!='\0')end++; 
        for(int i=end-1;i>=start;i--) cout<<word[i]; 
        cout<<' ';
        start = end = end+1; 
    }while(end<strlen(word)); 
    cout<<endl;

    
}

