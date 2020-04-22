#pragma once
#include <iostream>
using namespace std;

class String {
	private:
		char* arr;
		size_t size;
	
		
	public:
		String();
		String(const char* str);
		String(const String& other);
		String& operator= (const String& other);
		~String();
		
		bool operator== (const String& other) const;
		char& operator[](size_t index);
		const char& operator[](size_t index) const;
		void print() const;
		
		friend std::ostream& operator<< (std::ostream& out, const String& other);
};