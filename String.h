#pragma once
#include <iostream>
#include <sstream> //https://www.cplusplus.com/reference/sstream/istringstream/istringstream/
#include "Vector.h"
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
		
		static Vector<String> splitBySpace(const String& line);
	static int stringToInt(const String& s, bool& isValid);
		
		bool operator== (const String& other) const;
		bool operator!= (const String& other) const;
		char& operator[](size_t index);
		const char& operator[](size_t index) const;
		String operator+(const String& other) const;
		String operator+(char c) const;
		
		size_t getSize() const;
		const char* getStr() const;
		
		
		friend std::ostream& operator<< (std::ostream& out, const String& other);
		friend std::istream& operator>> (std::istream& in, String& other);
};
