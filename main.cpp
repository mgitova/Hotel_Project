#include <iostream>
#include "Hotel.h"
#include <sstream> //https://www.cplusplus.com/reference/sstream/istringstream/istringstream/


using namespace std;

Vector<String> splitBySpace(const String& line)
{
	Vector<String> result;	
	String currentParameter;
	
	for (int i = 0; i < line.getSize(); ++i)
	{
		if(line[i] == ' ')
		{
			if(currentParameter != "")
			{
				result.addElement(currentParameter);
				currentParameter = "";
			}
		}	
		else
		{
			currentParameter = currentParameter + line[i];
		}
	}
	
	if(currentParameter != "")
	{
		result.addElement(currentParameter);
	}
	
	return result;	
}

int stringToInt(const String& s, bool& isValid)
{
	int num;
	istringstream iss(s.getStr());
	iss >> num;
	if(iss.eof())
	{
		isValid = true;
		return num;
	}
	else
	{
		isValid = false;
		return -1;
	}
}

int main() 
{
	Vector<Room> rooms = Vector<Room>(); 
	rooms.addElement(Room(10,101));
	rooms.addElement(Room(5,102));
	rooms.addElement(Room(3,103));
	Hotel h = Hotel(rooms);
	
//	h.checkInNormal(101,"2020-06-03", "2020-06-04","Itovi",-1);
//	h.print();
//	h.checkOut(101);
//	h.print();	

	Vector<String> data;
	char arr[1000];
	while(true)
	{
		cin.getline(arr,1000);
		String line = arr;
		data = splitBySpace(line);
		String command;
		if(data.getSize() > 0)
		{
			command = data[0];
		}

		if(command == "checkin")
		{
			
			if (data.getSize() < 5)
			{
				cout << "There are too little arguments" << endl;
				continue;
			}
			
			bool isValid;
			int room = stringToInt(data[1],isValid);
			if(!isValid || room <= 0)
			{
				cout << "Invalid room number" << data[1] << endl;
				continue;
			}
			
			if(!CalendarDate::isValid(data[2].getStr()))
			{
				cout << "Invalid calendar date from" << endl;
				continue;
			}
			CalendarDate dateFrom = data[2].getStr();
			
			if(!CalendarDate::isValid(data[3].getStr()))
			{
				cout << "Invalid calendar date to" << endl;
				continue;
			}
			CalendarDate dateTo = data[3].getStr();
			if(dateTo < dateFrom)
			{
				cout << "Invalid date interval" << endl;
			}
		
			bool isVIP = false;
			int guests = 0;
			if(data[4] == "VIP")
			{
				isVIP = true;
			}
			else 
			{
				guests = stringToInt(data[4],isValid);
				if(isValid && guests <= 0)
				{
					cout << "Invalid bed count. " << endl;
					continue;
				}
			
			}
			
			String note;
			if(isVIP || guests > 0)
			{
				for (int i = 5; i < data.getSize(); ++i)
				{
					note = note + " " + data[i];
				}
			}
			else
			{
				for (int i = 4; i < data.getSize(); ++i)
				{
					note = note + " " + data[i];
				}
			}
		
			if(isVIP)
			{
				h.checkInVIP(room,dateFrom,dateTo,note);
			}
			else
			{
				h.checkInNormal(room,dateFrom,dateTo,note,guests);
			}
			
		}
		else if (command == "availability")
		{
			CalendarDate date;
			if(data.getSize() == 1)
			{
				date = CalendarDate::getDateToday();
			}
			else if(data.getSize() == 2)
			{
				if(!CalendarDate::isValid(data[1].getStr()))
				{
					cout << "Invalid calendar date" << endl;
					continue;
				}
				else 
				{
					date = data[1].getStr();
				}
			}
			else 
			{
				cout << "Invalid parameter count, expected 1 or 0" << endl;
				continue;
			}

			h.printAvailability(date);
		}
		else if (command == "checkout")
		{
			if(data.getSize() != 2)
			{
				cout << "Invalid parameter count" << endl;
				continue;
			}
			bool isValid;
			int room = stringToInt(data[1],isValid);
			if(isValid && room > 0)
			{
				h.checkOut(room);
			}
			else
			{
				cout << "Invalid room number";
				continue;
			}
						
		}
		else if (command == "report")
		{
			if(data.getSize() != 3)
			{
				cout << "Invalid parameter count" << endl;
				continue;
			}
			if(!CalendarDate::isValid(data[1].getStr()))
			{
				cout << "Invalid calendar date from" << endl;
				continue;
			}
			CalendarDate dateFrom = data[1].getStr();
			
			if(!CalendarDate::isValid(data[2].getStr()))
			{
				cout << "Invalid calendar date to" << endl;
				continue;
			}
			CalendarDate dateTo = data[2].getStr();
			if(dateTo < dateFrom)
			{
				cout << "Invalid date interval" << endl;
			}
			
			h.printReport(dateFrom, dateTo);
		}
		else if (command == "find")
		{
			if(data.getSize() != 4)
			{
				cout << "Invalid parameter count" << endl;
				continue;
			}
			
			bool isValid;
			int beds = stringToInt(data[1],isValid);
			if(!isValid && beds <= 0)
			{
				cout << "Invalid number of beds" << endl;
			}
			
						
			if(!CalendarDate::isValid(data[2].getStr()))
			{
				cout << "Invalid calendar date from" << endl;
				continue;
			}
			CalendarDate dateFrom = data[2].getStr();
			
			if(!CalendarDate::isValid(data[3].getStr()))
			{
				cout << "Invalid calendar date to" << endl;
				continue;
			}
			CalendarDate dateTo = data[3].getStr();
			if(dateTo < dateFrom)
			{
				cout << "Invalid date interval" << endl;
			}
			
			int roomNumber = h.findRoom(beds,dateFrom,dateTo);
			if(roomNumber != -1)
			{
				cout << "Room number " << roomNumber << " is the most suitable room. " << endl;				
			}
			else
			{
				cout << "There is no suitable room" << endl;
			}
		}
		else if (command == "find!")
		{
			if(data.getSize() != 4)
			{
				cout << "Invalid parameter count" << endl;
				continue;
			}
			
			bool isValid;
			int beds = stringToInt(data[1],isValid);
			if(!isValid && beds <= 0)
			{
				cout << "Invalid number of beds" << endl;
			}
			
						
			if(!CalendarDate::isValid(data[2].getStr()))
			{
				cout << "Invalid calendar date from" << endl;
				continue;
			}
			CalendarDate dateFrom = data[2].getStr();
			
			if(!CalendarDate::isValid(data[3].getStr()))
			{
				cout << "Invalid calendar date to" << endl;
				continue;
			}
			CalendarDate dateTo = data[3].getStr();
			if(dateTo < dateFrom)
			{
				cout << "Invalid date interval" << endl;
			}
			
			h.findRoomEmergency(beds,dateFrom,dateTo);
		}
		else if (command == "unavailable")
		{
			if(data.getSize() != 4)
			{
				cout << "Invalid parameter count" << endl;
				continue;
			}
			
			bool isValid;
			int room = stringToInt(data[1],isValid);
			if(!isValid && room <= 0)
			{
				cout << "Invalid room number" << endl;
			}
			
						
			if(!CalendarDate::isValid(data[2].getStr()))
			{
				cout << "Invalid calendar date from" << endl;
				continue;
			}
			CalendarDate dateFrom = data[2].getStr();
			
			
			if(!CalendarDate::isValid(data[3].getStr()))
			{
				cout << "Invalid calendar date to" << endl;
				continue;
			}
			CalendarDate dateTo = data[3].getStr();
			if(dateTo < dateFrom)
			{
				cout << "Invalid date interval" << endl;
			}
			
			
			String note = data[4];
						
			h.setRoomAsUnavailable(room,dateFrom,dateTo,note);
		}
		else if (command == "print")
		{
			h.print();
		}
		else
		{
			cout << " Invalid command " ;
			for (int i = 1; i < data.getSize(); ++i)
			{
				cout << data[i];
			}
			cout << endl;
		}
	}
	
	
	//https://github.com/mgitova/Hotel_Project_C-
	//system("pause");
	return 0;
}
