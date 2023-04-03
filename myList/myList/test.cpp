#include "myList.h"
#include <string>

// ����push_back()��list�ĵ�����
void Test1()
{
	myList::list<int> li;
	
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	myList::list<int>::iterator it = li.begin();
	while (it != li.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;
}

// ����insert()�����ð�push_back()��push_front()
void Test2()
{
	myList::list<int> li;

	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	li.push_front(5);
	li.push_front(6);

	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;

	myList::list<int>::iterator it = li.begin();
	int cnt = 2;
	while (cnt--)
	{
		++it;
	}
	li.insert(it, 10);

	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;
}

// ����erase()��pop_back()��pop_front()
void Test3()
{
	myList::list<int> li;

	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	li.push_front(5);
	li.push_front(6);

	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;

	li.pop_back();
	li.pop_back();

	li.pop_front();
	li.pop_front();

	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;
}

// ���Կ�������͸�ֵ����
void Test4()
{
	myList::list<int> li;

	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);
	cout << "li :" << endl;
	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;

	myList::list<int> li1(li);
	cout << "li1 :" << endl;
	for (auto e : li1)
	{
		cout << e << " ";
	}
	cout << endl;

	li1.push_back(50);
	li1.push_back(60);
	cout << "li1 :" << endl;
	for (auto e : li1)
	{
		cout << e << " ";
	}
	cout << endl;

	li = li1;
	cout << "li :" << endl;
	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;
}

struct Pos
{
	int _row;
	int _col;

	Pos(int row = 0, int col = 0)
		:_row(row)
		, _col(col)
	{}
};

// ���Ե�����operator->()
void Test5()
{
	myList::list<Pos> lt;
	Pos p1(1, 1);
	lt.push_back(p1);
	lt.push_back(p1);
	lt.push_back(p1);
	lt.push_back(Pos(2, 2));
	lt.push_back(Pos(3, 3));

	myList::list<Pos>::iterator it = lt.begin();
	while (it != lt.end())
	{
		//cout << (*it)._row << ":" << (*it)._col << endl;
		cout << it->_row << ":" << it->_col << endl;
		//cout << it.operator->()->_row << ":" << it.operator->()->_col << endl;
		++it;
	}
	cout << endl;
}

// ����n��value����list
void Test6()
{
	myList::list<int> li(4, 10);

	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;

	li.push_back(3);

	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;
}

void test(const myList::list<int> li)
{
	cout << li.front() << endl;
	cout << li.back() << endl;
}

// ����front()��back()
void Test7()
{
	myList::list<int> li;

	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	cout << li.front() << endl;
	cout << li.back() << endl;

	test(li);
}

// ����list�ķ��������
void Test8()
{
	myList::list<int> li;

	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	myList::list<int>::reverse_iterator rit = li.rbegin();
	while (rit != li.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}

void testConst(const myList::list<int> li)
{
	myList::list<int>::const_reverse_iterator rit = li.rbegin();
	while (rit != li.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}

// ���Է����������const�汾
void Test9()
{
	myList::list<int> li;

	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	testConst(li);
}

// ����c++11 initializer_list ��ʼ��list
void Test10()
{
	myList::list<int> li = { 1,2,3,4,5 };

	for (auto e : li)
	{
		cout << e << " ";
	}
	cout << endl;
}

// ������ֵ���ð汾��push_back()
void Test11()
{
	myList::list<string> lt;
	string s1("11111");
	lt.push_back(move(s1));
}

// ������ֵ����ʵ�ֵ��ƶ�����
void Test12()
{
	myList::list<string> lt1;
	string s1("11111");
	lt1.push_back(s1);

	myList::list<string> lt2(move(lt1));
}

// ������ֵ����ʵ�ֵ��ƶ���ֵ
void Test13()
{
	myList::list<string> lt1;
	string s1("11111");
	lt1.push_back(s1);

	myList::list<string> lt2;
	lt2 = move(lt1);
}

int main()
{
	Test13();

	return 0;
}