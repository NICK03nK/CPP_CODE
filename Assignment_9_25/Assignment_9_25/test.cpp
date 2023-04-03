#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>

using namespace std;

class Date
{
public:
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month)
	{
		static int day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

		if (month == 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0))
		{
			return day[2] + 1;
		}

		return day[month];
	}

	// ȫȱʡ�Ĺ��캯��
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	// �������캯��
    // d2(d1)
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}

	// ��ֵ���������
    // d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;

		return *this;
	}

	// ��������
	~Date()
	{
		;
	}

	// ����+=����
	Date& operator+=(int day)
	{
		if (day < 0)
		{
			return *this -= -day;
		}

		_day += day;

		while (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;

			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}

		return *this;
	}

	// ����+����
	Date operator+(int day)
	{
		Date ret(*this);

		ret += day;

		return ret;
	}

	// ����-����
	Date operator-(int day)
	{
		Date ret(*this);

		ret -= day;

		return ret;
	}

	// ����-=����
	Date& operator-=(int day)
	{
		if (day < 0)
		{
			return *this += -day;
		}

		_day -= day;

		while (_day <= 0)
		{
			_month--;

			if (_month == 0)
			{
				_year--;
				_month = 12;
			}

			_day += GetMonthDay(_year, _month);
		}

		return *this;
	}

	// ǰ��++
	Date& operator++()
	{
		_day += 1;

		if (_day > GetMonthDay(_year, _month))
		{
			_day -= GetMonthDay(_year, _month);
			_month++;

			if (_month == 13)
			{
				_year++;
				_month = 1;
			}
		}

		return *this;
	}

	// ����++  C++�涨���ü�һ��int���͵Ĳ���
	Date operator++(int)
	{
		Date ret(*this);

		++(*this);

		return ret;
	}

	// ����--  C++�涨���ü�һ��int���͵Ĳ���
	Date operator--(int)
	{
		Date ret(*this);

		--(*this);

		return ret;
	}

	// ǰ��--
	Date& operator--()
	{
		_day -= 1;

		if (_day == 0)
		{
			if (_month == 1)
			{
				_day = GetMonthDay(_year, 12);
			}
			else
			{
				_day = GetMonthDay(_year, _month - 1);
			}

			_month--;

			if (_month == 0)
			{
				_year--;
				_month = 12;
			}
		}

		return *this;
	}

	// >���������
	bool operator>(const Date& d)
	{
		if (_year > d._year)
		{
			return true;
		}
		else if (_year == d._year && _month > d._month)
		{
			return true;
		}
		else if (_year == d._year && _month == d._month && _day > d._day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// ==���������
	bool operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}

	// >=���������
	bool operator>=(const Date& d)
	{
		return *this > d || *this == d;
	}

	// <���������
	bool operator<(const Date& d)
	{
		if (_year < d._year)
		{
			return true;
		}
		else if (_year == d._year && _month < d._month)
		{
			return true;
		}
		else if (_year == d._year && _month == d._month && _day < d._day)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// <=���������
	bool operator<=(const Date& d)
	{
		return *this < d || *this == d;
	}

	// !=���������
	bool operator!=(const Date& d)
	{
		return _year != d._year && _month != d._month && _day != d._day;
	}

	// ����-���� ��������
	int operator-(const Date& d)
	{
		Date earlier(*this);
		Date later(d);
		if (earlier > later)
		{
			Date tmp = earlier;
			earlier = later;
			later = tmp;
		}

		int i = 0;
		for (i = 0;; i++)
		{
			if (earlier + i == later)
			{
				break;
			}
		}

		return i;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d1(2022, 9, 25);
	Date d2(d1);

	Date d3;
	d2 = d3;

	d2 = d1 + 7;

	//d1 -= 30;
	
	//Date d4(2022, 1, 1);
	//d4 -= 2;

	Date d5(2022, 12, 31);
	d1 = ++d5;

	Date d6(2022, 9, 25);
	d1 = d6++;

	Date d7(2022, 1, 1);
	d1 = --d7;

	Date d8(2022, 1, 1);
	d1 = d8--;

	int flag = d2 > d1;

	Date d9(d8);
	//flag = d9 == d1;

	flag = d9 >= d1;

	Date d10(2022, 9, 26);
	d9 = d10 - 513;

	Date d11(2023, 5, 30);
	Date d12(2022, 9, 26);
	int d = d12 - d11;

	return 0;
}