#pragma once

#include <iostream>
using namespace std;

namespace myIterator
{
	template<class Iterator, class Ref, class Ptr>
	class reverse_iterator
	{
		typedef reverse_iterator<Iterator, Ref, Ptr> Self;

	public:
		reverse_iterator(Iterator it)
			:_cur(it)
		{}

		reverse_iterator(const Self& rit)
			:_cur(rit._cur)
		{}

		Ref operator*()
		{
			Iterator tmp = _cur;
			return *(--tmp);
		}

		Ptr operator->()
		{
			return &(operator*());
		}

		Self& operator++()
		{
			--_cur;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);
			--_cur;
			return tmp;
		}

		Self& operator--()
		{
			++_cur;
			return *this;
		}

		Self operator--(int)
		{
			Self tmp(*this);
			++_cur;
			return tmp;
		}

		bool operator!=(const Self& rit) const
		{
			return _cur != rit._cur;
		}

		bool operator==(const Self& rit) const
		{
			return _cur == rit._cur;
		}

	private:
		Iterator _cur;
	};
}