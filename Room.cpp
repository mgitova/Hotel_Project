#include <iostream>
#include "Room.h"
#include <cassert>

Room::Room()
{
	this->totalNumberOfBeds = -1;
	this->roomNumber = -1;
	this->isAvailable = false;
}

Room::Room(int totalNumberOfBeds, int roomNumber)
{
	assert(totalNumberOfBeds > 0 && roomNumber > 0);
	this->totalNumberOfBeds = totalNumberOfBeds;
	this->roomNumber = roomNumber;
	this->isAvailable = true;
	this->isVIPinRoom = false;
}

void Room::addNormalClient(const CalendarDate& startDate, const CalendarDate& endDate, const String& note)
{
	if(!this->isVIPinRoom && this->totalNumberOfBeds > this->notesNormalClients.getSize())
	{
		this->startDatesNormalClients.addElement(startDate);
		this->endDatesNormalClients.addElement(endDate);
		this->notesNormalClients.addElement(note);
	}
	else if (isVIPinRoom)
	{
		std::cout << "Room is being used by VIP." << std::endl;
	}
	else
	{
		std::cout << "Room is full." << std::endl;
	}
}

void Room::removeNormalClientAtIndex(int index)
{
	if(index < this->startDatesNormalClients.getSize() && index >= 0)
	{
		this->startDatesNormalClients.removeElementAt(index);
		this->endDatesNormalClients.removeElementAt(index);
		this->notesNormalClients.removeElementAt(index);
	}
	else
	{
		std::cout << "Cannot remove client." << std::endl;
	}
}

void Room::addVIPclient(const CalendarDate& startDate, const CalendarDate& endDate, const String& note)
{
	if(!this->isVIPinRoom)
	{
		this->startDateVIPclient = startDate;
		this->endDateVIPclient = endDate;
		this->noteVIPclient = note;
		this->isVIPinRoom = true;
	}
	else
	{
		std::cout << "Room is already taken by a VIP." << std::endl;
	}
}

void Room::removeVIPclient()
{
	if(isVIPinRoom)
	{
		this->startDateVIPclient = CalendarDate();
		this->endDateVIPclient = CalendarDate();
		this->noteVIPclient = String();
		this->isVIPinRoom = false;
	}
	else
	{
		std::cout << "There is no VIP in the room." << std::endl;
	}
}

void Room::setUnavailability(const CalendarDate& startDate, const CalendarDate& endDate, const String& note)
{
	assert(this->isAvailable);
	assert(this->notesNormalClients.getSize() == 0);
	assert(!this->isVIPinRoom);
	
	this->startDateUnavailability = startDate;
	this->endDateUnavailability = endDate;
	this->unavailabilityNote = note;
	this->isAvailable = false;
}

void Room::setRoomAsAvailable()
{
	assert(!this->isAvailable);
	this->isAvailable = false;
}

int Room::getNumberOfFreeBeds() const
{
	return this->totalNumberOfBeds - this->notesNormalClients.getSize();
}

int Room::getTotalNumberOfBeds() const
{
	return this->totalNumberOfBeds;
}

int Room::getRoomNumber() const
{
	return this->roomNumber;
}
