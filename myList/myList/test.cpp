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

int main()
{
	Test2();

	return 0;
}