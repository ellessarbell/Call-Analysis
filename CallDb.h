#pragma once
#include "Call.h"

// Maximum number calls in call database 
const int MAXCALLS = 15;

// Call database 
class CallDb {
public:
	CallDb();
	// Load database with calls stored in a file 
	unsigned int LoadCallDB(istream& fin);
	// Get count of call records 
	unsigned int GetCountCallDB()const;
	// Retrieve call records 
	bool GetCallInCallDB(unsigned int index, Call& call) const;
	// Return first index >= of call w/ matching E164 prefix, or -1 
	int FindByE164PrefixInCallDB(unsigned int startIndex, const string& prefix) const;

private:
	Call _callLog[MAXCALLS];  // Stores calls in database  
	unsigned int  _numCalls;  // Number of calls stored 
};