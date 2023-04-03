#pragma once

#include <iostream>
#include <deque>
#include <assert.h>
using namespace std;

namespace myQueue
{
	template<class T, class Con = deque<T>>
	class queue
	{
	public:
		queue()
		{}

		void push(const T& x)
		{
			_c.push_back(x);
		}

		void pop()
		{
			assert(!empty());

			_c.pop_front();
		}

		T& back()
		{
			assert(!empty());

			return _c.back();
		}

		const T& back() const
		{
			assert(!empty());

			return _c.back();
		}

		T& front()
		{
			assert(!empty());

			return _c.front();
		}

		const T& front() const
		{
			assert(!empty());

			return _c.front();
		}

		size_t size() const
		{
			return _c.size();
		}


		bool empty() const
		{
			return _c.empty();
		}

	private:
		Con _c;
	};
}