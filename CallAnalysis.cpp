#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "CallDb.h"

//void Print(CallDb& obj, Call& item, string prefix);

int main()
{
	
	// Makes an array big enough to hold enough files
	const int SIZE = 20;
	int total = 0;
	int start = 0;
	int found = 0;
	string numberValues[SIZE];
	ifstream fin;
	string fileName, prefix;
	CallDb obj;
	Call item;

	//prompts for file name and reads it
	cout << "Enter a file name" << endl;
	getline(cin, fileName);
	fin.open(fileName);

	//produces error if file cannot be found
	if (fin.fail()) {
		cerr << "Can't open '" << fileName << "'" << endl;
		exit(1);
	}

	int fail = obj.LoadCallDB(fin); //sets int fail to LoadCallDB

	// closes file 
	fin.close();

	
	if (fail >= 2) //if fail is greater than or equal to 2, output
	{
		cout << "Not all calls could be added to database, " << obj.GetCountCallDB() << " records added, " << fail << " dropped";
	}
	else if (fail >= 1) //if fail is greater than or equal to 1, output
	{
		cout << "Log successfully read into database, " << obj.GetCountCallDB() << " records added, " << fail << " dropped";
	}
	else //output if successful
		cout << "Log successfully read into database, " << obj.GetCountCallDB() << " records added";
		cout << "\n\n";

	// properly displays header
	cout << "Contents of Call Database" << endl;

	//runs through for loop with 3 if statements and calls on functions in order to correctly format displayed text
	if (obj.GetCountCallDB() == 0)
	{
		cout << "No records" << endl << endl;
	}
	else if (obj.GetCountCallDB())
	{
		//properly displays header
		cout << "Start" << setw(23) << "End" << setw(29) << "Country" << setw(15) << "Phone Number" << setw(15) << "Duration" << endl;
		for (int i = 0; i < obj.GetCountCallDB(); i++)
		{
			obj.GetCallInCallDB(i, item);
			//prints formatted info
			cout << left << setw(25) << item.GetCallStart() << setw(25) << item.GetCallEnd() << setw(10) << item.GetCallCountryCode() << setw(19) << item.GetCallPhoneNumber() << (item.GetCallDuration() / 60) << ":" << right << setw(2) << setfill('0') << (item.GetCallDuration() % 60) << endl;
			cout << left << setfill(' ');
			total += item.GetCallDuration();
		}
		cout << "Total duration of all calls: " << total / 60 << ":" << total % 60 << endl << endl; //formats total
	}

	//calls Print
	cout << "E164 prefix for query: " << endl;
	getline(cin, prefix); //gets prefix
	while (prefix.length() > 0) //goes through loop as long as length is > 0
	{
		for (int i = 0; i < obj.GetCountCallDB(); i++)
		{
			found = obj.FindByE164PrefixInCallDB(i, prefix); //sets found to FindByE164PrefixInCallDb
			if (found != -1)
			{
				obj.GetCallInCallDB(found, item);
				//prints formatted info
				cout << left << setw(25) << item.GetCallStart() << setw(25) << item.GetCallEnd() << setw(10) << item.GetCallCountryCode() << setw(19) << item.GetCallPhoneNumber() << (item.GetCallDuration() / 60) << ":" << right << setw(2) << setfill('0') << (item.GetCallDuration() % 60) << endl;
				cout << left << setfill(' ');
				total += item.GetCallDuration(); //formats total
				i = found;
			}
		}
		//checks to see if prefix is allowed
		cout << "Total duration of all calls: " << total / 60 << ":" << total % 60 << endl;
		cout << "E164 prefix for query: ";
		getline(cin, prefix); //gets prefix again

		//checks to see if prefix is allowed
		if (prefix != "+1" || prefix != "+502" || prefix != "+503" || prefix != "+504" || prefix != "+505" || prefix != "+506" || prefix != "+886")
		{
			cout << "No Records" << endl;
		}
	}
	return 0;
}