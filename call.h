#pragma once

// Stores raw information about one call 
class Call {

public:
	Call();
	Call(string start, string end, string phone);
	// Get Duration of call as an int 
	unsigned int GetCallDuration() const;
	// Get formatted start time of call 
	string GetCallStart() const;
	// Get formatted end time of call 
	string GetCallEnd() const;
	// Get country code of call 
	string GetCallCountryCode() const;
	// Get phone number of call 
	string GetCallPhoneNumber() const;
	//string ToString();
	//string ToFormattedString();

	bool PhoneHasPrefix(const string&) const;

private:
	string _start;
	string _end;
	string _phone;
};

bool ValidateTime(const string& time);
bool ValidatePhone(const string& phoneNumber);
bool ValidateDuration(const string& duration);