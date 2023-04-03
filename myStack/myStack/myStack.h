#pragma once

#include <iostream>
#include <deque>
#include <assert.h>
using namespace std;

namespace myStack
{
	template<class T, class Con = deque<T>>
	class stack
	{
	public:
		stack()
		{}

		void push(const T& x)
		{
			_c.push_back(x);
		}

		void pop()
		{
			assert(!empty());

			_c.pop_back();
		}

		T& top()
		{
			assert(!empty());

			return _c.back();
		}

		const T& top() const
		{
			assert(!empty());

			return _c.bakc();
		}

		const size_t size() const
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