#pragma once

#include "Hotel.h"


class CommandRunner
{
	private:
		
	String currentFileName;
	Hotel hotel;
	
	public:
	CommandRunner();
			
	bool isFileOpen() const;
	
	void run();
	bool saveAs(const String& nameFile) const;
	void open(const String& nameFile);
	void close();
	void help();

};
