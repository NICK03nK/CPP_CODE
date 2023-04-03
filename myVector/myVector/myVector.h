#pragma once

#include <iostream>
#include <assert.h>
//#include <initializer_list>
#include "myIiterator.h"
using namespace std;

namespace myVector
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		// 反向迭代器
		typedef myIterator::reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef myIterator::reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		vector()
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{}

		vector(size_t n, const T& value = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				push_back(value);
			}
		}

		// 这里要另外实现一个n的类型为int的构造函数
		// 如果不实现，构造函数将会去调用迭代器构造
		// 而不是n个value构造
		vector(int n, const T& value = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			reserve(n);
			for (int i = 0; i < n; ++i)
			{
				push_back(value);
			}
		}

		template<class inputIterator>
		vector(inputIterator first, inputIterator last)
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		vector(const vector<T>& vT)
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			vector<T> tmp(vT.begin(), vT.end());
			swap(tmp);
		}

		vector(const initializer_list<T>& il)
			:_start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			reserve(il.size());

			typename initializer_list<T>::iterator it = il.begin();
			while (it != il.end())
			{
				push_back(*it);
				++it;
			}
		}

		vector& operator=(vector<T> vT)
		{
			swap(vT);
			return *this;
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
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
					// 若vector<T>中的T为自定义类型(vector<int>，string等)
					// 用memecpy()来拷贝数据，当发生扩容时，就会出现浅拷贝问题
					// 浅拷贝后，把原先的空间释放掉，拷贝到tmp中的空间也会被释放
					//memcpy(tmp, _start, sizeof(T) * oldSize);

					// 复用赋值重载函数来解决上述问题
					for (int i = 0; i < oldSize; ++i)
					{
						tmp[i] = _start[i];
					}

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

		const T& operator[](size_t pos) const
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

		void swap(vector<T>& vT)
		{
			std::swap(_start, vT._start);
			std::swap(_finish, vT._finish);
			std::swap(_endOfStorage, vT._endOfStorage);
		}

		// 可能存在迭代器失效问题(也是一种野指针问题)
		iterator insert(iterator pos, const T& x)
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

			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			iterator begin = pos + 1;

			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;

			return pos;
		}

		void clear()
		{
			_finish = _start;
		}

	private:
		iterator _start;
		iterator _finish;
		iterator _endOfStorage;
	};
}
