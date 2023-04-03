#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

template<class K>
class HashFunc
{
public:
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 模板特化处理string不能取模运算的问题
template<>
class HashFunc<string>
{
public:
	size_t operator()(const string& key)
	{
		//return key[0];

		// 将字符串的ascii码相加作为返回值，能够一定程度避免发生哈希冲突
		size_t ret = 0;
		for (auto e : key)
		{
			ret *= 131;  // BKDRHash算法，为解决“abc”，“cba”，“aad”这种情况的哈希冲突
			ret += e;
		}

		return ret;
	}
};

template<class T>
struct HashNode
{
	T _data;
	HashNode<T>* _next;

	HashNode(const T& data)
		:_data(data)
		, _next(nullptr)
	{}
};

// 此处迭代器类和哈希表类存在相互引用问题，需要用前置声明来解决这一问题
// 前置声明
template<class K, class T, class Hash, class KeyOfT>
class HashTable;

template<class K, class T, class Hash, class KeyOfT>
struct __HTIterator
{
	typedef HashNode<T> Node;
	typedef __HTIterator<K, T, Hash, KeyOfT> Self;
	typedef HashTable<K, T, Hash, KeyOfT> HT;

	Node* _node;
	HT* _ht;  // 指针指向哈希表

	__HTIterator(Node* node, HT* ht)
		:_node(node)
		, _ht(ht)
	{}

	T& operator*()
	{
		return _node->_data;
	}

	T* operator->()
	{
		return &_node->_data;
	}

	bool operator!=(const Self& it) const
	{
		return _node != it._node;
	}

	bool operator==(const Self& it) const
	{
		return _node == it._node;
	}

	Self& operator++()
	{
		// _node->_next存在，表示当前迭代器指向的元素不是桶中的最后一个元素
		if (_node->_next)
		{
			_node = _node->_next;
		}
		// 迭代器指向的是桶中的最后一个元素，当前桶的元素已经遍历完了，要找下一个桶的第一个元素
		else
		{
			Hash hf;
			KeyOfT kot;

			// 计算出当前元素的桶的位置
			size_t hashi = hf(kot(_node->_data)) % _ht->_tables.size();
			++hashi;  // 跳过当前元素所处的桶

			// 往后找不为空的桶
			while (hashi < _ht->_tables.size())
			{
				// 找到不为空的桶
				if (_ht->_tables[hashi])
				{
					_node = _ht->_tables[hashi];
					break;  // 找到了就不用继续往后找了
				}
				else
				{
					++hashi;
				}
			}

			// 跳出循环有两种可能，第一种是找到不为空的桶了
			// 第二种是走到最后一个桶的后面了，没有桶了
			if (hashi == _ht->_tables.size())
			{
				_node = nullptr;  // 让空指针来充当end()
			}
		}

		return *this;
	}
};

template<class K, class T, class Hash, class KeyOfT>
class HashTable
{
	typedef HashNode<T> Node;

	template<class K, class T, class Hash, class KeyOfT>
	friend struct __HTIterator;

	inline unsigned long __stl_next_prime(unsigned long n)
	{
		static const int __stl_num_primes = 28;
		static const unsigned long __stl_prime_list[__stl_num_primes] =
		{
			53,         97,         193,       389,       769,
			1543,       3079,       6151,      12289,     24593,
			49157,      98317,      196613,    393241,    786433,
			1572869,    3145739,    6291469,   12582917,  25165843,
			50331653,   100663319,  201326611, 402653189, 805306457,
			1610612741, 3221225473, 4294967291
		};

		for (int i = 0; i < __stl_num_primes; ++i)
		{
			if (__stl_prime_list[i] > n)
			{
				return __stl_prime_list[i];
			}
		}

		return __stl_prime_list[__stl_num_primes - 1];
	}

public:
	typedef __HTIterator<K, T, Hash, KeyOfT> iterator;

	iterator begin()
	{
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			// 遍历到当前桶不为空
			if (_tables[i])
			{
				// 用该桶的第一个结点的指针构造一个迭代器返回
				return iterator(_tables[i], this);  // this指针存的就是当前对象的地址，直接用this指针传参构造迭代器
			}
		}

		return iterator(nullptr, this);  // 哈希表中一个有数据的桶都没有就返回一个用空指针构造的迭代器
	}

	iterator end()
	{
		return iterator(nullptr, this);  // 用空指针去替代最后一个数据的下一个
	}

	HashTable()
		:_n(0)
	{
		//_tables.resize(10);
		_tables.resize(__stl_next_prime(0));
	}

	~HashTable()
	{
		for (int i = 0; i < _tables.size(); ++i)
		{
			// 桶不为空，则遍历删除桶中的结点
			Node* cur = _tables[i];

			while (cur)
			{
				Node* next = cur->_next;
				delete cur;
				cur = next;
			}

			_tables[i] = nullptr;
		}
	}

	pair<iterator,bool> Insert(const T& data)
	{
		Hash hf;
		KeyOfT kot;

		iterator it = Find(kot(data));
		// 插入的元素已存在
		if (it != end())
		{
			return make_pair(it, false);
		}

		// 表达负载因子设置为1，超过就扩容
		if (_tables.size() == _n)
		{
			vector<Node*> newTables;
			//newTables.resize(_tables.size() * 2, nullptr);
			newTables.resize(__stl_next_prime(_tables.size()), nullptr);

			for (int i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];

				while (cur)
				{
					Node* next = cur->_next;

					// 找到数据在新表中的映射的桶的位置
					size_t hashi = hf(kot(cur->_data)) % newTables.size();

					//将数据头插到新表中
					cur->_next = newTables[hashi];
					newTables[hashi] = cur;

					cur = next;
				}

				_tables[i] = nullptr;
			}

			// 将新表换给旧表
			_tables.swap(newTables);
		}

		size_t hashi = hf(kot(data)) % _tables.size();

		// 根据key的值映射到对应桶的位置，然后头插
		Node* newNode = new Node(data);
		newNode->_next = _tables[hashi];
		_tables[hashi] = newNode;
		++_n;  // 表中有效个数++

		return make_pair(iterator(newNode, this), true);
	}

	iterator Find(const K& key)
	{
		Hash hf;
		KeyOfT kot;

		// 通过key先找到对应的桶
		size_t hashi = hf(key) % _tables.size();

		// 遍历对应的桶找key
		Node* cur = _tables[hashi];
		while (cur)
		{
			if (kot(cur->_data) == key)
			{
				return iterator(cur, this);
			}

			cur = cur->_next;
		}

		return end();
	}

	bool Erase(const K& key)
	{
		Hash hf;

		// 通过key先找到对应的桶
		size_t hashi = hf(key) % _tables.size();

		Node* cur = _tables[hashi];
		Node* prev = nullptr;

		// 遍历桶
		while (cur)
		{
			// 找到key并删除
			if (cur->_kv.first == key)
			{
				// 如果要删除的结点为桶的头结点，则直接删除即可
				if (cur == _tables[hashi])
				{
					_tables[hashi] = cur->_next;
				}
				else
				{
					prev->_next = cur->_next;
				}

				delete cur;
				--_n;

				return true;
			}

			prev = cur;
			cur = cur->_next;
		}

		return false;
	}

private:
	vector<Node*> _tables;
	size_t _n;  // 记录哈希表中存储的有效数据个数
};