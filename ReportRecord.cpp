#include "ReportRecord.h"

ReportRecord::ReportRecord()
{
	
}

ReportRecord::ReportRecord(const CalendarDate& date, const String& description, int roomNumber)
: date (date), description(description), roomNumber(roomNumber)
{
	
}

CalendarDate ReportRecord::getDate() const
{
	return this->date;
}

String ReportRecord::getDescription() const
{
	return this->description;
}

int ReportRecord::getRoomNumber() const
{
	return this->roomNumber;
}
