#include "CommandRunner.h"
#include <fstream>

CommandRunner::CommandRunner()
{
	this->hotel = nullptr;
}

void CommandRunner::createDefaultHotel()
{
	Vector<Room> rooms = Vector<Room>(); 

	rooms.addElement(Room(10,101));
	rooms.addElement(Room(5,102));
	rooms.addElement(Room(3,103));
	
	Hotel h = Hotel(rooms);
	h.checkInNormal(102,"2020-03-23","2020-03-24","Georgievi",2);
	h.checkInNormal(103, "2020-03-23", "2020-03-24","Belakovi",3);
	char fileName[] = "hotel.txt";
	ofstream writer(fileName);
	h.writeToFile(writer);
}

void CommandRunner::setHotel(Hotel* ptr)
{
	this->hotel = ptr;
}

bool CommandRunner::isFileOpen() const
{
	return this->currentFileName.getSize() > 0;
}

void CommandRunner::run()
{
//
//	Vector<Room> rooms = Vector<Room>(); 
//
//	rooms.addElement(Room(10,101));
//	rooms.addElement(Room(5,102));
//	rooms.addElement(Room(3,103));
//	
	Hotel& h = *(this->hotel);
//	h = Hotel(rooms);
	
	Vector<String> data;
	char arr[1000];
	CommandRunner::createDefaultHotel();
	
	while(true)
	{
		cin.getline(arr,1000);
		String line = arr;
		data = String::splitBySpace(line);
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
			int room = String::stringToInt(data[1],isValid);
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
				guests = String::stringToInt(data[4],isValid);
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
					note = note + data[i] + " ";
				}
			}
			else
			{
				for (int i = 4; i < data.getSize(); ++i)
				{
					note = note + data[i] + " ";
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
			int room = String::stringToInt(data[1],isValid);
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
			int beds = String::stringToInt(data[1],isValid);
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
			int beds = String::stringToInt(data[1],isValid);
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
			if(data.getSize() != 5)
			{
				cout << "Invalid parameter count" << endl;
				continue;
			}
			
			bool isValid;
			int room = String::stringToInt(data[1],isValid);
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
		else if(command == "save")
		{
			if (data.getSize() == 3)
			{
				if(data[1] == "as")
				{
					if(this->saveAs(data[2]))
					{
						cout << "Successfully saved in file \"" << data[2] << "\"" << endl;
					}
					else
					{
						cout << "Failed to save in file \"" << data[2] << "\"" << endl;
					}
				}
				else
				{
					cout << "Invalid command ";
					for (int i = 1; i < data.getSize(); ++i)
					{
						cout << data[i];
					}
					cout << endl;
				}
			}
			else if (data.getSize() == 1)
			{
				cout << "Test1 " << endl;
				if(this->saveAs(this->currentFileName))
				{
					cout << "Successfully saved in file \"" << this->currentFileName << "\"" << endl;
				}
				else
				{
					cout << "Failed to save in file \"" << this->currentFileName << "\"" << endl;
				}
			}
			
 		}
 		else if(command == "open")
 		{
 			if (data.getSize() != 2)
 			{
 				cout << "Invalid parameters" << endl;
			}
			else
			{
				this->open(data[1]);
			}
		}
		else if(command == "close")
		{
			if(data.getSize() == 1)
			{ 
				this->close();
			}
			else
			{
				cout << "Invalid parameter count" << endl;
			}
		}
		else if(command =="exit")
		{
			if(data.getSize() == 1)
			{
				break;
			}
			else
			{
				cout << "Invalid parameters count." << endl;
			}
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
	cout << "Goodbye! =)" << endl;
}


bool CommandRunner::saveAs(const String& nameFile) const
{
	if(!this->isFileOpen())
	{
		cout << "There are no files opened." << endl;
		return false;
	}
	ofstream writer(nameFile.getStr());
	if(!writer.good())
	{
		return false;
	}
	this->hotel->writeToFile(writer);
	return writer.good();
}

void CommandRunner::open(const String& nameFile)
{
	if(this->isFileOpen())
	{
		cout << "The file \"" << nameFile << "\" is already opened." << endl;
		return;
	}
	ifstream reader(nameFile.getStr());
	if(!reader.good())
	{
		cout << "The file \"" << nameFile << "\"can't be opened." << endl;
		return;
	}
	//readHotel
	Hotel input;
	
	if(input.readFromFile(reader) && reader.good())
	{
		*(this->hotel) = input;
		cout << "Successfully read a hotel from file \"" << nameFile << "\"" << endl;
		this->currentFileName = nameFile;
	}
	else
	{
		cout << "Invalid hotel from file \"" << nameFile << "\"" << endl;
		cout << "No changes made. " << endl;
	}
	
}

void CommandRunner::close()
{
	if(this->isFileOpen())
	{
		this->currentFileName == "";
		cout << "Successfully closed without saving" << endl;
	}
	else
	{
		cout << "There are no files opened." << endl;
	}
}


void CommandRunner::help()
{
	cout << "Checkin blablabla";
}


