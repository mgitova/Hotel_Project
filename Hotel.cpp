#include "Hotel.h"

Hotel::Hotel()
{
	
}

Hotel::Hotel (const Vector<Room>& rooms) : rooms (rooms)
{
	for (int i = 0; i < rooms.getSize() ; ++i)
	{
		assert(rooms[i].isAvailable);
		assert(!rooms[i].isVIPinRoom);
		assert(rooms[i].notesNormalClients.getSize() == 0);
	}
	for (int i = 0; i < rooms.getSize() ; ++i)
	{
		for (int j = i + 1; j < rooms.getSize(); ++j)
		{
			if(rooms[i].getRoomNumber() == rooms[j].getRoomNumber())
			{
				cout << "Number of room at index " << i << " is equal to number of room at index " << j << " = " << rooms[i].getRoomNumber() << endl;
				assert(false);
			}
		}
	}
}

Vector<int> Hotel::findClientReallocations(int roomIndex) const
{
	Vector<int> roomIndexesOfReallocatedClients = Vector<int>();
	int freeBedsFoundSoFar = 0 ;	
	for (int i = 0; i < this->rooms.getSize(); ++i)
	{
		if(i != roomIndex) 
		{
			int freeBedsCurrentRoom = this->rooms[i].getNumberOfFreeBeds();
			freeBedsFoundSoFar += freeBedsCurrentRoom;
			for (int j = 0; j < freeBedsCurrentRoom; ++j)
			{
				roomIndexesOfReallocatedClients.addElement(i);
			}
		}	
	}
	return roomIndexesOfReallocatedClients;
}	


//if guests == -1 , the client wants to use every bed in the room
void Hotel::checkInNormal(int room, const CalendarDate& startDate, const CalendarDate& endDate, const String& note, int guests)
{	
	for(int i = 0; i < this->rooms.getSize(); i++)
	{
		if(this->rooms[i].getRoomNumber() == room)
		{
			if(!this->rooms[i].isAvailable)
			{
				cout << "The room is unavailable for check-ins." << endl;
				return;
			}
			
			if (guests == -1)
			{
				guests = this->rooms[i].getTotalNumberOfBeds();
			}			
			if(this->rooms[i].getNumberOfFreeBeds() >= guests)
			{
				for(int j = 0; j < guests; j++)
				{
					this->rooms[i].addNormalClient(startDate, endDate, note);
				}
				cout << "The guest" << (guests > 1 ? "s" : "") << (guests > 1 ? " have" : " has") <<" checked in." << endl;
				return;
			}
			else
			{
				std::cout << "There is no enough beds in this room." << std::endl;
				return;	
			}
		}
	}
	std::cout << "There is no room with number " << room << std::endl;	
}

void Hotel::checkInVIP(int room, const CalendarDate& startDate, const CalendarDate& endDate,const String& note)
{
	for(int i = 0; i < this->rooms.getSize(); i++)
	{
		if(this->rooms[i].getRoomNumber() == room)
		{
			this->rooms[i].addVIPclient(startDate, endDate, note);
			return;
		}
	}
	std::cout << "There is no room with this number." << std::endl;	
}

void Hotel::printAvailability(const CalendarDate& date)
{
	bool isRoomFound = false;
	
	for (int i = 0; i < this->rooms.getSize() ; ++i)
	{
		if(this->rooms[i].isAvailableFromTo(date, date))
		{
			cout<< "Room number " << this->rooms[i].getRoomNumber() << " is available for date " << date << endl;
			isRoomFound = true;
		}
	}
	
	if(!isRoomFound)
	{
		cout << "There are no available rooms for date " << date << endl;
	}
	
}

void Hotel::checkOut(int roomNumber)
{
	for (int i = 0; i < this->rooms.getSize(); ++i)
	{
		if(this->rooms[i].getRoomNumber() == roomNumber)
		{
			if (!this->rooms[i].isVIPinRoom && this->rooms[i].startDatesNormalClients.getSize() == 0)
			{
				cout << "The room is already empty" << endl;
				return;
			}
			if(this->rooms[i].isVIPinRoom)
			{
				cout << "The VIP client is checked out." << endl;
				ReportRecord rec1 (this->rooms[i].endDateVIPclient, String (" VIP client checked out from room, note : ") + this->rooms[i].noteVIPclient , this->rooms[i].getRoomNumber());
				this->report.addElement(rec1);	
				this->rooms[i].removeVIPclient();
			}
			
			if(this->rooms[i].startDatesNormalClients.getSize() > 0)
			{
				for (int j = 0; j < this->rooms[i].startDatesNormalClients.getSize(); ++j)
				{
					ReportRecord rec1 (this->rooms[i].endDatesNormalClients[j], String (" normal client checked out from room, note : ") + this->rooms[i].notesNormalClients[j], this->rooms[i].getRoomNumber());
					this->report.addElement(rec1);	
				}
				this->rooms[i].removeAllNormalClients();
				cout << "The room is empty now." << endl;
			}
			return;
		}
	}
}

void Hotel::printReport(const CalendarDate& startDate, const CalendarDate& endDate) const
{
	bool isRecordFound = false;
	for(int i = 0; i < this->report.getSize(); ++i)
	{
		if(CalendarDate::areOverlapping(startDate,endDate,this->report[i].getDate(), this->report[i].getDate()))
		{
			cout << report[i].getDate() << " room number " << report[i].getRoomNumber() << " : " << report[i].getDescription() << endl; 
			isRecordFound = true;
		}
	}	
	if(!isRecordFound)
	{
		cout << "There is no report" << endl;
	}
	
}

int Hotel::findRoom(int bedCount, const CalendarDate& startDate, const CalendarDate& endDate) const
{
	bool isRoomFound = false;
	int roomIndex = 0;
	int roomNumber = this->rooms[roomIndex].getRoomNumber();
	
	for (int i = 0; i < this->rooms.getSize(); ++i)
	{
		if(this->rooms[i].isAvailableFromTo(startDate, endDate))
		{
			if(this->rooms[i].getNumberOfFreeBeds() >= bedCount)
			{
				roomIndex = i;
				roomNumber = this->rooms[i].getRoomNumber();
				isRoomFound = true;
			}
		}
	}
	
	if (isRoomFound)
	{
		return roomNumber;
	}
	else 
	{
		return -1;
	}	
}

int Hotel::findRoomEmergency(int bedCount, const CalendarDate& startDate, const CalendarDate& endDate) 
{
	//check if empty room with enough beds exist
	int roomNumber = this->findRoom(bedCount, startDate, endDate);
	if(roomNumber != -1)
	{
		cout << "Room number " << roomNumber << " is the most suitable room for the VIP. " << endl;		
		return roomNumber;
	}
	//find room with normal clients and minimum beds >= bedCount
	int roomIndex = 0;
	bool isRoomFound = false;
	for (int i = 0; i < this->rooms.getSize(); ++i)
	{
		if(!this->rooms[i].isVIPinRoom && this->rooms[i].getTotalNumberOfBeds() >= bedCount)
		{
			isRoomFound = true;
			if(this->rooms[roomIndex].getTotalNumberOfBeds() > this->rooms[i].getTotalNumberOfBeds())
			{
				roomIndex = i;
			}		
		}
	}
	
	if(!isRoomFound)
	{
		cout << "There is no suitable room for the VIP." << endl;
		return -1;
	}
	
	Vector<int> clientReallocations = this->findClientReallocations(roomIndex);
	
	int i = 0; //move clients to a free bed
	for(i = 0; i < clientReallocations.getSize();++i)
	{
		this->rooms[clientReallocations[i]].addNormalClient(this->rooms[roomIndex].startDatesNormalClients[i],this->rooms[roomIndex].endDatesNormalClients[i],this->rooms[roomIndex].notesNormalClients[i]);
		
	}
	
	//update report for clients for which there are no free beds
	for (;i < this->rooms[roomIndex].notesNormalClients.getSize();++i)
	{
		cout << "A client has been removed from the hotel because of the demands of the VIP." << endl;
		ReportRecord rec1 (this->rooms[roomIndex].endDatesNormalClients[i], String (" normal client checked out from room because VIP needs room urgently, note : ") + this->rooms[roomIndex].notesNormalClients[i], this->rooms[roomIndex].getRoomNumber());
		this->report.addElement(rec1);	
	}
	
	//remove clients from the old room
	this->rooms[roomIndex].removeAllNormalClients();
	cout << "Room number " << this->rooms[roomIndex].getRoomNumber() << " is the most suitable room for the VIP. " << endl;	
	return roomIndex;	
}

void Hotel::setRoomAsUnavailable(int roomNumber, const CalendarDate& startDate, const CalendarDate& endDate,const String& note)
{
	for (int i = 0; i < this->rooms.getSize();++i)
	{
		if(this->rooms[i].getRoomNumber() == roomNumber)
		{
			this->rooms[i].setUnavailability(startDate,endDate,note);
		}
	}
}

void Hotel::writeToFile(std::ostream& os)
{
	os << this->rooms.getSize() << endl;
	
	for(int i = 0; i < this->rooms.getSize(); ++i)
	{
		//print room in file
		this->rooms[i].writeToFile(os);
	}
	os << this->report.getSize() << endl;
	for(int i = 0; i < this->report.getSize(); ++i)
	{
		os << this->report[i].getDate() << endl;
		os << this->report[i].getDescription() << endl;
		os << this->report[i].getRoomNumber() << endl;
	}	
}

bool Hotel::readFromFile(std::istream& is)
{
	int roomCount;	
	is >> roomCount;
//	cout << "RoomCount = " << roomCount << endl;
	if(roomCount <= 0)
	{
		return false;
	}
	
	is.ignore();
	this->rooms = Vector<Room>();
	Room currentRoom;
	for(int i = 0; i < roomCount; ++i)
	{
		//read room from file
		bool isValid = currentRoom.readFromFile(is);
				
		if(!isValid || !is.good())
		{
			//cout << "Invalid room detected" << endl;
			return false;
		}
		
		this->rooms.addElement(currentRoom);
		//cout << "Room read from file." << endl;
	}
	
	int reportCount;
	is >> reportCount;
	//cout << "ReportCount = " << reportCount << endl;
 	if(reportCount < 0)
	{
		return false;
	}
	is.ignore();
	
	this->report = Vector<ReportRecord>();
	
	CalendarDate date;
	Vector<String> descriptionData;
	String description;
	int roomNumber;
	char arr[1000];
	
	for(int i = 0; i < reportCount; ++i)
	{
		is >> date;
		is.ignore();
		is.getline(arr,1000);
	//	cout << "Date= " << date << endl;
		
		descriptionData = String::splitBySpace(arr);
		description = "";
		for(int i = 0; i < descriptionData.getSize(); ++i)
		{
			description = description + descriptionData[i] + " ";
		}
	//	cout << "Description = " << description << endl;
		is >> roomNumber;
	//	cout << "RoomNumber = " << roomNumber << endl;
		is.ignore();
				
		if(!is.good())
		{
//			cout << "eof " << is.eof() << endl;
//			cout << "bad " << is.bad() << endl;
//			cout << "fail " << is.fail() << endl;
			return false;
		}
		
		this->report.addElement(ReportRecord(date,description,roomNumber));
	}

	return is.good();
}
