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
	Hotel();
	Hotel(const Vector<Room>& rooms);
	void checkInNormal(int room, const CalendarDate& startDate, const CalendarDate& endDate, const String& note, int guests);
	void checkInVIP(int room, const CalendarDate& startDate, const CalendarDate& endDate,const String& note);
		
	void printAvailability(const CalendarDate& date = CalendarDate::getDateToday());
	void checkOut(int roomNumber);
	
	void printReport(const CalendarDate& startDate, const CalendarDate& endDate) const;
	int findRoom(int bedCount, const CalendarDate& startDate, const CalendarDate& endDate) const;
	int findRoomEmergency(int bedCount, const CalendarDate& startDate, const CalendarDate& endDate) ;
	
	void setRoomAsUnavailable(int roomNumber, const CalendarDate& startDate, const CalendarDate& endDate,const String& note);
	void writeToFile(std::ostream& os);
	bool readFromFile(std::istream& is);
	
	void print() const
	{
		cout << "Rooms: " << endl;
		for(int i =0; i < this->rooms.getSize(); ++i)
		{
			this->rooms[i].print();
		}
		cout << "Report: " << endl;
		for(int i =0; i < this->report.getSize(); ++i)
		{
			this->report[i].print();
		}
		cout << endl;
	}
};
