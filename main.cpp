#include <iostream>

#include "Hotel.h"
using namespace std;

int main() 
{
	Vector<Room> rooms = Vector<Room>(); 
	rooms.addElement(Room(10,101));
	rooms.addElement(Room(10,101));
	rooms.addElement(Room(5,102));
	rooms.addElement(Room(3,103));
	Hotel h = Hotel(rooms);
	
//	h.checkInNormal(101,"2020-06-03", "2020-06-04","Itovi",-1);
//	h.print();
//	h.checkOut(101);
//	h.print();	
	while(true)
	{
		String command;
		cin >> command;
		if(command == "checkin")
		{
			int room;
			cin >> room;
			
			char from[100];
			cin >> from;
			CalendarDate dateFrom = from;
			
			char to[100];
			cin >> to;
			CalendarDate dateTo = to;
			
			String note;
			cin >> note;
			
			int guests;
			cin >> guests;	
			
			h.checkInNormal(room,dateFrom,dateTo,note, guests);
		}
		else if (command == "availability")
		{
			char dates[100];
			cin >> dates;
			CalendarDate date = dates;
			
			h.printAvailability(date);
		}
		else if (command == "checkout")
		{
			int room;
			cin >> room;
			
			h.checkOut(room);
		}
		else if (command == "report")
		{
			char from[100];
			cin >> from;
			CalendarDate dateFrom = from;
			
			char to[100];
			cin >> to;
			CalendarDate dateTo = to;
			
			h.printReport(dateFrom, dateTo);
		}
		else if (command == "find")
		{
			int beds;
			cin >> beds;
			
			char from[100];
			cin >> from;
			CalendarDate dateFrom = from;
			
			char to[100];
			cin >> to;
			CalendarDate dateTo = to;
			
			h.findRoom(beds,dateFrom,dateTo);
		}
		else if (command == "find!")
		{
			int beds;
			cin >> beds;
			
			char from[100];
			cin >> from;
			CalendarDate dateFrom = from;
			
			char to[100];
			cin >> to;
			CalendarDate dateTo = to;
			
			h.findRoomEmergency(beds,dateFrom,dateTo);
		}
		else if (command == "unavailable")
		{
			int roomNumber;
			cin >> roomNumber;
			
			char from[100];
			cin >> from;
			CalendarDate dateFrom = from;
			
			char to[100];
			cin >> to;
			CalendarDate dateTo = to;
			
			String note;
			cin >> note;
						
			h.setRoomAsUnavailable(roomNumber,dateFrom,dateTo,note);
		}
		else 
		{
			h.print();
		}
	}
	
	
	//https://github.com/mgitova/Hotel_Project_C-
	//system("pause");
	return 0;
}
