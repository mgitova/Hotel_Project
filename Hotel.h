#pragma once

#include "Room.h"
#include "ReportRecord.h"

class Hotel
{
	private:
	Vector<Room> rooms;
	Vector<ReportRecord> report;
		
	public:
	void checkInNormal(int room, const CalendarDate& startDate, const CalendarDate& endDate, const String& note, int guests);
	void checkInVIP(int room, const CalendarDate& startDate, const CalendarDate& endDate,const String& note);
		
		
};
