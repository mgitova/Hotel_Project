#include "String.h"
#include <cstring>
#include <cassert>

String:: String ()
{
	this->size = 0;
	this->arr = new char [this->size + 1];
	this->arr[0] = '\0';
}

String:: String (const char* str)
{
	this->size = strlen(str);
	this->arr = new char [this->size + 1];
	strcpy(this->arr,str);
}

String:: String (const String& other)
{
	this->size = other.size;
	this->arr = new char [this->size + 1];
	this->arr[this->size] = '\0';
	
	for (int i = 0; i < this->size; i++)
	{
		this->arr[i] = other.arr[i];
	}
}

String& String::operator=(const String& other)
{
	if(this != &other)
	{
		this->size = other.size;
		delete [] this->arr;
		this->arr = new char [this->size + 1];
		this->arr[this->size] = '\0';
	
		for (int i = 0; i < this->size; i++)
		{
			this->arr[i] = other.arr[i];
		}	
	}
	return *this;
}

String::~String()
{
	delete [] this->arr;
}

bool String::operator== (const String& other) const 
{
	return strcmp(this->arr,other.arr) == 0;
}

char& String::operator[] (size_t index)
{
	assert(index < this->size);
	return this->arr[index];
}

const char& String::operator[] (size_t index) const
{
	assert(index < this->size);
	return this->arr[index];
}

void String::print() const 
{
	std::cout << this->arr << std::endl;
}

std::ostream& operator<< (std::ostream& out, const String& other)
{
	out << other.arr;
	return out;
}

