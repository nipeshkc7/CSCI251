/**********************************************************************
 * wordstats.cpp - CSCI251 - Ass3 - Contains WordsStats class definition
 * <your name> <your login> <date last modified>
 **********************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "wordstats.h"
using namespace std;

WordStats::WordStats(){
	strcpy(Filename,"testdata.txt");
}

// Reads dictionary.txt into Dictionary
void WordStats::ReadDictionary(){
	ifstream fin;
	fin.open("Dictionary.txt");
	if (fin.fail()){
		cout<<"\nCould not open file \n";
	}
	cout<<"\nReading data from Dictionary.txt..\n";
	int counter;
	while(!fin.eof()){
		string temp;
		getline(fin,temp);
		
		//Converting to lowercase
		for (int i=0;i<temp.length();i++)   
		   temp[i]=tolower(temp[i]);
		Dictionary.insert(temp);
		counter++;
	}
	cout<<counter <<" Records read.\n\n";
}

// Displays Dictwords 10 at a time
void WordStats::DisplayDictionary(){
	cout<<"Displaying the first 20 records"<<endl;
	set<string>::iterator it=Dictionary.begin();
    for(int i=0;i<20;i++){
    	cout<<*it<<endl;
    	it++;
	}
	cout<<endl;
}

// Reads textfile into KnownWords and UnknownWords
void WordStats::ReadTxtFile(){
	ifstream fin;
	int counterTotalKnownWords=0,PositionIndex=0;
	fin.open(Filename);
	if(fin.fail()){
		cout<<"\nCould not read test data.. \n EXITING.. \n";
		exit(1);
	}
	while(!fin.eof()){
		string temp;
		fin>>temp;
		temp=StripPunctuation(temp); //strips punctuation from argument

		//set<string>::iterator it=Dictionary.find(temp);
		if(!isNumber(temp)){
			if(Dictionary.find(temp) != Dictionary.end())
			{//if word found in the dictionary
				StoreToMap(KnownWords,temp,PositionIndex);
			}
			else
			{//If word not found in the dictionary
				StoreToMap(UnknownWords,temp,PositionIndex);
			}
		}
		PositionIndex++;	
	}
	
//	cout<<"\nTotal words:: "<<PositionIndex;
//	cout<<"\nTotal known words:: "<<counterTotalKnownWords<<endl<<endl;
	cout<<"\nTotal words:: "<<KnownWords.size()+UnknownWords.size();
	cout<<"\nTotal unknown words::"<<UnknownWords.size();
	cout<<"\nTotal known words:: "<<KnownWords.size()<<endl<<endl;
	
}

// Displays stats of words in KnownWords
void WordStats::DisplayKnownWordStats(){
	DisplayStats(KnownWords);
}

// Displays stats of words in Unknownwords
void WordStats::DisplayUnknownWordStats(){
	DisplayStats(UnknownWords);
}

// Displays 20 most frequent words in KnownWords
void WordStats::DisplayMostFreqKnownWords(){
	DisplayFrequency(KnownWords);
}

// Displays 20 most frequent words in UnknownWords
void WordStats::DisplayMostFreqUnknownWords(){
	DisplayFrequency(UnknownWords);
}

// Displays original text from KnownWords & UnknownWords
void WordStats::DisplayOriginalText(){
}

// ============ Private Fns ========================

// add your private fns here...
string WordStats::StripPunctuation(string temp){ //strips punctuation except hyphen and apostrophe
	for (int i=0;i<temp.size();i++){ 	
		   temp[i]=tolower(temp[i]);
		   if(ispunct(temp[i]) && temp[i]!='-' && temp[i]!='\''){
		   		temp.erase(i,1);
				i--; 
				}
		}
	return temp;
}

void WordStats::StoreToMap(WordMap &map,string word, int index){//Stores word and index to map
	WordMapIter iter=map.find(word);
	if(iter !=map.end()){
		(*iter).second.push_back(index);
	}else{
		vector<int> vect(1,index);
		map.insert(iter,pair<string, vector<int> >(word,vect));
	}
}

void WordStats::DisplayStats(WordMap &map){
	cout<< setw(16)<< "Words"<<setw(8)<<"Count"<<setw(16)<<"Occurrences"<<endl;
	for(WordMapIter iter=map.begin();iter!=map.end();iter++){
		cout<<setw(16)<<iter->first;
		vector<int> vect=iter->second;
		int count=vect.size();
		cout<< setw(8)<<count<<setw(8);
		for(int i=0;i<count;i++)
			cout<<vect[i]<<" ";
		cout<<endl;
	}
}

bool WordStats::isNumber(string word){
	for(int i=0;i<word.length();i++){
		if(isdigit(word[i]))
			return true;
	}
	return false;
}

void WordStats::DisplayFrequency(WordMap map){
	multimap<int,string> frequencyMap;
	multimap<int,string>::reverse_iterator revIterator;
	for(WordMapIter iter=map.begin();iter!=map.end();iter++){
		vector<int> vect= iter->second;
		string word=iter->first; 
		frequencyMap.insert(frequencyMap.begin(),pair<int,string>(vect.size(),word));
	}
	
	revIterator=frequencyMap.rbegin();
	cout<<setw(13)<<"Word"<<setw(16)<<"Frequency"<<endl;
	for(int i=0;i<20;i++){
		cout<< setw(13)<< revIterator->second <<setw(16)<<revIterator->first<<endl;
		revIterator++;
	}
}


