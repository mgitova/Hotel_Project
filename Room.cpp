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

void Room::removeAllNormalClients()
{
	if(this->startDatesNormalClients.getSize() > 0)
	{
		this->startDatesNormalClients = Vector<CalendarDate>();
		this->endDatesNormalClients = Vector<CalendarDate>();
		this->notesNormalClients = Vector<String>();	
	}
	else
	{
		cout << "There are no normal clients in the room" << endl;
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
	if (this->isAvailable && this->notesNormalClients.getSize() == 0 && !this->isVIPinRoom)
	{	
		cout << "Set as unavailable" << endl;
		this->startDateUnavailability = startDate;
		this->endDateUnavailability = endDate;
		this->unavailabilityNote = note;
		this->isAvailable = false;
	}
	else 
	{
		if(!this->isAvailable)
		{
			cout << "The room is already set as unavailable." << endl;
		}
		else 
		{
			cout << "Room is in use by clients." << endl;
		}
	}
	
}

void Room::setRoomAsAvailable()
{
	if(!this->isAvailable)
	{
		this->isAvailable = false;
	}
	else
	{
		cout << "Room is already available." << endl;
	}
	
}

int Room::getNumberOfFreeBeds() const
{
	if(isVIPinRoom)
	{
		return 0;
	}
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

bool Room::isAvailableFromTo(const CalendarDate& dateStart, const CalendarDate& dateEnd) const
{
	for (int i = 0; i < this->startDatesNormalClients.getSize();++i)
	{
		if(CalendarDate::areOverlapping(dateStart,dateEnd,this->startDatesNormalClients[i],this->endDatesNormalClients[i]))
		{
			return false;
		}
	}
	
	if(this->isVIPinRoom)
	{
		if(CalendarDate::areOverlapping(dateStart,dateEnd,this->startDateVIPclient,this->endDateVIPclient))
		{
			return false;
		}
	}
	
	if(!this->isAvailable)
	{
		if(CalendarDate::areOverlapping(dateStart,dateEnd,this->startDateUnavailability,this->endDateUnavailability))
		{
			return false;
		}
	}
	return true;	
}

