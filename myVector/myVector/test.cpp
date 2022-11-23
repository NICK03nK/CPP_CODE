#include "myVector.h"

// 测试reserve，push_back，operator[]，size，capacity函数的使用
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
	}
	cout << endl;

	for (auto e : v)
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