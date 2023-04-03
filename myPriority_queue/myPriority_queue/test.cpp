#include <iostream>
#include <vector>
using namespace std;

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}
	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}
	friend ostream& operator<<(ostream& _cout, const Date& d)
	{
		_cout << d._year << "-" << d._month << "-" << d._day;
		return _cout;
	}
private:
	int _year;
	int _month;
	int _day;
};

#include "myPriority_queue.h"

//class PDLess
//{
//public:
//	bool operator()(const Date* d1, const Date* d2)
//	{
//		return *d1 < *d2;
//	}
//};
//
//class PDGreater
//{
//public:
//	bool operator()(const Date* d1, const Date* d2)
//	{
//		return *d1 > *d2;
//	}
//};

void TestPriorityQueue()
{
	myPriority_queue::priority_queue<Date> q1;
	q1.push(Date(2018, 10, 29));
	q1.push(Date(2018, 10, 28));
	q1.push(Date(2018, 10, 30));
	cout << q1.top() << endl;


	myPriority_queue::priority_queue<Date, vector<Date>, greater<Date>> q2;
	q2.push(Date(2018, 10, 29));
	q2.push(Date(2018, 10, 28));
	q2.push(Date(2018, 10, 30));
	cout << q2.top() << endl;


	// 若此处不使用仿函数特殊处理Date*的情况，则在建堆的时候默认按照地址来比较大小
	// 因为每次new出来的地址都是随机的，所以按照地址来比较没有意义，无法达到预期要
	// 所以需要使用仿函数来特殊处理
	/*myPriority_queue::priority_queue<Date*, vector<Date*>, PDLess> q3;
	q3.push(new Date(2018, 10, 29));
	q3.push(new Date(2018, 10, 28));
	q3.push(new Date(2018, 10, 30));
	cout << *(q3.top()) << endl;


	myPriority_queue::priority_queue<Date*, vector<Date*>, PDGreater> q4;
	q4.push(new Date(2018, 10, 29));
	q4.push(new Date(2018, 10, 28));
	q4.push(new Date(2018, 10, 30));
	cout << *(q4.top()) << endl;*/


	// 使用模板特化解决上述问题
	myPriority_queue::priority_queue<Date*> q3;
	q3.push(new Date(2018, 10, 29));
	q3.push(new Date(2018, 10, 28));
	q3.push(new Date(2018, 10, 30));
	cout << *(q3.top()) << endl;


	myPriority_queue::priority_queue<Date*, vector<Date*>, myPriority_queue::greater<Date*>> q4;
	q4.push(new Date(2018, 10, 29));
	q4.push(new Date(2018, 10, 28));
	q4.push(new Date(2018, 10, 30));
	cout << *(q4.top()) << endl;
}

int main()
{
	TestPriorityQueue();

	return 0;
}

//int main()
//{
//	//myPriority_queue::priority_queue<int> pq;  // 建大堆 --> 数值大的优先级高
//	myPriority_queue::priority_queue<int, vector<int>, greater<int>> pq;  // 建小堆 --> 数值小的优先级高
//
//	pq.push(1);
//	pq.push(3);
//	pq.push(10);
//	pq.push(0);
//	pq.push(6);
//
//	while (!pq.empty())
//	{
//		cout << pq.top() << " ";
//		pq.pop();
//	}
//	cout << endl;
//
//	return 0;
//}