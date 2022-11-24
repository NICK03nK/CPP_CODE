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
				// 解决_finish始终为nullptr的问题
				size_t oldSize = size();

				T* tmp = new T[n];
				
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * oldSize);
					delete[] _start;
				}

				_start = tmp;
				_finish = _start + oldSize;
				_endOfStorage = _start + n;
			}
		}

		void resize(size_t n, const T& value = T())
		{
			if (n > capacity())  // 扩容 + 插入数据
			{
				reserve(n);
			}

			if (n > size())  // 插入数据
			{
				while (_finish < _start + n)
				{
					*_finish = value;
					++_finish;
				}
			}
			else  // 删除数据
			{
				_finish = _start + n;
			}
		}

		bool empty()
		{
			return _finish = _start;
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

		void pop_back()
		{
			assert(!empty());

			--_finish;
		}

		// 可能存在迭代器失效问题(也是一种野指针问题)
		void insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			if (_finish == _endOfStorage)
			{
				// 扩容会导致pos迭代器失效
				size_t len = pos - _start;

				size_t newCapcity = capacity() == 0 ? 4 : capacity() * 2;
				reserve(newCapcity);

				// 需要更新pos来解决迭代器失效的问题
				pos = _start + len;
			}

			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}

			*pos = x;
			++_finish;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endOfStorage;
	};
}