#include "SmartPtr.h"
#include <string>

void Test_auto_ptr()
{
	SmartPtr::auto_ptr<int> ap1(new int(1));
	SmartPtr::auto_ptr<int> ap2 = ap1;  // 资源管理权由ap1转移给ap2

	(*ap1)++;  // 导致空指针解引用错误
	(*ap2)++;
}

template<class T>
struct DeleteArray
{
	void operator()(T* ptr)
	{
		delete[] ptr;
	}
};

// 测试定制删除器
void Test_shared_ptr()
{
	SmartPtr::shared_ptr<string, DeleteArray<string>> sp(new string[10]);
}

int main()
{
	Test_shared_ptr();

	return 0;
}

//class Date
//{
//public:
//	Date(int year = 1, int month = 1, int day = 1)
//		:_year(year)
//		, _month(month)
//		, _day(day)
//	{}
//
//	void Func()
//	{}
//
//private:
//	int _year;
//	int _month;
//	int _day;
//};
//
//int main()
//{
//	SmartPtr::unique_ptr<Date> sp1(new Date(2023, 3, 22));
//
//	sp1->Func();
//
//	return 0;
//}