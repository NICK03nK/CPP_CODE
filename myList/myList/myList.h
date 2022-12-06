#pragma once

#include <iostream>
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

		bool operator!=(const __list_iterator<T>& it)
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

		iterator begin()
		{
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}

		list()
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;
		}

		void push_back(const T& value)
		{
			node* newNode = new node(value);
			node* tail = _head->_prev;
			tail->_next = newNode;
			newNode->_prev = tail;
			newNode->_next = _head;
			_head->_prev = newNode;
		}

	private:
		node* _head;
	};
}