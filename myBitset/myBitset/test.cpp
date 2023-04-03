#include "myBitset.h"

void Test1()
{
	myBitset::bitset<-1> bs;

	bs.set(1000);
	bs.set(1880);
	bs.set(101);
	bs.set(12);

	cout << bs.test(1000) << endl;
	cout << bs.test(12) << endl;
	cout << bs.test(101) << endl << endl;

	cout << bs.test(11) << endl;

	bs.reset(12);
	cout << bs.test(12) << endl;
}

// 给定100亿个整数，设计算法找到只出现一次的整数？
void Test2()
{
	int arr[] = { 1,2,3,4,1,2,3,4,4,3,2,1,5,6,7,8 };
	myBitset::twoBitSet<100> tbs;

	for (auto e : arr)
	{
		tbs.set(e);
	}

	tbs.PrintOnce();
}

void Test3()
{
	int arr1[] = { 1,2,3,3,4,5 };
	int arr2[] = { 1,1,4,6 };

	myBitset::bitset<10> bs1;
	myBitset::bitset<10> bs2;

	for (auto e : arr1)
	{
		bs1.set(e);
	}

	for (auto e : arr2)
	{
		bs2.set(e);
	}

	vector<int> vt;
	for (int i = 0; i <= 10; ++i)
	{
		if (bs1.test(i) && bs2.test(i))
		{
			vt.push_back(i);
		}
	}

	// 给两个文件，分别有100亿个整数，我们只有1G内存，如何找到两个文件交集？
	for (auto e : vt)
	{
		cout << e << " ";
	}
	cout << endl;
}

int main()
{
	//Test1();
	//Test2();
	Test3();

	return 0;
}