// Title: Lab 3 Call Database Unit Test - Lab3UnitTest.cpp
//
// Purpose: Runs validation tests on the call database component for Lab 3.
// 
// Class: CSC 2430 Spring 2018
//
// Author: Carlos Arias (Adapted from Max Benson)

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

#include "call.h"
#include "calldb.h"


int main()
{
	// Update all stringstreams
	// Update types according to standard
	CallDb calldb;
	Call call;
	stringstream inbuffer1;
	stringstream inbuffer2;
	stringstream inbuffer3;
	string expected;


	// Try some calls
	assert(calldb.GetCountCallDB() == 0);
	assert(!calldb.GetCallInCallDB(0, call));
	assert(calldb.FindByE164PrefixInCallDB(0, "+") == -1);

	cerr << "TEST 01 --------------- PASSED" << endl;
	cerr << "Empty Call DB" << endl;
	cerr << "------------------------------" << endl;

	// Load some calls
	inbuffer1.str(
		"20160101120000 20160101120015 +12062812000\n"
		"20160508115512 20160508121513 +86698974534\n"
		"20170110091233 20170229110000 +50622334589\n"	// Not a leap year
		"20171129145316 20171129150000 +852\n");		// Invalid phone number
	assert(calldb.LoadCallDB(inbuffer1) == 2);
	assert(calldb.GetCountCallDB() == 2);

	cerr << "TEST 02 --------------- PASSED" << endl;
	cerr << "Loading Records to Call DB" << endl;
	cerr << "------------------------------" << endl;


	assert(calldb.GetCallInCallDB(0, call));
	assert(call.GetCallDuration() == 15);
	assert(call.GetCallStart() == "Jan  1 12:00:00 2016");
	assert(call.GetCallEnd() == "Jan  1 12:00:15 2016");
	assert(call.GetCallCountryCode() == "1");
	assert(call.GetCallPhoneNumber() == "(206) 281-2000");

	cerr << "TEST 03 --------------- PASSED" << endl;
	cerr << "First Call Record Test" << endl;
	cerr << "------------------------------" << endl;

	assert(calldb.GetCallInCallDB(1, call));
	assert(call.GetCallDuration() == 1201);
	assert(call.GetCallStart() == "May  8 11:55:12 2016");
	assert(call.GetCallEnd() == "May  8 12:15:13 2016");
	assert(call.GetCallCountryCode() == "866");
	assert(call.GetCallPhoneNumber() == "9897-4534");

	cerr << "TEST 04 --------------- PASSED" << endl;
	cerr << "Second Call Record Test" << endl;
	cerr << "------------------------------" << endl;

	assert(!calldb.GetCallInCallDB(2, call));
	assert(calldb.FindByE164PrefixInCallDB(0, "") == 0);
	assert(calldb.FindByE164PrefixInCallDB(0, "+1") == 0);
	assert(calldb.FindByE164PrefixInCallDB(1, "+1") == -1);
	assert(calldb.FindByE164PrefixInCallDB(0, "+866") == 1);
	assert(calldb.FindByE164PrefixInCallDB(0, "+9") == -1);

	cerr << "TEST 05 --------------- PASSED" << endl;
	cerr << "Testing Finding by Prefix" << endl;
	cerr << "------------------------------" << endl;

	CallDb calldb2;

	// Load some more calls
	inbuffer2.str(
		"18000101120000 20160101120015 +12062812000\n" 	// Invalid start time
		"20160508115512 20160508121513 86698974534\n"	// Invalid phone number
		"20150229182110 20160229190005 +12025551234\n"	// Invalid start time
		"20170131235500 2017AA31235532 +50499853746\n"	// Invalid end time
		"20181231011515 2018 +13257744661\n"			// Invalid end time
		"20190505060000 20190505061559 +15XX7845191\n"	// Invalid phone number
		"20181301010000 20181201250000 +12062832000\n"	// Invalid start and end time
		"20181201157500 20181201130000 +45\n");			// Invalid start time and phone

	assert(calldb2.LoadCallDB(inbuffer2) == 8);
	assert(calldb2.GetCountCallDB() == 0);
	assert(!calldb2.GetCallInCallDB(0, call));

	cerr << "TEST 06 --------------- PASSED" << endl;
	cerr << "Testing All Invalid Records" << endl;
	cerr << "------------------------------" << endl;

	CallDb calldb3;

	// Load some more calls
	inbuffer3.str(
		"20180214123102 20180214123503 +12065554881\n"
		"20180216015000 20180216020500 +50499853746\n"
		"20180217124515 20180217135000 +12062812000\n"
		"20180218115559 20180219010500 +12029251234\n"
		"20170229081000 20170229081500 +13255551234\n"
		"20171515100000 20170101000000 +50298784565\n"
		"20180105153215 AAF00000000000 +50345783224\n"
		"20161010090012 2016 +50565781245\n"
		"20151010250000 20151010007500 +50278894512\n"
		"20170827153000 20170827153215 123456789012\n"
		"20170827153000 20170827153215 +234567A9012\n"
		"20170827153000 20170827153215 +8656789012\n"
		"20170827153000 20170827153215 +86656789012\n"
		"20101015120000 20101015120555 +12065558989\n"
		"20101015134515 20101015135001 +12062812000\n"
		"20101231115900 20110101000015 +50422320484\n");

	assert(calldb3.LoadCallDB(inbuffer3) == 8);
	assert(calldb3.GetCountCallDB() == 8);

	cerr << "TEST 07 --------------- PASSED" << endl;
	cerr << "Loading Records to Call DB (2)" << endl;
	cerr << "------------------------------" << endl;

	assert(calldb3.GetCallInCallDB(0, call));
	assert(call.GetCallDuration() == 241);
	assert(call.GetCallStart() == "Feb 14 12:31:02 2018");
	assert(call.GetCallEnd() == "Feb 14 12:35:03 2018");
	assert(call.GetCallCountryCode() == "1");
	assert(call.GetCallPhoneNumber() == "(206) 555-4881");

	cerr << "TEST 08 --------------- PASSED" << endl;
	cerr << "First Call Record Test" << endl;
	cerr << "------------------------------" << endl;

	assert(calldb3.FindByE164PrefixInCallDB(0, "") == 0);
	assert(calldb3.FindByE164PrefixInCallDB(0, "+1") == 0);
	assert(calldb3.FindByE164PrefixInCallDB(1, "+1") == 2);
	assert(calldb3.FindByE164PrefixInCallDB(3, "+1") == 3);
	assert(calldb3.FindByE164PrefixInCallDB(4, "+1") == 5);
	assert(calldb3.FindByE164PrefixInCallDB(6, "+1") == 6);
	assert(calldb3.FindByE164PrefixInCallDB(7, "+1") == -1);
	assert(calldb3.FindByE164PrefixInCallDB(0, "+5042") == 7);
	assert(calldb3.FindByE164PrefixInCallDB(0, "+12065") == 0);
	assert(calldb3.FindByE164PrefixInCallDB(1, "+12065") == 5);
	assert(calldb3.FindByE164PrefixInCallDB(6, "+12065") == -1);
	assert(calldb3.FindByE164PrefixInCallDB(0, "+4") == -1);

	cerr << "TEST 09 --------------- PASSED" << endl;
	cerr << "Find by Prefix Test" << endl;
	cerr << "------------------------------" << endl;


	assert(calldb3.GetCallInCallDB(1, call));
	assert(call.GetCallDuration() == 900);

	assert(calldb3.GetCallInCallDB(2, call));
	assert(call.GetCallDuration() == 3885);

	assert(calldb3.GetCallInCallDB(4, call));
	assert(call.GetCallDuration() == 135);

	assert(calldb3.GetCallInCallDB(5, call));
	assert(call.GetCallDuration() == 355);

	assert(calldb3.GetCallInCallDB(6, call));
	assert(call.GetCallDuration() == 286);

	cerr << "TEST 10 --------------- PASSED" << endl;
	cerr << "Duration test" << endl;
	cerr << "------------------------------" << endl;

	assert(calldb3.GetCallInCallDB(3, call)); // Extra Credit commented by default
	assert(call.GetCallDuration() == 47341);
	cerr << "E X T R A   C R E D I T  ===== 1/2 =====" << endl;

	assert(calldb3.GetCallInCallDB(7, call));
	assert(call.GetCallDuration() == 43275);
	cerr << "E X T R A   C R E D I T  ===== 2/2 =====" << endl;



	// Congratulate 
	cerr << endl << "Good work, you passed the unit tests." << endl;

    return 0;
}
