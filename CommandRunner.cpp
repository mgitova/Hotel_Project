#include "CommandRunner.h"
#include <fstream>

///default constructor
CommandRunner::CommandRunner()
{
	
}

///checks whether the file is open
bool CommandRunner::isFileOpen() const
{
	return this->currentFileName.getSize() > 0;
}

void CommandRunner::run()
{
	cout << "Please type a command." << endl;
	cout << "If you want to see the commands type \"help\" " << endl;
	Hotel& h = this->hotel; 
	
	Vector<String> data;
	char arr[1000];
	
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
			if(!this->isFileOpen())
			{
				cout << "No file opened."<< endl;
				continue;
			}
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
					cout << "Invalid bed count." << endl;
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
			if(!this->isFileOpen())
			{
				cout << "No file opened."<< endl;
				continue;
			}
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
			if(!this->isFileOpen())
			{
				cout << "No file opened."<< endl;
				continue;
			}
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
			if(!this->isFileOpen())
			{
				cout << "No file opened."<< endl;
				continue;
			}
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
			if(!this->isFileOpen())
			{
				cout << "No file opened."<< endl;
				continue;
			}
			
			if(data.getSize() != 4)
			{
				cout << "Invalid parameter count" << endl;
				continue;
			}
			
			bool isValid;
			int beds = String::stringToInt(data[1],isValid);
			if(!isValid || beds <= 0)
			{
				cout << "Invalid number of beds" << endl;
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
			if(!this->isFileOpen())
			{
				cout << "No file opened."<< endl;
				continue;
			}
			if(data.getSize() != 4)
			{
				cout << "Invalid parameter count" << endl;
				continue;
			}
			
			bool isValid;
			int beds = String::stringToInt(data[1],isValid);
			if(!isValid || beds <= 0)
			{
				cout << "Invalid number of beds" << endl;
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
			
			h.findRoomEmergency(beds,dateFrom,dateTo);
		}
		else if (command == "unavailable")
		{
			if(!this->isFileOpen())
			{
				cout << "No file opened."<< endl;
				continue;
			}
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
//		else if (command == "print")
//		{
//			h.print();
//		}
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
		else if(command == "help")
		{
			if(data.getSize() != 1)
			{
				cout << "Invalid parameter count" << endl;
			}
			else
			{
				this->help();
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
			cout << "Invalid command \"" ;
			for (int i = 0; i < data.getSize() - 1; ++i)
			{
				cout << data[i] << " ";
			}
			cout << data[data.getSize() - 1] << "\"" << endl;
		}
	}
	cout << "Goodbye!\nExiting the program..." << endl;
}

///save [as <file>]
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
	this->hotel.writeToFile(writer);
	return writer.good();
}

///open <file>
void CommandRunner::open(const String& nameFile)
{
	if(this->isFileOpen())
	{
		cout << "The file \"" << this->currentFileName << "\" is already opened." << endl;
		return;
	}
	ifstream reader(nameFile.getStr());
	
	if(!reader.good())
	{
		ofstream writer(nameFile.getStr());
		if(!writer.good())
		{
			cout << "The file \"" << nameFile << "\" cannot be created." << endl;
			return;
		}
	
		cout << "Enter the number of rooms for the new hotel: " << endl;
		int roomCount;
		cin >> roomCount;
		cin.ignore();
		if(roomCount < 0)
		{
			cout << "Room count has to be at least one." << endl;
			return;
		}
		if(!cin.good())
		{
			cout << "Invalid room count." << endl;
			///clear error flags from cin
			cin.clear();
			return;
		}
		
		Vector<Room> rooms;
		for (int i = 0; i < roomCount; ++i)
		{
			cout << "Enter a room number for the room " << i + 1 << ":"<< endl;
			int roomNumber;
			cin >> roomNumber;
			cin.ignore();
			if(roomNumber < 0)
			{
				cout << "Room number has to be a positive number." << endl;
				return;
			}
			if(!cin.good())
			{
				cout << "Invalid room number." << endl;
				//clear error flags from cin
				cin.clear();
				return;
			}
			
			cout << "Enter total number of beds in the current room: " << endl;
			int totalNumberOfBeds;
			cin >> totalNumberOfBeds;
			cin.ignore();
			if(totalNumberOfBeds < 0)
			{
				cout << "Total number of beds has to be a positive number." << endl;
				return;
			}
			if(!cin.good())
			{
				cout << "Invalid total number of beds. " << endl;
				//clear error flags from cin
				cin.clear();
				return;
			}		
			rooms.addElement(Room(totalNumberOfBeds, roomNumber));	
		}
		
		this->hotel = Hotel(rooms);
		this->hotel.writeToFile(writer);
		cout << "New hotel successfully created in file \"" << nameFile << "\"" << endl;
		this->currentFileName = nameFile;
		return;
	}
	///if there are file with name <nameFile>, we read the hotel.
	Hotel input;
	if(input.readFromFile(reader) && reader.good())
	{
		this->hotel = input;
		cout << "Successfully read a hotel from file \"" << nameFile << "\"" << endl;
		this->currentFileName = nameFile;
	}
	else
	{
		cout << "Invalid hotel from file \"" << nameFile << "\"" << endl;
		cout << "No changes made. " << endl;
	}
}

///closes currently opened file
void CommandRunner::close()
{
	if(this->isFileOpen())
	{
		cout << "Successfully closed \"" << this->currentFileName << "\" without saving."<< endl;
		this->currentFileName = "";
	}
	else
	{
		cout << "There are no files opened." << endl;
	}
}

///prints the commands
void CommandRunner::help()
{
	cout << "The following commands are supported: " << endl;
	cout << endl;
	cout << "checkin - registration in <room number> <date from> <date to> [number of guests] <note for the guest/s>" << endl;
	cout << "availability - list of free rooms for [<date>] or for current calendar date" << endl;
	cout << "checkout - checkout <room number>" << endl;
	cout << "report - report of rooms <date from> <date to>" << endl;
	cout << "find - finds suitable room with free <number of beds> <date from> <date to>" << endl;
	cout << "find! - Urgently finds suitable room with free <number of beds> <date from> <date to> for a VIP client" << endl;
	cout << "unavailable - make unavailable <room number> <date from> <date to> <unavailability note>" << endl;
	cout << endl;
	cout << "open <file> - opens <file>" << endl;
	cout << "close - closes currently opened file" << endl;
	cout << "save - saves the currently open file" << endl;
	cout << "save as <file> - saves the currently open file in <file>" << endl;
	cout << "help - prints this information" << endl;
	cout << "exit - exists the program" << endl;
}




