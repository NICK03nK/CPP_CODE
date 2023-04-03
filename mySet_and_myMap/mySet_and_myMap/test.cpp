#include "RBTree.h"
#include "mySet.h"
#include "myMap.h"
#include <string>

void test_set()
{
	int data[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	mySet::set<int> s;

	for (auto e : data)
	{
		s.insert(e);
	}

	mySet::set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}

void test_map()
{
	int data[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	myMap::map<int, int> m;

	for (auto e : data)
	{
		m.insert(make_pair(e, e));
	}

	myMap::map<int, int>::iterator it = m.begin();
	while (it != m.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}

void test_count()
{
	string arr[] = { "Æ»¹û", "Î÷¹Ï", "Ïã½¶", "²ÝÝ®", "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Ïã½¶", "Æ»¹û", "Ïã½¶" };
	myMap::map<string, int> countMap;

	for (auto& str : arr)
	{
		countMap[str]++;
	}

	for (auto& kv : countMap)
	{
		cout << kv.first << ":" << kv.second << endl;
	}
}

int main()
{
	//test_set();
	//test_map();
	test_count();

	return 0;
}