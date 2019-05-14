#include <iostream>	
#include <string>
#include <iomanip>
#include <cassert>
#include <fstream>

using namespace std;

#include "Call.h"

//This function makes sure that the string is a valid time 
//Parameters: const string& time
//Returns: time.length()
//Effects: prints the names for the columns set apart from each other
bool ValidateTime(const string& time)
{
	// checks if date is only digits
	for (unsigned int i = 0; i < time.size(); i++)
	{
		if (!isdigit(time[i]))
		{
			return false;
		}
	}

	// checks date length
	if (time.length() != 14)
		return false;

	bool length = false;
	bool onlyNumbers = false;
	bool validRange = false;
	bool validMonth = false;
	bool validDay = false;
	bool validHour = false;
	bool validMin = false;
	bool validSec = false;

	bool leapYear = false;

	// constants for checking days
	string const MIN_DAY = "01";
	string const MAX_DAY = "31";

	// constants for checking month
	string const MIN_MON = "01";
	string const MAX_MON = "12";

	// constants for checking year
	string const MIN_YEAR = "1980";
	string const MAX_YEAR = "2050";

	string january = "01";
	string february = "02";
	string march = "03";
	string may = "05";
	string july = "07";
	string august = "08";
	string october = "10";
	string december = "12";

	string month = time.substr(4, 2);
	string day = time.substr(6, 2);
	string hour = time.substr(8, 2);
	string minute = time.substr(10, 2);
	string second = time.substr(12, 2);
	string year = time.substr(0, 4);


	int i_year = stoi(year);

	// checks if leap year
	if ((i_year % 4 == 0) && (!(i_year % 100 == 0)) || (i_year % 400 == 0))
	{
		leapYear = true;
	}

	// checks length of time
	if (time.length() == 14)
	{
		length = true;
	}

	// checks if the string is only numbers
	for (unsigned int i = 0; i < time.size(); i++)
	{
		if (!isdigit(time[i]))
		{
			onlyNumbers;
		}
		else
			onlyNumbers = true;
	}

	// checks if the time is within the correct range of years
	if (year > MIN_YEAR && year < MAX_YEAR)
	{
		validRange = true;
	}
	// checks if the time is a valid month
	if (month >= MIN_MON && month <= MAX_MON)
	{
		validMonth = true;
	}

	// checks if it is a valid day
	if (day >= MIN_DAY && day <= MAX_DAY)
	{
		// checks if it is a valid leap year date
		if (day <= "28")
		{
			validDay = true;
		}

		else if (day == "29" && (month == february && leapYear == true) || (month != february))
		{
			validDay = true;
		}
		// checks if day 30 is valid
		else if (day == "30" && month != february)
		{
			validDay = true;
		}

		// checks if day 31 is valid
		else if (day == "31" && ((month == january) || (month == march) || (month == may) || (month == july) || (month == august) || (month == october) || (month == december)))
		{
			validDay = true;
		}
	}

	// checks if time is valide hour
	if (hour >= "00" && hour <= "24")
	{
		validHour = true;
	}

	// checks if time is valid minute
	if (minute >= "00" && minute <= "59")
	{
		validMin = true;
	}

	// checks if time is valid second
	if (second >= "00" && second <= "59")
	{
		validSec = true;
	}

	// checks if everything that needs to be true is true
	if (length == true && onlyNumbers == true && validRange == true && validDay == true && validSec == true && validHour == true && validMin == true && validMonth == true)
		return true;
	else
		return false;
}

//This function validates the length of duration
//Parameters: const string& timeDuration
//Returns: timeDuration if it is inbetween 0 and 10
//Effects: checks to see if the timeDuration.length() is inbetween 0 and 10
bool ValidateDuration(const string& duration)
{
	if (duration.length() > 0 && duration.length() < 10)
	{
		if (duration.find_first_not_of("0123456789") == string::npos)
		{
			return true;
		}
	}
	else
		return false;
}

//This function checks to see if it is a valid phone number
//Parameters: const string& phoneNumber
//Returns: phoneNumber if it is 12 characters long and starts with either of the three sub strings
//Effects: makes sure phoneNumber.length is correct through the use of substr
bool ValidatePhone(const string& phoneNumber)
{
	for (unsigned int i = 1; i < phoneNumber.size(); i++)
	{
		if (!isdigit(phoneNumber[i]))
		{
			return false;
		}
	}

	if (phoneNumber.length() == 12 && (phoneNumber.substr(0, 1) == "+"))
	{
		return true;
	}
	else
		return false;
}
// default constructor
Call::Call()
{
}

// special constructor
Call::Call(string start, string end, string phone)
{
	_start = start;
	_end = end;
	_phone = phone;
}

// Get Duration of call as an int 
// Parameters: n/a
// Returns: duration
// Formatting error: n/a
unsigned int Call::GetCallDuration() const
{
	int duration = 0;
	int beginHour = stoi(_start.substr(8, 2));
	int beginMin = stoi(_start.substr(10, 2));
	int beginSec = stoi(_start.substr(12, 2));

	int endHour = stoi(_end.substr(8, 2));
	int endMin = stoi(_end.substr(10, 2));
	int endSec = stoi(_end.substr(12, 2));

	unsigned int beginTimeInSeconds = ((beginHour * 60 * 60) + (beginMin * 60) + beginSec);
	if (beginHour > endHour)
	{
		endHour = endHour + 12;
	}
	unsigned int endTimeInSeconds = ((endHour * 60 * 60) + (endMin * 60) + endSec);


	return duration = (endTimeInSeconds - beginTimeInSeconds);
}

// Get formatted start time of call 
// Parameters: n/a
// Returns: startTime
// Effects: prints out formatted string
string Call::GetCallStart() const
{
	string january = "01";
	string february = "02";
	string march = "03";
	string april = "04";
	string may = "05";
	string june = "06";
	string july = "07";
	string august = "08";
	string september = "09";
	string october = "10";
	string november = "11";
	string december = "12";

	string startTime = "0";
	string month, updatedDay;
	string day = _start.substr(6, 2);


	if (ValidateTime(_start))
	{
		if (day < "10")
			updatedDay = _start.substr(7, 1);
		else if (day >= "10")
			updatedDay = day;

		if (_start.substr(4, 2) == january)
			month = "Jan";

		else if (_start.substr(4, 2) == february)
			month = "Feb";

		else if (_start.substr(4, 2) == march)
			month = "Mar";

		else if (_start.substr(4, 2) == april)
			month = "Apr";

		else if (_start.substr(4, 2) == may)
			month = "May";

		else if (_start.substr(4, 2) == june)
			month = "Jun";

		else if (_start.substr(4, 2) == july)
			month = "Jul";

		else if (_start.substr(4, 2) == august)
			month = "Aug";

		else if (_start.substr(4, 2) == september)
			month = "Sep";

		else if (_start.substr(4, 2) == october)
			month = "Oct";

		else if (_start.substr(4, 2) == november)
			month = "Nov";

		else if (_start.substr(4, 2) == december)
			month = "Dec";

		if (updatedDay.length() == 1)
			startTime = month + "  " + updatedDay + " " + _start.substr(8, 2) + ":" + _start.substr(10, 2) + ":" + _start.substr(12, 2) + " " + _start.substr(0, 4);
		else if (updatedDay.length() == 2)
			startTime = month + " " + updatedDay + " " + _start.substr(8, 2) + ":" + _start.substr(10, 2) + ":" + _start.substr(12, 2) + " " + _start.substr(0, 4);
	}
	return startTime;
}

// Get end of call
// Parameters: n/a
// Returns: endTime
// Formatting error: returns formatted string
string Call::GetCallEnd() const
{
	string january = "01";
	string february = "02";
	string march = "03";
	string april = "04";
	string may = "05";
	string june = "06";
	string july = "07";
	string august = "08";
	string september = "09";
	string october = "10";
	string november = "11";
	string december = "12";

	string endTime = "0";
	string month, updatedDay;
	string day = _end.substr(6, 2);


	if (ValidateTime(_end))
	{
		if (day < "10")
			updatedDay = _end.substr(7, 1);
		else if (day >= "10")
			updatedDay = day;

		if (_end.substr(4, 2) == january)
			month = "Jan";

		else if (_end.substr(4, 2) == february)
			month = "Feb";

		else if (_end.substr(4, 2) == march)
			month = "Mar";

		else if (_end.substr(4, 2) == april)
			month = "Apr";

		else if (_end.substr(4, 2) == may)
			month = "May";

		else if (_end.substr(4, 2) == june)
			month = "Jun";

		else if (_end.substr(4, 2) == july)
			month = "Jul";

		else if (_end.substr(4, 2) == august)
			month = "Aug";

		else if (_end.substr(4, 2) == september)
			month = "Sep";

		else if (_end.substr(4, 2) == october)
			month = "Oct";

		else if (_end.substr(4, 2) == november)
			month = "Nov";

		else if (_end.substr(4, 2) == december)
			month = "Dec";

		if (updatedDay.length() == 1)
			endTime = month + "  " + updatedDay + " " + _end.substr(8, 2) + ":" + _end.substr(10, 2) + ":" + _end.substr(12, 2) + " " + _end.substr(0, 4);
		else if (updatedDay.length() == 2)
			endTime = month + " " + updatedDay + " " + _end.substr(8, 2) + ":" + _end.substr(10, 2) + ":" + _end.substr(12, 2) + " " + _end.substr(0, 4);
	}
	return endTime;
}

// Get country code of call
// Parameters: n/a
// Returns: formatted country code
// Effects: formats country code
string Call::GetCallCountryCode() const
{
	if (_phone.at(1) == '1') return "1";
	if (_phone.at(1) == '5' && _phone.at(2) == '0' && _phone.at(3) == '2') return "502";
	if (_phone.at(1) == '5' && _phone.at(2) == '0' && _phone.at(3) == '3') return "503";
	if (_phone.at(1) == '5' && _phone.at(2) == '0' && _phone.at(3) == '4') return "504";
	if (_phone.at(1) == '5' && _phone.at(2) == '0' && _phone.at(3) == '5') return "505";
	if (_phone.at(1) == '5' && _phone.at(2) == '0' && _phone.at(3) == '6') return "506";
	if (_phone.at(1) == '8' && _phone.at(2) == '6' && _phone.at(3) == '6') return "866";

	return "";
}

// Get phone number of call
// Parameters: n/a
// Returns: formatted phone number
// Effects: formats the string
string Call::GetCallPhoneNumber() const
{
	if (_phone.at(1) == '1')  return "(" + _phone.substr(2, 3) + ") " + _phone.substr(5, 3) + "-" + _phone.substr(8, 4);
	if (_phone.at(1) != '1')  return _phone.substr(4, 4) + "-" + _phone.substr(8, 4);
	return "";
}

// checks if the phone has the specified prefix
// Parameters: const string& prefix
// Returns: true if it has the prefix, false if else
// Formatting error: n/a
bool Call::PhoneHasPrefix(const string& prefix) const
{
	for (size_t i = 0; i < _phone.length(); i++)
	{
		if (_phone.find(prefix) != string::npos)
		{
			return true;
		}
	}
	return false;
}
