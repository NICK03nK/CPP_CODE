#pragma once

#include "RBTree.h"

namespace mySet
{
	template<class K>
	class set
	{
		// KeyOfT用于RBTree中的比较，无论是set还是map都能使用对应的比较规则
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		// 由于set中的元素的Key不允许被修改，所以set的迭代器都采用const迭代器
		//typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;
		typedef typename RBTree<K, K, SetKeyOfT>::const_iterator iterator;
		typedef typename RBTree<K, K, SetKeyOfT>::const_iterator const_iterator;

		iterator begin() const
		{
			return _t.begin();
		}

		iterator end() const
		{
			return _t.end();
		}

		pair<iterator, bool> insert(const K& key)
		{
			pair<typename RBTree<K, K, SetKeyOfT>::iterator, bool> ret = _t.Insert(key);  // 这里显示调用RBTree中的普通迭代器类型
			return pair<iterator, bool>(ret.first, ret.second);  // 这里的iterator是mySet中的iterator，实际上是const迭代器，用普通迭代器构造const迭代器
		}
	
	private:
		RBTree<K, K, SetKeyOfT> _t;
	};
}