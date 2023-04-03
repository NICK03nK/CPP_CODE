#pragma once

#include <iostream>
#include <assert.h>
#include <initializer_list>
#include "myIiterator.h"
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

		list_node(T&& value)  // value����ֵ���ã��߱���ֵ����
			:_next(nullptr)
			, _prev(nullptr)
			, _data(move(value))  // ����Ҫ���� T �Ŀ������죬�������ǵ����ƶ����죬����Ҫ����move()����valueתΪ��ֵ����������ƥ���ȥ���� T ����ֵ���ð汾�Ŀ�������(���ƶ�����)
		{}
	};

	// ͬһ����ģ��ʵ��������������ͬ������
	// typedef __list_iterator<T, T&, T*> iterator;
	// typedef __list_iterator<T, const T&, const T*> const_iterator;
	// �������������ڲ�ͬ���࣬ͨ����__list_iteratorģ�崫��ͬ�Ĳ����Ӷ�ʵ��������ͬ����
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> node;
		typedef __list_iterator<T, Ref, Ptr> Self;  // ʹ��typedef��__list_iterator<T, Ref, Ptr>������ΪSelf�����ں���ͳһ�������������
		node* _pnode;

		__list_iterator(node* p = nullptr)
			:_pnode(p)
		{}

		__list_iterator(const Self& lt)
			:_pnode(lt._pnode)
		{}

		Ref operator*()
		{
			return _pnode->_data;
		}

		Ptr operator->()
		{
			return &_pnode->_data;
		}

		Self& operator++()
		{
			_pnode = _pnode->_next;
			return *this;
		}

		Self operator++(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_next;
			return tmp;
		}

		Self& operator--()
		{
			_pnode = _pnode->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self tmp(*this);
			_pnode = _pnode->_prev;
			return tmp;
		}

		bool operator!=(const Self& it) const
		{
			return _pnode != it._pnode;
		}

		bool operator==(const Self& it) const
		{
			return _pnode == it._pnode;
		}
	};

	/*template<class T>
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
	};*/

	template<class T>
	class list
	{
	public:
		typedef list_node<T> node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		//typedef __list_const_iterator<T> const_iterator;

		// ���������
		typedef myIterator::reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef myIterator::reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;

		void empty_initialize()
		{
			_head = new node(T());
			_head->_next = _head;
			_head->_prev = _head;

			_size = 0;
		}

		list()
		{
			empty_initialize();
		}

		list(int n, const T& value = T())
		{
			empty_initialize();

			while (n--)
			{
				push_back(value);
			}
		}

		template <class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_initialize();

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		// ��ͳд��
		/*list(const list<T>& lT)
		{
			empty_initialize();

			for (const auto& e : lT)
			{
				push_back(e);
			}
		}*/

		// �ִ�д��
		list(const list<T>& lT)
		{
			empty_initialize();

			list<T> tmp(lT.begin(), lT.end());
			swap(tmp);
		}

		// �ƶ�����
		list(list<T>&& lT)
		{
			swap(lT);
		}

		list(const initializer_list<T>& il)
		{
			empty_initialize();

			typename initializer_list<T>::iterator it = il.begin();
			while (it != il.end())
			{
				push_back(*it);
				++it;
			}
		}

		// ��ͳд��
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

		// �ִ�д��
		/*list<T>& operator=(list<T> lT)
		{
			swap(lT);

			return *this;
		}*/

		// �ƶ���ֵ
		list<T>& operator=(list<T>&& lT)  // �ƶ���ֵ���ִ�д���ĸ�ֵ���س�ͻ��ע�͵��ִ�д���ĸ�ֵ���ز���ͨ������
		{
			swap(lT);

			return *this;
		}

		~list()
		{
			clear();

			delete _head;
			_head = nullptr;
		}

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

		size_t size() const
		{
			return _size;
		}

		bool empty() const
		{
			return _size == 0;
		}

		T& front()
		{
			assert(!empty());

			return _head->_next->_data;
		}

		const T& front() const
		{
			assert(!empty());

			return _head->_next->_data;
		}

		T& back()
		{
			assert(!empty());

			return _head->_prev->_data;
		}

		const T& back() const
		{
			assert(!empty());

			return _head->_prev->_data;
		}

		void push_back(const T& value)
		{
			// ��ͳд��
			/*node* newNode = new node(value);
			node* tail = _head->_prev;
			tail->_next = newNode;
			newNode->_prev = tail;
			newNode->_next = _head;
			_head->_prev = newNode;*/

			// ����insert()д��
			insert(end(), value);
		}

		void push_back(T&& value)  // ��ֵ���þ߱���ֵ����
		{
			insert(end(), move(value));  // Ҫ������ֵ���ð汾��insert()����Ҫmove(value)������ֵmove()Ϊ��ֵ
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& value)
		{
			insert(begin(), value);
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

			++_size;

			return iterator(newNode);
		}

		iterator insert(iterator pos, T&& value)  // value����ֵ���ã��߱���ֵ����
		{
			node* newNode = new node(move(value));  // Ҫ������ֵ���ð汾��node�Ĺ��캯������Ҫmove(value)
			node* cur = pos._pnode;
			node* prev = cur->_prev;

			prev->_next = newNode;
			newNode->_prev = prev;
			newNode->_next = cur;
			cur->_prev = newNode;

			++_size;

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

			--_size;

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

		void swap(list<T>& lT)
		{
			std::swap(_head, lT._head);
			std::swap(_size, lT._size);
		}

	private:
		node* _head;
		size_t _size;
	};
}