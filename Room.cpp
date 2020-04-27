#include <iostream>
#include "Room.h"
#include <cassert>

Room::Room()
{
	this->totalNumberOfBeds = -1;
	this->roomNumber = -1;
	this->isAvailable = true;
}

Room::Room(int totalNumberOfBeds, int roomNumber)
{
	assert(totalNumberOfBeds > 0 && roomNumber > 0);
	this->totalNumberOfBeds = totalNumberOfBeds;
	this->roomNumber = roomNumber;
	isAvailable = true;
}

void Room::addNormalClient(const CalendarDate& startDate, const CalendarDate& endDate, const String& note)
{
	if(this->totalNumberOfBeds > this->notesNormalClients.getSize() + this->notesVIPclients.getSize())
	{
		this->startDatesNormalClients.addElement(startDate);
		this->endDatesNormalClients.addElement(endDate);
		this->notesNormalClients.addElement(note);
	}
	else
	{
		std::cout << "Cannot add client." << std::endl;
	}
}

void Room::removeNormalClientAtIndex(int index)
{
	if(index < startDatesNormalClients.getSize() && index >= 0)
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
	if(this->totalNumberOfBeds > this->notesNormalClients.getSize() + this->notesVIPclients.getSize())
	{
		this->startDatesVIPclients.addElement(startDate);
		this->endDatesVIPclients.addElement(endDate);
		this->notesVIPclients.addElement(note);
	}
	else
	{
		std::cout << "Cannot add VIP client." << std::endl;
	}
}

void Room::removeVIPclientAtIndex(int index)
{
	if(index < startDatesVIPclients.getSize() && index >= 0)
	{
		this->startDatesVIPclients.removeElementAt(index);
		this->endDatesVIPclients.removeElementAt(index);
		this->notesVIPclients.removeElementAt(index);
	}
	else
	{
		std::cout << "Cannot remove VIP client." << std::endl;
	}
}
