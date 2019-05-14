#include <iostream>	
#include <string>
#include <cassert>
#include <fstream>

using namespace std;

#include "CallDb.h"
#include "Call.h"

CallDb::CallDb()
{
	_numCalls = 0;
}

// Load database with calls stored in a file
// Parameters: istream& fin
// Returns: failCounter
// Formatting error: n/a
unsigned int CallDb::LoadCallDB(istream& fin)
{
	unsigned int failCounter = 0;
	string start, phone, end;
	fin >> start >> end >> phone;
	while (!fin.eof())
	{
		if (ValidateTime(start) == true && ValidateTime(end) == true && ValidatePhone(phone) == true && _numCalls < MAXCALLS)
		{
			_callLog[_numCalls] = { start, end, phone };
			_numCalls++;
		}
		else
			failCounter++;
		fin >> start >> end >> phone;
	}

	return failCounter;
}

// Get count of call records 
// Parameters: n/a
// Returns: _numCalls
// Formatting error: n/a
unsigned int CallDb::GetCountCallDB() const
{
	return _numCalls;
}

// Retrieve call records
// Parameters: unsigned int index, Call& call
// Returns: false if index is greater than _numCalls, returns true
// Formatting error: n/a
bool CallDb::GetCallInCallDB(unsigned int index, Call& call) const
{
	if (index >= _numCalls)
	{
		return false;
	}
	else
	{
		call = _callLog[index];
	}

	return true;
}

// Return first index >= of call w/ matching E164 prefix, or -1
// Parameters: unsigned int startIndex, const string& prefix
// Returns: i if it has the prefix, -1 if not
// Formatting error: n/a
int CallDb::FindByE164PrefixInCallDB(unsigned int startIndex, const string& prefix) const
{
	for (int i = startIndex; i < MAXCALLS; i++) 
	{
		if (_callLog[i].PhoneHasPrefix(prefix))
			return i;
	}
	return (-1);
}