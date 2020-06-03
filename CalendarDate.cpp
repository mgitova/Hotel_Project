#include "CalendarDate.h"
#include <cassert>
#include <cstring>
#include <ctime>

size_t CalendarDate::getDigit(char c) 
{
	return c - '0';
}

bool CalendarDate::isDigit(char c) 
{
	return c >= '0' && c <= '9';
}

bool CalendarDate::isLeapYear (size_t year) 
{
	if(year % 4 == 0)
	{
		if(year % 100 == 0)
		{
			if(year % 400 == 0)
			{
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
	
}

CalendarDate::CalendarDate()
{
	this->day = 1;
	this->month = 1;
	this->year = 1970;
}

CalendarDate::CalendarDate(const char* date)
{
	assert(this->isValid(date));
	this->year = getDigit(date[0])*1000 + getDigit(date[1])*100 + getDigit(date[2])*10 + getDigit(date[3]);
	this->day = getDigit(date[5])*10 + getDigit(date[6]);
	this->month = getDigit(date[8])*10 + getDigit(date[9]);
	
}

bool CalendarDate::operator< (const CalendarDate& rhs) const
{	 
	if(this->year < rhs.year)
	{
		return true;
	}
	else if(this->year > rhs.year)
	{
		return false;
	}
	else
	{		
		if(this->month < rhs.month)
		{
			return true;
		}
		else if (this->month > rhs.month)
		{
			return false;
		}
		else
		{
			if(this->day < rhs.day)
			{
				return true;
			}
			else if (this->day > rhs.day)
			{
				return false;
			}
			else
			{
				return false;
			}
		}		
	}
}

bool CalendarDate::operator> (const CalendarDate& rhs) const
{
	return rhs < *this;
}
//lhs >= rhs 
bool CalendarDate::operator>= (const CalendarDate& rhs) const
{
	return !(*this < rhs);
}
//lhs <= rhs
bool CalendarDate::operator<= (const CalendarDate& rhs) const
{
	return !(*this > rhs);
}
//lhs==rhs
bool CalendarDate::operator== (const CalendarDate& rhs) const
{
	return this->day == rhs.day && this->month == rhs.month && this->year == rhs.year;
//	return !(rhs < *this) && !(*this < rhs);
}

bool CalendarDate::operator!= (const CalendarDate& rhs) const
{
	return !(rhs == *this);	
}

bool CalendarDate::isValid(const char* date) 
{
	if (date == nullptr)
	{
		return false;
	}
	
	size_t length = strlen(date);
	if (length != 10)
	{
		return false;
	}

	//check year
	for(int i = 0; i < 4; i++)
	{
		if (!isDigit(date[i]))
		{
			return false;
		}
	}

	if (date[4] != '-')
	{
		return false;
	}
	
	//check month
	if(!isDigit(date[5]) && !isDigit(date[6]))
	{
		return false;
	}

	if (date[7] != '-')
	{
		return false;
	}

	//check day
	if(!isDigit(date[8]) && !isDigit(date[9]))
	{
		return false;
	}
	
	size_t year = getDigit(date[0])*1000 + getDigit(date[1])*100 + getDigit(date[2])*10 + getDigit(date[3]);
	size_t month = getDigit(date[5])*10 + getDigit(date[6]);
	size_t day =  getDigit(date[8])*10 + getDigit(date[9]);
	
	
	if (month < 1 || month > 12)
	{
		return false;
	}
	
	switch(month)
	{
		case 2: 
		{
			if(isLeapYear(year) && day > 29)
			{
				return false;
			}
			
			if (!(isLeapYear(year)) && day > 28)
			{
				return false;
			}
			
			break;
		}
		case 1: 
		case 3: 
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: 
		{
			if (day > 31)
			{
				return false;
			}
			break;
		}
		default:
		{
			if(day > 30)
			{ 
				return false;
			}
		}	
	}
	
	return true;	
	
}

std::ostream& operator<< (std::ostream& out, const CalendarDate& other)
{
	if(other.year <= 9)
	{
		out << "000" << other.year;		
	}
	else if (other.year >= 10 && other.year <= 99)
	{
		out << "00" << other.year;
	}
	else if (other.year >= 100 && other.year <= 999)
	{
		out << "0" << other.year;
	}
	else
	{
		out << other.year;
	}
	
	out << "-";
	
	out << (other.month <= 9 ? "0" : "") << other.month;
	
	out << "-";
	
	out << (other.day <= 9 ? "0" : "") << other.day;
	
	return out;	
}
	
CalendarDate CalendarDate::getDateToday()
{
	long long t = time(0);
	std::tm* now = std::localtime(&t);
	
	CalendarDate result;
	result.day = now->tm_mday;
	result.month = now->tm_mon + 1;
	result.year = now->tm_year + 1900;
	
	return result;
}

bool CalendarDate::areOverlapping(const CalendarDate& dateStart1, const CalendarDate& dateEnd1, 
								const CalendarDate& dateStart2, const CalendarDate& dateEnd2)
{
	bool check1 = dateStart1 >= dateStart2 && dateStart1 <= dateEnd2;
	bool check2 = dateEnd1 >= dateStart2 && dateEnd1 <= dateEnd2;
	bool check3 = dateStart2 >= dateStart1 && dateStart2 <= dateEnd1;
	bool check4 = dateEnd2 >= dateStart1 && dateEnd2 <= dateEnd1;
	
	return check1 || check2 || check3 || check4;
}
	
