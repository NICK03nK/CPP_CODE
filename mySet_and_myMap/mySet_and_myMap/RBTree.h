#pragma once

#include <iostream>
using namespace std;

enum Color
{
	RED,
	BLACK
};

template <class T>
struct RBTreeNode
{
	T _data;
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;
	Color _col;

	RBTreeNode(const T& data)
		:_data(data)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)
	{}
};

template <class T, class Ref, class Ptr>
struct __RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef __RBTreeIterator<T, Ref, Ptr> Self;
	typedef __RBTreeIterator<T, T&, T*> iterator;

	Node* _node;

	__RBTreeIterator(Node* node)
		:_node(node)
	{}

	// 若为普通迭代器，则以下函数是拷贝构造
	// 若为const迭代器，则以下函数为构造函数(用一个普通迭代器构造一个const迭代器)
	__RBTreeIterator(const iterator& it)
		:_node(it._node)
	{}

	Ref operator*()
	{
		return _node->_data;
	}

	Ptr operator->()
	{
		return &_node->_data;
	}

	Self& operator++()
	{
		// 右子树不为空，则迭代器指向右子树的最小值(服从二叉树中序遍历)
		if (_node->_right)
		{
			Node* min = _node->_right;  // 找右子树中的最小值
			while (min->_left)
			{
				min = min->_left;
			}

			_node = min;
		}
		// 右子树为空，则迭代器指向 cur为parent的左子树的 parent
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			
			while (parent && cur == parent->_right)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}

			_node = parent;
		}

		return *this;
	}

	Self& operator--()
	{
		// 左子树不为空，则迭代器指向左子树的最大值(服从二叉树中序逆序遍历 -- 右根左)
		if (_node->_left)
		{
			Node* max = _node->_left;
			while (max->_right)
			{
				max = max->_right;
			}

			_node = max;
		}
		// 右子树为空，则迭代器指向 cur为parent的左子树的 parent
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;
			
			while (parent && cur == parent->_left)
			{
				cur = cur->_parent;
				parent = parent->_parent;
			}

			_node = parent;
		}
	}

	bool operator==(const Self& it) const
	{
		return _node == it._node;
	}

	bool operator!=(const Self& it) const
	{
		return _node != it._node;
	}
};

template <class K, class T, class KeyOfT>
class RBTree
{
	typedef RBTreeNode<T> Node;

public:
	typedef __RBTreeIterator<T, T&, T*> iterator;
	typedef __RBTreeIterator<T, const T&, const T*> const_iterator;

	// begin返回的是开头，搜索树的开头是最左最小值
	iterator begin()
	{
		Node* left = _root;
		while (left && left->_left)
		{
			left = left->_left;
		}

		return iterator(left);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	const_iterator begin() const
	{
		Node* left = _root;
		while (left && left->_left)
		{
			left = left->_left;
		}

		return const_iterator(left);
	}

	const_iterator end() const
	{
		return const_iterator(nullptr);
	}

	pair<iterator, bool> Insert(const T& data)
	{
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_col = BLACK;

			return make_pair(iterator(_root), true);
		}

		Node* parent = nullptr;
		Node* cur = _root;

		KeyOfT kot;  // 仿函数对象，适用于在红黑树中的比较
		while (cur)
		{
			if (kot(data) > kot(cur->_data))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kot(data) < kot(cur->_data))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return make_pair(iterator(cur), false);
			}
		}

		cur = new Node(data);
		Node* newNode = cur;  // 用于指向插入的结点
		cur->_col = RED;
		if (kot(data) > kot(parent->_data))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		// 检查并调整结点颜色
		while (parent && parent->_col == RED)
		{
			Node* grandParent = parent->_parent;

			if (parent == grandParent->_left)  // parent在grandParent左边的情况
			{
				Node* uncle = grandParent->_right;
				
				// 情况一：uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandParent->_col = RED;

					cur = grandParent;
					parent = cur->_parent;
				}
				// 情况二和情况三
				else
				{
					// 情况二：uncle不存在 或 uncle存在且为黑 (grandParent，parent，cur在直线上)
					if (cur == parent->_left)
					{
						RotateR(grandParent);

						grandParent->_col = RED;
						parent->_col = BLACK;
					}
					// 情况三：uncle不存在 或 uncle存在且为黑 (grandParent，parent，cur在折线上)
					else
					{
						RotateL(parent);
						RotateR(grandParent);

						grandParent->_col = RED;
						cur->_col = BLACK;
					}

					// 因为情况二和情况三处理完后，顶上最终的grandParent都会改为黑色，
					// 即不会与其上面的parent形成连续两个红色的情况，所以处理完后break即可。
					break;
				}
			}
			else  // parent在grandParent右边的情况
			{
				Node* uncle = grandParent->_left;

				// 情况一：uncle存在且为红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandParent->_col = RED;

					cur = grandParent;
					parent = cur->_parent;
				}
				// 情况二和情况三
				else
				{
					// 情况二：uncle不存在 或 uncle存在且为黑 (grandParent，parent，cur在直线上)
					if (cur == parent->_right)
					{
						RotateL(grandParent);

						grandParent->_col = RED;
						parent->_col = BLACK;
					}
					// 情况三：uncle不存在 或 uncle存在且为黑 (grandParent，parent，cur在折线上)
					else
					{
						RotateR(parent);
						RotateL(grandParent);

						grandParent->_col = RED;
						cur->_col = BLACK;
					}

					break;
				}
			}
		}

		_root->_col = BLACK;

		return make_pair(iterator(newNode), true);
	}

	/*bool Find()
	{

	}*/

	void InOrder()
	{
		_InOrder(_root);
	}

	bool IsRBTree()
	{
		if (_root == nullptr)
		{
			return true;
		}

		if (_root->_col != BLACK)
		{
			return false;
		}

		// 将最左路径上的黑结点数量记录下来，作为参考值
		Node* left = _root;
		int ref = 0;
		while (left)
		{
			if (left->_col == BLACK)
			{
				++ref;
			}

			left = left->_left;
		}

		return Check(_root, 0, ref);
	}

private:
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
		{
			subRL->_parent = parent;
		}

		Node* ppNode = parent->_parent;
		subR->_left = parent;
		parent->_parent = subR;

		if (ppNode == nullptr)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (parent == ppNode->_left)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		Node* ppNode = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (ppNode == nullptr)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (parent == ppNode->_left)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}

	bool Check(Node* root, int blackNum, const int ref)
	{
		if (root == nullptr)
		{
			// 违反红黑树性质4
			if (blackNum != ref)
			{
				return false;
			}

			return true;
		}

		// 违反红黑树性质3
		if (root->_col == RED && root->_parent->_col == RED)
		{
			return false;
		}

		if (root->_col == BLACK)
		{
			++blackNum;
		}

		return Check(root->_left, blackNum, ref) && Check(root->_right, blackNum, ref);
	}

private:
	Node* _root = nullptr;
};