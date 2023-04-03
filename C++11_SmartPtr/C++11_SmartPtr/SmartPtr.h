#pragma once

#include <iostream>
#include <mutex>
using namespace std;

namespace SmartPtr
{
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr)
			:_ptr(ptr)
		{}

		~auto_ptr()
		{
			delete _ptr;
		}

		auto_ptr(auto_ptr<T>& ap)
			:_ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T& operator[](size_t pos)
		{
			return _ptr[pos];
		}

	private:
		T* _ptr;
	};

	template<class T>
	class unique_ptr
	{
	public:
		unique_ptr(T* ptr)
			:_ptr(ptr)
		{}

		~unique_ptr()
		{
			delete _ptr;
		}

		unique_ptr(const unique_ptr<T>& up) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& up) = delete;

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T& operator[](size_t pos)
		{
			return _ptr[pos];
		}

	private:
		T* _ptr;
	};

	// 默认定制删除器
	template<class T>
	struct default_delete
	{
		void operator()(T* ptr)
		{
			delete ptr;
		}
	};

	template<class T, class D = default_delete<T>>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr)
			:_ptr(ptr)
			, _pcount(new int(1))
			, _pmtx(new mutex)
		{}

		~shared_ptr()
		{
			Release();
		}

		void Release()
		{
			bool flag = false;

			_pmtx->lock();
			if (--(*_pcount) == 0)
			{
				//delete _ptr;
				_del(_ptr);  // 使用定制删除器来释放资源
				delete _pcount;
				flag = true;
			}
			_pmtx->unlock();

			if (flag)
			{
				delete _pmtx;
			}
		}

		shared_ptr(const shared_ptr<T>& sp)
			:_ptr(sp._ptr)
			, _pcount(sp._pcount)
			, _pmtx(sp._pmtx)
		{
			_pmtx->lock();
			++(*_pcount);
			_pmtx->unlock();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (sp._ptr != _ptr)
			{
				Release();

				_ptr = sp._ptr;
				_pcount = sp._pcount;
				_pmtx = sp._pmtx;

				_pmtx->lock();
				++(*_pcount);
				_pmtx->unlock();
			}

			return *this;
		}

		int use_count() const
		{
			return *_pcount;
		}

		T* get() const
		{
			return _ptr;
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		T& operator[](size_t pos)
		{
			return _ptr[pos];
		}

	private:
		T* _ptr;
		int* _pcount;  // 引用计数，用于记录有多少个sp指向当前这块空间
		mutex* _pmtx;

		D _del;  // 定制删除器
	};

	template<class T>
	class weak_ptr
	{
	public:
		weak_ptr()
			:_ptr(nullptr)
		{}

		weak_ptr(const shared_ptr<T>& sp)
			:_ptr(sp.get())
		{}

		weak_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			_ptr = sp.get();
			return *this;
		}

	private:
		T* _ptr;
	};
}