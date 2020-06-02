#pragma once

#include "Room.h"
#include "ReportRecord.h"

class Hotel
{
	private:
	Vector<Room> rooms;
	Vector<ReportRecord> report;
	Vector<int> findClientReallocations(int roomIndex) const;
		
	public:
	void checkInNormal(int room, const CalendarDate& startDate, const CalendarDate& endDate, const String& note, int guests);
	void checkInVIP(int room, const CalendarDate& startDate, const CalendarDate& endDate,const String& note);
		
	void printAvailability(const CalendarDate& date = CalendarDate::getDateToday());
	void checkOut(int roomNumber);
	
	void printReport(const CalendarDate& startDate, const CalendarDate& endDate) const;
	int findRoom(int bedCount, const CalendarDate& startDate, const CalendarDate& endDate) const;
	int findRoomEmergency(int bedCount, const CalendarDate& startDate, const CalendarDate& endDate) ;
	
	void setRoomAsUnavailable(int roomNumber, const CalendarDate& startDate, const CalendarDate& endDate,const String& note);
};
