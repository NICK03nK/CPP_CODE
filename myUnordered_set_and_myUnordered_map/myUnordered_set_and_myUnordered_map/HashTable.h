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

// ģ���ػ�����string����ȡģ���������
template<>
class HashFunc<string>
{
public:
	size_t operator()(const string& key)
	{
		//return key[0];

		// ���ַ�����ascii�������Ϊ����ֵ���ܹ�һ���̶ȱ��ⷢ����ϣ��ͻ
		size_t ret = 0;
		for (auto e : key)
		{
			ret *= 131;  // BKDRHash�㷨��Ϊ�����abc������cba������aad����������Ĺ�ϣ��ͻ
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

// �˴���������͹�ϣ��������໥�������⣬��Ҫ��ǰ�������������һ����
// ǰ������
template<class K, class T, class Hash, class KeyOfT>
class HashTable;

template<class K, class T, class Hash, class KeyOfT>
struct __HTIterator
{
	typedef HashNode<T> Node;
	typedef __HTIterator<K, T, Hash, KeyOfT> Self;
	typedef HashTable<K, T, Hash, KeyOfT> HT;

	Node* _node;
	HT* _ht;  // ָ��ָ���ϣ��

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
		// _node->_next���ڣ���ʾ��ǰ������ָ���Ԫ�ز���Ͱ�е����һ��Ԫ��
		if (_node->_next)
		{
			_node = _node->_next;
		}
		// ������ָ�����Ͱ�е����һ��Ԫ�أ���ǰͰ��Ԫ���Ѿ��������ˣ�Ҫ����һ��Ͱ�ĵ�һ��Ԫ��
		else
		{
			Hash hf;
			KeyOfT kot;

			// �������ǰԪ�ص�Ͱ��λ��
			size_t hashi = hf(kot(_node->_data)) % _ht->_tables.size();
			++hashi;  // ������ǰԪ��������Ͱ

			// �����Ҳ�Ϊ�յ�Ͱ
			while (hashi < _ht->_tables.size())
			{
				// �ҵ���Ϊ�յ�Ͱ
				if (_ht->_tables[hashi])
				{
					_node = _ht->_tables[hashi];
					break;  // �ҵ��˾Ͳ��ü�����������
				}
				else
				{
					++hashi;
				}
			}

			// ����ѭ�������ֿ��ܣ���һ�����ҵ���Ϊ�յ�Ͱ��
			// �ڶ������ߵ����һ��Ͱ�ĺ����ˣ�û��Ͱ��
			if (hashi == _ht->_tables.size())
			{
				_node = nullptr;  // �ÿ�ָ�����䵱end()
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
			// ��������ǰͰ��Ϊ��
			if (_tables[i])
			{
				// �ø�Ͱ�ĵ�һ������ָ�빹��һ������������
				return iterator(_tables[i], this);  // thisָ���ľ��ǵ�ǰ����ĵ�ַ��ֱ����thisָ�봫�ι��������
			}
		}

		return iterator(nullptr, this);  // ��ϣ����һ�������ݵ�Ͱ��û�оͷ���һ���ÿ�ָ�빹��ĵ�����
	}

	iterator end()
	{
		return iterator(nullptr, this);  // �ÿ�ָ��ȥ������һ�����ݵ���һ��
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
			// Ͱ��Ϊ�գ������ɾ��Ͱ�еĽ��
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
		// �����Ԫ���Ѵ���
		if (it != end())
		{
			return make_pair(it, false);
		}

		// ��︺����������Ϊ1������������
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

					// �ҵ��������±��е�ӳ���Ͱ��λ��
					size_t hashi = hf(kot(cur->_data)) % newTables.size();

					//������ͷ�嵽�±���
					cur->_next = newTables[hashi];
					newTables[hashi] = cur;

					cur = next;
				}

				_tables[i] = nullptr;
			}

			// ���±����ɱ�
			_tables.swap(newTables);
		}

		size_t hashi = hf(kot(data)) % _tables.size();

		// ����key��ֵӳ�䵽��ӦͰ��λ�ã�Ȼ��ͷ��
		Node* newNode = new Node(data);
		newNode->_next = _tables[hashi];
		_tables[hashi] = newNode;
		++_n;  // ������Ч����++

		return make_pair(iterator(newNode, this), true);
	}

	iterator Find(const K& key)
	{
		Hash hf;
		KeyOfT kot;

		// ͨ��key���ҵ���Ӧ��Ͱ
		size_t hashi = hf(key) % _tables.size();

		// ������Ӧ��Ͱ��key
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

		// ͨ��key���ҵ���Ӧ��Ͱ
		size_t hashi = hf(key) % _tables.size();

		Node* cur = _tables[hashi];
		Node* prev = nullptr;

		// ����Ͱ
		while (cur)
		{
			// �ҵ�key��ɾ��
			if (cur->_kv.first == key)
			{
				// ���Ҫɾ���Ľ��ΪͰ��ͷ��㣬��ֱ��ɾ������
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
	size_t _n;  // ��¼��ϣ���д洢����Ч���ݸ���
};