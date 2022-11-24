#include "myVector.h"

// 测试reserve()，push_back()，operator[]，size()，capacity()
void Test1()
{
	myVector::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	for (int i = 0; i < v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	myVector::vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

// 测试resize()
void Test2()
{
	myVector::vector<int> v;
	
	v.resize(10, -1);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	v.resize(5);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;

	v.resize(15);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

// 测试insert()
void Test3()
{
	myVector::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	//v.insert(v.begin() + 2, 30);
	/*v.insert(v.begin(), 0);
	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;*/

	// 指定数据前插入数据
	myVector::vector<int>::iterator it = find(v.begin(), v.end(), 4);
	if (it != v.end())
	{
		v.insert(it, (*it) * 10);
	}

	//(*it)++;  // <不要这样使用it> 当插入数据需要扩容时，it迭代器指向的地址已经因扩容而被释放了，所以此处it迭代器失效

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	Test3();

	return 0;
}