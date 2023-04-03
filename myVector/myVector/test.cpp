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

// 测试erase()
void Test4()
{
	myVector::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);


	/*myVector::vector<int>::iterator it = find(v.begin(), v.end(), 4);
	if (it != v.end())
	{
		it = v.erase(it);
	}
	cout << *it << endl;*/

	myVector::vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (auto e : v)
	{
		cout << e << " ";
	}
	cout << endl;
}

// 测试拷贝构造函数，迭代器构造函数，赋值重载函数
void Test5()
{
	myVector::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	//myVector::vector<int> v1(v);  // 拷贝构造
	myVector::vector<int> v1 = v;  // 拷贝构造
	v1.push_back(40);
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;

	myVector::vector<int> v2;
	v2.push_back(10);
	v2.push_back(20);

	v1 = v2;
	for (auto e : v1)
	{
		cout << e << " ";
	}
	cout << endl;
}

// 测试n个value的构造函数
void Test6()
{
	myVector::vector<int> vi(10, 1);
	for (auto e : vi)
	{
		cout << e << " ";
	}
	cout << endl;
}

// 测试解决vector<自定义类型>浅拷贝问题(以 vector<vector<int>> 为例)
void Test7()
{
	myVector::vector<myVector::vector<int>> vvi;
	
	myVector::vector<int> vi;
	vi.resize(4, 1);

	vvi.push_back(vi);
	vvi.push_back(vi);
	vvi.push_back(vi);
	vvi.push_back(vi);
	vvi.push_back(vi);

	for (int i = 0; i < vvi.size(); ++i)
	{
		for (int j = 0; j < vvi[i].size(); ++j)
		{
			cout << vvi[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// 测试vector的反向迭代器
void Test8()
{
	myVector::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	myVector::vector<int>::reverse_iterator rit = v.rbegin();
	while (rit != v.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}

void testConst(const myVector::vector<int> v)
{
	myVector::vector<int>::const_reverse_iterator rit = v.rbegin();
	while (rit != v.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;
}

// 测试反向迭代器的const版本
void Test9()
{
	myVector::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	testConst(v);
}

// 测试c++11 initializer_list 初始化vector
void Test10()
{
	myVector::vector<int> vt = { 1,2,3,4,5 };

	for (auto e : vt)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	Test10();

	return 0;
}