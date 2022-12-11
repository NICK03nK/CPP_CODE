#pragma once

#include <iostream>
#include <assert.h>
using namespace std;

namespace myList
{
	template<class T>
	struct list_node
	{
		list_node* _next;
		list_node* _prev;
		T _data;

		list_node(const T& value)
			:_next(nullptr)
			, _prev(nullptr)
			, _data(value)
		{}
	};

	template<class T>
	struct __list_iterator
	{
		typedef list_node<T> node;
		node* _pnode;

		__list_iterator(node* p)
			:_pnode(p)
		{}

		T& operator*()
		{
			return _pnode->_data;
		}

		__list_iterator<T>& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		__list_iterator<T>& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		bool operator!=(const __list_iterator<T>& it)
		{
			return _pnode != it._pnode;
		}
	};

	template<class T>
	struct __list_const_iterator
	{
		typedef list_node<T> node;
		node* _pnode;

		__list_const_iterator(node* p)
			:_pnode(p)
		{}

		const T& operator*()
		{
			return _pnode->_data;
		}

		__list_const_iterator<T>& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		__list_const_iterator<T>& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		bool operator!=(const __list_const_iterator<T>& it)
		{
			return _pnode != it._pnode;
		}
	};

	template<class T>
	class list
	{
	public:
		typedef list_node<T> node;
		typedef __list_iterator<T> iterator;
		typedef __list_const_iterator<T> const_iterator;

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		void empty_initialize()
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;
		}

		list()
		{
			empty_initialize();
		}

		// 传统写法
		list(const list<T>& lT)
		{
			empty_initialize();

			for (const auto& e : lT)
			{
				push_back(e);
			}
		}

		// 传统写法
		list<T>& operator=(const list<T>& lT)
		{
			if (this != &lT)
			{
				clear();

				for (const auto& e : lT)
				{
					push_back(e);
				}
			}

			return *this;
		}

		~list()
		{
			clear();

			delete _head;
			_head = nullptr;
		}

		void push_back(const T& value)
		{
			// 传统写法
			/*node* newNode = new node(value);
			node* tail = _head->_prev;
			tail->_next = newNode;
			newNode->_prev = tail;
			newNode->_next = _head;
			_head->_prev = newNode;*/

			// 复用insert()写法
			insert(end(), value);
		}

		void push_front(const T& value)
		{
			insert(begin(), value);
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		iterator insert(iterator pos, const T& value)
		{
			node* newNode = new node(value);
			node* cur = pos._pnode;
			node* prev = cur->_prev;

			prev->_next = newNode;
			newNode->_prev = prev;
			newNode->_next = cur;
			cur->_prev = newNode;

			return iterator(newNode);
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());

			node* prev = pos._pnode->_prev;
			node* next = pos._pnode->_next;

			prev->_next = next;
			next->_prev = prev;

			delete pos._pnode;

			return iterator(next);
		}

		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}

	private:
		node* _head;
	};
}