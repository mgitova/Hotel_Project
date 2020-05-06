#pragma once
#include <iostream>

using namespace std;

class CalendarDate
{
private:
	size_t day;
	size_t month;
	size_t year;
	size_t getDigit(char c) const;
	bool isDigit(char c) const;
	bool isValid(const char* date) const;
	bool isLeapYear(size_t year) const;
public:
	CalendarDate();
	//YYYY-MM-DD
	CalendarDate(const char* date);
		
	bool operator< (const CalendarDate& rhs) const;
	bool operator> (const CalendarDate& rhs) const;
	bool operator>= (const CalendarDate& rhs) const;
	bool operator<= (const CalendarDate& rhs) const;
	bool operator== (const CalendarDate& rhs) const;
	bool operator!= (const CalendarDate& rhs) const;
	
	friend std::ostream& operator<< (std::ostream& out, const CalendarDate& other);
	
};
