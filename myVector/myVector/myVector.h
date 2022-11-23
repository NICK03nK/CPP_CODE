#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

namespace myVector
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator cbegin() const
		{
			return _start;
		}

		const_iterator cend() const
		{
			return _finish;
		}

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _endOfStorage - _start;
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				T* tmp = new T[n];
				
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * size());
					delete[] _start;
				}

				_start = tmp;
				_finish = _start + size();
				_endOfStorage = _start + capacity();
			}
		}

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return _start[pos];
		}

		void push_back(const T& x)
		{
			if (_finish == _endOfStorage)
			{
				size_t newCapcity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapcity);
			}

			*_finish = x;
			++_finish;
		}



	private:
		iterator _start;
		iterator _finish;
		iterator _endOfStorage;
	};
}