#pragma once
#include "String.h"
#include "Vector.h"
#include "CalendarDate.h"

class Room
{
	private:
	int totalNumberOfBeds;
	int roomNumber;
	
	Vector<CalendarDate> startDatesNormalClients;
	Vector<CalendarDate> endDatesNormalClients;
	Vector<String> notesNormalClients;
	
	Vector<CalendarDate> startDatesVIPclients;
	Vector<CalendarDate> endDatesVIPclients;
	Vector<String> notesVIPclients;
	
	bool isAvailable;
	CalendarDate startDateUnavailability;
	CalendarDate endDateUnavailability;
	String unavailabilityNote;
	
	public:
	Room();
	Room(int totalNumberOfBeds, int roomNumber);
	
	void addNormalClient(const CalendarDate& startDate, const CalendarDate& endDate, const String& note);
	void removeNormalClientAtIndex(int index);
	
	void addVIPclient(const CalendarDate& startDate, const CalendarDate& endDate, const String& note);
	void removeVIPclientAtIndex(int index);
};
