#include "Hotel.h"
//if guests == -1 , the client wants to use every bed in the room
void Hotel::checkInNormal(int room, const CalendarDate& startDate, const CalendarDate& endDate, const String& note, int guests)
{
	for(int i; i < this->rooms.getSize(); i++)
	{
		if(this->rooms[i].getRoomNumber() == room)
		{
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
				return;
			}
			else
			{
				std::cout << "There is no enough beds in this room." << std::endl;	
			}
		}
	}
	std::cout << "There is no room with this number." << std::endl;	
}

void Hotel::checkInVIP(int room, const CalendarDate& startDate, const CalendarDate& endDate,const String& note)
{
	for(int i; i < this->rooms.getSize(); i++)
	{
		if(this->rooms[i].getRoomNumber() == room)
		{
			this->rooms[i].addVIPclient(startDate, endDate, note);
			return;
		}
	}
	std::cout << "There is no room with this number." << std::endl;	
}
