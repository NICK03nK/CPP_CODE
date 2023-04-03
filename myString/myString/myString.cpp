#define _CRT_SECURE_NO_WARNINGS 1

#include "myString.h"

myString::string::string(const char* s)
{
	_size = strlen(s);
	_capacity = _size;
	_str = new char[_capacity + 1];

	strcpy(_str, s);
}

// 传统写法
//myString::string::string(const string& s)
//{
//	_size = s._size;
//	_capacity = s._capacity;
//	_str = new char[_capacity + 1];
//
//	strcpy(_str, s._str);
//}

// 现代写法
myString::string::string(const string& s)
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
{
	myString::string tmp(s._str);  // 调用构造函数
	/*std::swap(_str, tmp._str);
	std::swap(_size, tmp._size);
	std::swap(_capacity, tmp._capacity);*/
	swap(tmp);
}

// 移动构造
myString::string::string(string&& s)
	:_str(nullptr)
	, _size(0)
	, _capacity(0)
{
	swap(s);
}

// 传统写法
//myString::string& myString::string::operator=(const string& s)
//{
//	// 以下方式实现会导致内存泄露
//	/*if (this != &s)
//	{
//		_size = s._size;
//		_capacity = s._capacity;
//		_str = new char[_capacity + 1];
//
//		strcpy(_str, s._str);
//	}*/
//
//	if (this != &s)
//	{
//		char* tmp = new char[s._capacity + 1];
//		strcpy(tmp, s._str);
//
//		delete[] _str;
//		_str = tmp;
//
//		_size = s._size;
//		_capacity = s._capacity;
//	}
//
//	return *this;
//}

// 现代写法1
myString::string& myString::string::operator=(const string& s)
{
	if (this != &s)
	{
		myString::string tmp(s._str);
		swap(tmp);
	}

	return *this;
}

// 现代写法2
//myString::string& myString::string::operator=(string s)
//{
//	swap(s);
//	return *this;
//}

// 移动赋值
myString::string& myString::string::operator=(string&& s)
{
	swap(s);
	return *this;
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
		size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
		reserve(newCapacity);
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

myString::string& myString::string::operator+=(char c)
{
	push_back(c);

	return *this;
}

myString::string& myString::string::operator+=(const char* str)
{
	append(str);

	return *this;
}

void myString::string::clear()
{
	_str[0] = '\0';
	_size = 0;
}

void myString::string::swap(string& s)
{
	std::swap(_str, s._str);
	std::swap(_size, s._size);
	std::swap(_capacity, s._capacity);
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

void myString::string::resize(size_t n, char c)
{
	if (n < _size)
	{
		_size = n;
		_str[_size] = '\0';
	}
	else if (n > _size && n <= _capacity)
	{
		while (_size != n)
		{
			_str[_size] = c;
			++_size;
		}
		_str[_size] = '\0';
	}
	else if (n > _capacity)
	{
		reserve(n);

		while (_size != n)
		{
			_str[_size] = c;
			++_size;
		}
		_str[_size] = '\0';
	}
}

void myString::string::reserve(size_t n)
{
	if (n > _capacity)
	{
		char* tmp = new char[n + 1];

		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
		_capacity = n;
	}
}

char& myString::string::operator[](size_t index)
{
	assert(index < _size);

	return _str[index];
}

const char& myString::string::operator[](size_t index)const
{
	assert(index < _size);

	return _str[index];
}

bool myString::string::operator<(const string& s)
{
	return strcmp(_str, s._str) < 0;
}

bool myString::string::operator<=(const string& s)
{
	return *this < s || *this == s;
}

bool myString::string::operator>(const string& s)
{
	return strcmp(_str, s._str) > 0;
}

bool myString::string::operator>=(const string& s)
{
	return *this > s || *this == s;
}

bool myString::string::operator==(const string& s)
{
	return strcmp(_str, s._str) == 0;
}

bool myString::string::operator!=(const string& s)
{
	return strcmp(_str, s._str) != 0;
}

size_t myString::string::find(char c, size_t pos) const
{
	assert(pos < _size);

	for (size_t i = pos; i < _size; ++i)
	{
		if (_str[i] == c)
		{
			return i;
		}
	}

	return npos;
}

size_t myString::string::find(const char* s, size_t pos) const
{
	assert(pos < _size);

	if (strstr(_str + pos, s))
	{
		return strstr(_str + pos, s) - _str;
	}
	else
	{
		return npos;
	}
}

myString::string& myString::string::insert(size_t pos, char c)
{
	assert(pos <= _size);

	if (_size == _capacity)
	{
		size_t newCapacity = _capacity == 0 ? 4 : _capacity * 2;
		reserve(newCapacity);
	}

	size_t end = _size + 1;
	while (end > pos)
	{
		_str[end] = _str[end - 1];
		--end;
	}

	_str[pos] = c;
	++_size;

	return *this;
}

myString::string& myString::string::insert(size_t pos, const char* str)
{
	assert(pos <= _size);

	size_t len = strlen(str);
	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}

	size_t end = _size + len;
	while (end > pos + len - 1)
	{
		_str[end] = _str[end - len];
		--end;
	}

	strncpy(_str + pos, str, len);
	_size += len;

	return *this;
}

myString::string& myString::string::erase(size_t pos, size_t len)
{
	assert(pos < _size);

	if (len == npos || len >= _size - pos)
	{
		_str[pos] = '\0';
		_size = pos;
	}
	else
	{
		strcpy(_str + pos, _str + pos + len);
		_size -= len;
	}

	return *this;
}

ostream& myString::operator<<(ostream& out, const myString::string& s)
{
	for (size_t i = 0; i < s._size; ++i)
	{
		out << s[i];
	}

	return out;
}

istream& myString::operator>>(istream& in, myString::string& s)
{
	s.clear();

	char c = in.get();
	while (c != ' ' && c != '\n')
	{
		s += c;
		c = in.get();
	}

	return in;
}