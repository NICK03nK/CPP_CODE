#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

namespace myString
{
	class string
	{
		friend ostream& operator<<(ostream& out, const myString::string& s);

		friend istream& operator>>(istream& in, myString::string& s);

	public:
		typedef char* iterator;

	public:
		string(const char* s = "");

		string(const string& s);

		string(string&& s);

		string& operator=(const string& s);
		//string& operator=(string s);  // ÏÖ´úÐ´·¨2

		string& operator=(string&& s);

		~string();

		iterator begin();

		iterator end();

		void push_back(char c);

		void append(const char* str);

		string& operator+=(char c);

		string& operator+=(const char* str);

		void clear();

		void swap(string& s);

		const char* c_str()const;

		size_t size()const;

		size_t capacity()const;

		bool empty()const;

		void resize(size_t n, char c = '\0');
		
		void reserve(size_t n);

		char& operator[](size_t index);

		const char& operator[](size_t index)const;

		bool operator<(const string& s);

		bool operator<=(const string& s);

		bool operator>(const string& s);

		bool operator>=(const string& s);

		bool operator==(const string& s);

		bool operator!=(const string& s);

		size_t find(char c, size_t pos = 0) const;

		size_t find(const char* s, size_t pos = 0) const;

		string& insert(size_t pos, char c);

		string& insert(size_t pos, const char* str);

		string& erase(size_t pos, size_t len = npos);

	private:
		char* _str;
		size_t _size;
		size_t _capacity;

		const static size_t npos = -1;
	};

	ostream& operator<<(ostream& out, const myString::string& s);

	istream& operator>>(istream& in, myString::string& s);
}