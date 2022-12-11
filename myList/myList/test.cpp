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

int main()
{
	Test4();

	return 0;
}