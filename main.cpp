#include <iostream>
#include "Hotel.h"
#include "CommandRunner.h"
#include <fstream>

using namespace std;


int main() 
{
	Hotel h;
	CommandRunner runner;
	runner.setHotel(&h);
	runner.run();
	

	//https://github.com/mgitova/Hotel_Project_C-
	//system("pause");
	return 0;
}
