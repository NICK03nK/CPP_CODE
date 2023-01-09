#include "myList.h"

// 测试push_back()和list的迭代器
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

// 测试insert()，复用版push_back()，push_front()
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

// 测试erase()，pop_back()，pop_front()
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

// 测试拷贝构造和赋值重载
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

// 测试迭代器operator->()
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

// 测试n个value构造list
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

// 测试front()和back()
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

// 测试list的反向迭代器
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

// 测试反向迭代器的const版本
void Test9()
{
	myList::list<int> li;

	li.push_back(1);
	li.push_back(2);
	li.push_back(3);
	li.push_back(4);

	testConst(li);
}

int main()
{
	Test9();

	return 0;
}