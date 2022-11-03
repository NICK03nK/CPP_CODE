#define _CRT_SECURE_NO_WARNINGS 1

#include "myString.h"

myString::string::string(const char* s)
{
	_size = strlen(s);
	_capacity = _size;
	_str = new char[_capacity + 1];

	strcpy(_str, s);
}

myString::string::string(const string& s)
{
	_size = s._size;
	_capacity = s._capacity;
	_str = new char[_capacity + 1];

	strcpy(_str, s._str);
}

myString::string::~string()
{
	//cout << "myString::string::~string()" << endl;

	_size = _capacity = 0;
	delete[] _str;
}

myString::string::iterator myString::string::begin()
{
	return _str;
}

myString::string::iterator myString::string::end()
{
	return _str + _size;
}

void myString::string::push_back(char c)
{
	if (_size == _capacity)
	{
		myString::string::reserve(_capacity * 2);
	}

	_str[_size] = c;
	++_size;
	_str[_size] = '\0';
}

void myString ::string::append(const char* str)
{
	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		myString::string::reserve(_size + len);
	}

	while (*str != '\0')
	{
		_str[_size] = *str;
		++_size;
		++str;
	}
	_str[_size] = '\0';
}

void myString::string::clear()
{
	_str[0] = '\0';
	_size = 0;
}

void myString::string::swap(string& s)
{
	string tmpStr(*this);

	if (s._size > _size)
	{
		myString::string::reserve(s._size);
	}
	strcpy(_str, s._str);
	_size = s._size;
	_capacity = s._capacity;

	if (s._size < tmpStr._size)
	{
		s.reserve(tmpStr._size);
	}
	strcpy(s._str, tmpStr._str);
	s._size = tmpStr._size;
	s._capacity = tmpStr._capacity;

	// 以下方法实现swap会造成内存泄露
	//string tmpStr = *this;
	////char* test = _str;    // 指针test用于验证用此方法会造成内存泄露(成员变量_str原先指向的空间没被释放)
	//*this = s;
	//s = tmpStr;
}

const char* myString::string::c_str()const
{
	return _str;
}

size_t myString::string::size()const
{
	return _size;
}

size_t myString::string::capacity()const
{
	return _capacity;
}

bool myString::string::empty()const
{
	return _size == 0;
}

void myString::string::resize(size_t n, char c = '\0')
{

}

void myString::string::reserve(size_t n)
{
	char* tmp = new char[n + 1];

	strcpy(tmp, _str);
	delete[] _str;
	_str = tmp;
	_capacity = n;
}