#pragma once

#include "RBTree.h"

namespace mySet
{
	template<class K>
	class set
	{
		// KeyOfT����RBTree�еıȽϣ�������set����map����ʹ�ö�Ӧ�ıȽϹ���
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};

	public:
		// ����set�е�Ԫ�ص�Key�������޸ģ�����set�ĵ�����������const������
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
			pair<typename RBTree<K, K, SetKeyOfT>::iterator, bool> ret = _t.Insert(key);  // ������ʾ����RBTree�е���ͨ����������
			return pair<iterator, bool>(ret.first, ret.second);  // �����iterator��mySet�е�iterator��ʵ������const������������ͨ����������const������
		}
	
	private:
		RBTree<K, K, SetKeyOfT> _t;
	};
}