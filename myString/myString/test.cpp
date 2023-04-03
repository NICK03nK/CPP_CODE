#define _CRT_SECURE_NO_WARNINGS 1

#include "myString.h"

// �����ַ������͹��캯��
void Test_1()
{
	myString::string s1("hello nK!");

	cout << s1.c_str() << endl;
}

// ���Կ������캯��
void Test_2()
{
	myString::string s1("hello nK!");

	myString::string s2(s1);

	cout << s2.c_str() << endl;
}

// ���Ը�ֵ���������
void Test_3()
{
	myString::string s1("hello nK!");

	/*myString::string s2 = s1;*/
	myString::string s2 = "test myString";
	s2 = s1;

	/*myString::string s2, s3, s4;

	s2 = s3 = s4 = s1;

	cout << s2.c_str() << endl;
	cout << s3.c_str() << endl;
	cout << s4.c_str() << endl;*/
}

// ������������
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

// ����push_back��+=һ���ַ�
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

// ����append��+=һ���ַ���
void Test_6()
{
	myString::string s1("hello nK!");

	const char* s2 = "zbc";
	
	s1.append(s2);

	s1 += " cbz";

	cout << s1.c_str() << endl;
}

// ����clear
void Test_7()
{
	myString::string s1("hello nK!");

	s1.clear();

	cout << s1.c_str();

	cout << "test" << endl;
}

// ����swap
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

// ����size��capacity
void Test_9()
{
	myString::string s1 = "hello nK!";

	cout << s1.size() << endl;
	cout << s1.capacity() << endl;
}

// ����empty
void Test_10()
{
	//myString::string s1("hello nK!!!");
	myString::string s1;

	cout << s1.empty() << endl;
}

// ����reserve
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

// ����find_c
void Test_12()
{
	myString::string s1("hello nK!");

	//size_t pos = s1.find('!');
	size_t pos = s1.find('l', 3);

	cout << pos << endl;
}

// ����find_subStr
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

// ����insert_c
void Test_14()
{
	myString::string s1("hello nK!");

	s1.insert(4, 'x');
	//s1.insert(24, 'x');

	/*s1.reserve(20);
	s1.insert(4, 'x');*/

	cout << s1.c_str() << endl;
}

// ����inser_str
void Test_15()
{
	myString::string s1("hello nK!");

	//s1.insert(4, "xxx");
	//s1.insert(24, "xxx");

	s1.reserve(20);
	s1.insert(4, "xxxx");

	cout << s1.c_str() << endl;
}

// ����erase
void Test_16()
{
	myString::string s1("hello world!");
	
	s1.erase(5, 100);

	cout << s1.c_str() << endl;

	myString::string s2("hello hello world!");
	
	s2.erase(0, 6);

	cout << s2.c_str() << endl;
}

// ����operator<<��operator>>
void Test_17()
{
	myString::string s1("hello world!");

	cout << s1 << endl;
	cout << s1.c_str() << endl;

	s1.insert(5, '\0');

	cout << s1 << endl;
	cout << s1.c_str() << endl;

	myString::string s2;

	cin >> s1;
	cout << s1 << endl;

	cin >> s2;
	cout << s2 << endl;
}

// ������ֵ����ʵ�ֵ��ƶ�����
void Test_18()
{
	myString::string s1("hello world!");
	myString::string s2(move(s1));
}

// ������ֵ����ʵ�ֵ��ƶ���ֵ
void Test_19()
{
	myString::string s1("hello world!");
	myString::string s2;
	s2 = move(s1);
}

int main()
{
	Test_19();

	return 0;
}