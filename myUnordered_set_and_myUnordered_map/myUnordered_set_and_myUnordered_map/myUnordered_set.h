#pragma once

#include "HashTable.h"

namespace myUnordered_set
{
	template<class K, class Hash = HashFunc<K>>
	class unordered_set
	{
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		typedef typename HashTable<K, K, Hash, SetKeyOfT>::iterator iterator;  // 取类模板里的类型，前面要加上typename

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		pair<iterator, bool> insert(const K& key)
		{
			return _ht.Insert(key);
		}

	private:
		HashTable<K, K, Hash, SetKeyOfT> _ht;
	};
}