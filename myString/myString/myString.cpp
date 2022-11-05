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

myString::string& myString::string::operator=(const string& s)
{
	// 以下方式实现会导致内存泄露
	/*if (this != &s)
	{
		_size = s._size;
		_capacity = s._capacity;
		_str = new char[_capacity + 1];

		strcpy(_str, s._str);
	}*/

	if (this != &s)
	{
		char* tmp = new char[s._capacity + 1];
		strcpy(tmp, s._str);

		delete[] _str;
		_str = tmp;

		_size = s._size;
		_capacity = s._capacity;
	}

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

	// 以下方法实现swap会造成内存泄露(仅针对第一种方法实现opreator=)
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

//bool myString::string::operator<=(const string& s)
//{
//
//}

bool myString::string::operator>(const string& s)
{
	return strcmp(_str, s._str) > 0;
}

//bool operator>=(const string& s)
//{
//
//}

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

	char* tmp = new char[_capacity + 2];

	if (_size + 1 > _capacity)
	{
		reserve(_capacity + 1);
	}

	int i = 0;
	int j = 0;
	while (i < _size)
	{
		if (i == pos)
		{
			tmp[j++] = c;
			tmp[j++] = _str[i++];
		}
		else
		{
			tmp[j++] = _str[i++];
		}
	}

	strncpy(_str, tmp, j);
	_size += 1;
	_str[_size] = '\0';

	delete[] tmp;

	return *this;
}

myString::string& myString::string::insert(size_t pos, const char* str)
{
	assert(pos <= _size);

	int len = strlen(str);
	char* tmp = new char[_size + len + 1];

	if (_size + len > _capacity)
	{
		reserve(_size + len);
	}

	int i = 0;
	int j = 0;
	while (i < _size)
	{
		if (i == pos)
		{
			strcpy(tmp + i, str);
			j += len;
			tmp[j++] = _str[i++];
		}
		else
		{
			tmp[j++] = _str[i++];
		}
	}

	strncpy(_str, tmp, j);
	_size += len;
	_str[_size] = '\0';

	delete[] tmp;

	return *this;
}

myString::string& myString::string::erase(size_t pos, size_t len)
{
	
}