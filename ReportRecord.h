#pragma once

#include "CalendarDate.h"
#include "String.h"

class ReportRecord
{
	private:
	CalendarDate date;
	String description;
	int roomNumber;
	
	public:
	ReportRecord();
	ReportRecord(const CalendarDate& date, const String& description, int roomNumber);
	
	CalendarDate getDate() const;
	String getDescription() const;
	int getRoomNumber() const;
	
	
//	void print() const
//	{
//		cout << date << description << roomNumber << endl;
//	}

};
