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
	if(this->startDatesNormalClients.getSize() > 0)
	{
		cout << "The room is in use by clients" << endl;
	}	
	else if(!this->isVIPinRoom)
	{
		this->startDateVIPclient = startDate;
		this->endDateVIPclient = endDate;
		this->noteVIPclient = note;
		this->isVIPinRoom = true;
		cout << "VIP has checked in" << endl;
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
		cout << "The room is set as unavailable." << endl;
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


void Room::writeToFile(std::ostream& os)
{
	os << this->totalNumberOfBeds << endl;
	os << this->roomNumber << endl;
	os << this->notesNormalClients.getSize() << endl;
	
	for(int i = 0; i < this->notesNormalClients.getSize(); ++i)
	{
		os << this->startDatesNormalClients[i] << endl;
	}
	
	for(int i = 0; i < this->notesNormalClients.getSize(); ++i)
	{
		os << this->endDatesNormalClients[i] << endl;
	}
	
	for(int i = 0; i < this->notesNormalClients.getSize(); ++i)
	{
		os << this->notesNormalClients[i] << endl;
	}
	
	os << this->isVIPinRoom << endl;
	if(this->isVIPinRoom)
	{
		os << startDateVIPclient << endl;
		os << endDateVIPclient << endl;
		os << noteVIPclient << endl;
	}
	
	os << this->isAvailable << endl;
	if(!this->isAvailable)
	{
		os << startDateUnavailability << endl;
		os << endDateUnavailability << endl;
		os << unavailabilityNote << endl;
	}
	
}

bool Room::readFromFile(std::istream& is)
{
	is >> this->totalNumberOfBeds;
	//cout << "totalNumber of beds =" << totalNumberOfBeds << endl;
	if(this->totalNumberOfBeds <= 0)
	{
	//	cout << "Invalid totalNumberOfBeds" << endl;
		return false;
	}
	is.ignore();
	
	is >> this->roomNumber;
	//cout << "roomNumber = " << roomNumber << endl;
	if(this->roomNumber <= 0)
	{
		return false;
	}
	is.ignore();
	
	int notesNormalClientsCount;
	is >> notesNormalClientsCount;
	if(notesNormalClientsCount < 0)
	{
		return false;
	}
//	cout << "notesNormalClientCount =" << notesNormalClientsCount << endl;
	is.ignore();
	this->startDatesNormalClients = Vector<CalendarDate>();
	
	for(int i = 0; i < notesNormalClientsCount; ++i)
	{
		CalendarDate startDate;
		is >> startDate;
	//	cout << "startDate =" << startDate << endl;
		is.ignore();
		if(!is.good())
		{
			return false;
		}
		this->startDatesNormalClients.addElement(startDate);
	}
	
	for(int i = 0; i < notesNormalClientsCount; ++i)
	{
		CalendarDate endDate;
		is >> endDate;
	//	cout << "endDate =" << endDate << endl;
		is.ignore();
		if(!is.good())
		{
			return false;
		}
		this->endDatesNormalClients.addElement(endDate);
	}

	String note;
	Vector<String> noteData;
	char arr[1000];
	
	for(int i = 0; i < notesNormalClientsCount; ++i)
	{
		is.getline(arr,1000);
		noteData = String::splitBySpace(arr);
		note = "";
		for(int i = 0; i < noteData.getSize(); ++i)
		{
		
			note = note + noteData[i] + " ";
		}
		this->notesNormalClients.addElement(note);
	//	cout << "notesNormalClients =" << note << endl;
	}
	
	is >> this->isVIPinRoom;
	//cout << "isVIPinROOm = " << isVIPinRoom << endl;
	if(!is.good())
	{
		return false;
	}
	
	if(this->isVIPinRoom)
	{
		is >> startDateVIPclient;
		is.ignore();
	//	cout << "startDateVIPclient = " << startDateVIPclient << endl;
		is >> endDateVIPclient;
		is.ignore();
	//	cout << "endDateVIPclient = " << endDateVIPclient << endl;
		
		String note;
		Vector<String> noteData;
		char arr[1000];
		is.getline(arr,1000);
		noteData = String::splitBySpace(arr);
		note = "";
		
		for(int i = 0; i < noteData.getSize(); ++i)
		{
			note = note + noteData[i] + " ";
		}
		
		if(!is.good())
		{
			return false;
		}
		this->noteVIPclient = note;
//		cout << "noteVIP = " << note<< endl;
	}

	is >> this->isAvailable;
	if(!is.good())
	{
		return false;
	}
	//cout << "isAvaialable =" << isAvailable << endl;
	if(!this->isAvailable)
	{		
		is >> startDateUnavailability;
		is.ignore();
	//	cout << "startDateUnavailable =" << startDateUnavailability << endl;
		is >> endDateUnavailability;
	//	cout << "endDateUnavailbale =" << endDateUnavailability << endl;
		is.ignore();
		
		String note;
		Vector<String> noteData;
		
		char arr[1000];
	//	cout << "Is stream good " << is.good() << endl;
		is.getline(arr,1000);
	//	cout << "Is stream good " << is.good() << endl;
		noteData = String::splitBySpace(arr);
		note = "";
		for(int i = 0; i < noteData.getSize(); ++i)
		{
			note = note + noteData[i] + " ";
		}
//		cout << "noteUnavailbale =" << note << endl;
		if(!is.good())
		{
//			cout << "eof " << is.eof() << endl;
//			cout << "bad " << is.bad() << endl;
//			cout << "fail " << is.fail() << endl;
			return false;
		}
		//cout << "Test14 room" << endl;
		this->unavailabilityNote = note;
	}
	return is.good();	
}
	


