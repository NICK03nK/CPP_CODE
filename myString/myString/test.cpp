#define _CRT_SECURE_NO_WARNINGS 1

#include "myString.h"

// 测试字符串类型构造函数
void Test_1()
{
	myString::string s1("hello nK!");

	cout << s1.c_str() << endl;
}

// 测试string类类型构造函数
void Test_2()
{
	myString::string s1("hello nK!");

	myString::string s2(s1);

	cout << s2.c_str() << endl;
}

// 测试赋值运算符重载
void Test_3()
{
	myString::string s1("hello nK!");

	//myString::string s2 = s1;
	//myString::string s2 = "test myString";

	myString::string s2, s3, s4;

	s2 = s3 = s4 = s1;

	cout << s2.c_str() << endl;
	cout << s3.c_str() << endl;
	cout << s4.c_str() << endl;
}

// 测试析构函数
void Test_4()
{
	myString::string s1("hello nK!");

	if (1)
	{
		myString::string s2, s3, s4;

		s2 = s3 = s4 = s1;

		cout << s2.c_str() << endl;
		cout << s3.c_str() << endl;
		cout << s4.c_str() << endl;
	}

	cout << "test" << endl;
}

// 测试push_back和+=一个字符
void Test_5()
{
	myString::string s1("hello nK!");

	s1.push_back('!');
	s1.push_back('K');
	s1.push_back('n');

	s1 += '!';
	s1 += '-';
	
	cout << s1.c_str() << endl;
}

// 测试append和+=一个字符串
void Test_6()
{
	myString::string s1("hello nK!");

	const char* s2 = "zbc";
	
	s1.append(s2);

	s1 += " cbz";

	cout << s1.c_str() << endl;
}

// 测试clear
void Test_7()
{
	myString::string s1("hello nK!");

	s1.clear();

	cout << s1.c_str();

	cout << "test" << endl;
}

// 测试swap
void Test_8()
{
	myString::string s1("hello");
	myString::string s2("nK!!!!!!");
	
	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;

	s1.swap(s2);
	cout << "After swap" << endl;

	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;
}

// 测试size和capacity
void Test_9()
{
	myString::string s1 = "hello nK!";

	cout << s1.size() << endl;
	cout << s1.capacity() << endl;
}

// 测试empty
void Test_10()
{
	//myString::string s1("hello nK!!!");
	myString::string s1;

	cout << s1.empty() << endl;
}

// 测试reserve
void Test_11()
{
	myString::string s1("hello world");
	
	// 1. n < _size
	//s1.resize(5);

	// 2. _size < n <= _capacity
	/*s1.reserve(15);
	s1.resize(13, '!');*/

	// 3. n > capacity
	s1.reserve(13);
	s1.resize(15, '!');

	cout << s1.c_str() << endl;
}

// 测试find_c
void Test_12()
{
	myString::string s1("hello nK!");

	//size_t pos = s1.find('!');
	size_t pos = s1.find('l', 3);

	cout << pos << endl;
}

// 测试find_subStr
void Test_13()
{
	//myString::string s1("helwlowbitnK!");
	myString::string s1("helwwbiowbitnK!");

	const char* s = "wbi";
	//size_t pos = s1.find(s);
	//size_t pos = s1.find(s, 5);
	size_t pos = s1.find(s, 25);

	/*const char* s = "wi";
	size_t pos = s1.find(s);*/

	cout << pos << endl;
}

// 测试insert_c
void Test_14()
{
	myString::string s1("hello nK!");

	s1.insert(4, 'x');
	//s1.insert(24, 'x');

	/*s1.reserve(20);
	s1.insert(4, 'x');*/

	cout << s1.c_str() << endl;
}

// 测试inser_str
void Test_15()
{
	myString::string s1("hello nK!");



	cout << s1.c_str() << endl;
}

int main()
{
	Test_15();

	return 0;
}