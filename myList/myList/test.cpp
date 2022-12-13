#include "myList.h"

// ²âÊÔpush_back()ºÍlistµÄµü´úÆ÷
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

// ²âÊÔinsert()£¬¸´ÓÃ°æpush_back()£¬push_front()
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

// ²âÊÔerase()£¬pop_back()£¬pop_front()
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

// ²âÊÔ¿½±´¹¹ÔìºÍ¸³ÖµÖØÔØ
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

// ²âÊÔµü´úÆ÷operator->()
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

int main()
{
	Test5();

	return 0;
}