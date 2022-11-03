#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

namespace myString
{
	class string
	{
	public:
		typedef char* iterator;

	public:
		string(const char* s = "");

		string(const string& s);

		string& operator=(const string& s)
		{
			_size = s._size;
			_capacity = s._capacity;
			_str = new char[_capacity + 1];

			strcpy(_str, s._str);

			return *this;
		}

		~string();

		iterator begin();

		iterator end();

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			
			return _str[pos];
		}

		void push_back(char c);

		void append(const char* str);

		string& operator+=(char c)
		{
			push_back(c);

			return *this;
		}

		string& operator+=(const char* str)
		{
			append(str);

			return *this;
		}

		void clear();

		void swap(string& s);

		const char* c_str()const;

		size_t size()const;

		size_t capacity()const;

		bool empty()const;

		void resize(size_t n, char c = '\0');
		
		void reserve(size_t n);

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}