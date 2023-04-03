#include "myUnordered_set.h"
#include "myUnordered_map.h"

void testUnordered_set()
{
	myUnordered_set::unordered_set<int> us;
	
	us.insert(3);
	us.insert(8);
	us.insert(60);
	us.insert(33);
	us.insert(2);
	us.insert(7);

	myUnordered_set::unordered_set<int>::iterator it = us.begin();
	while (it != us.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : us)
	{
		cout << e << " ";
	}
	cout << endl;
}

void testUnordered_map()
{
	string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };
	myUnordered_map::unordered_map<string, int> um;

	for (const auto& str : arr)
	{
		um[str]++;
	}

	myUnordered_map::unordered_map<string, int>::iterator it = um.begin();
	while (it != um.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}

int main()
{
	//testUnordered_set();
	testUnordered_map();

	return 0;
}