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

int main()
{
	Test1();

	return 0;
}