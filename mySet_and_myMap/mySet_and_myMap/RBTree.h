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

	// ��Ϊ��ͨ�������������º����ǿ�������
	// ��Ϊconst�������������º���Ϊ���캯��(��һ����ͨ����������һ��const������)
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
		// ��������Ϊ�գ��������ָ������������Сֵ(���Ӷ������������)
		if (_node->_right)
		{
			Node* min = _node->_right;  // ���������е���Сֵ
			while (min->_left)
			{
				min = min->_left;
			}

			_node = min;
		}
		// ������Ϊ�գ��������ָ�� curΪparent���������� parent
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
		// ��������Ϊ�գ��������ָ�������������ֵ(���Ӷ���������������� -- �Ҹ���)
		if (_node->_left)
		{
			Node* max = _node->_left;
			while (max->_right)
			{
				max = max->_right;
			}

			_node = max;
		}
		// ������Ϊ�գ��������ָ�� curΪparent���������� parent
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

	// begin���ص��ǿ�ͷ���������Ŀ�ͷ��������Сֵ
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

		KeyOfT kot;  // �º��������������ں�����еıȽ�
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
		Node* newNode = cur;  // ����ָ�����Ľ��
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

		// ��鲢���������ɫ
		while (parent && parent->_col == RED)
		{
			Node* grandParent = parent->_parent;

			if (parent == grandParent->_left)  // parent��grandParent��ߵ����
			{
				Node* uncle = grandParent->_right;
				
				// ���һ��uncle������Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandParent->_col = RED;

					cur = grandParent;
					parent = cur->_parent;
				}
				// ������������
				else
				{
					// �������uncle������ �� uncle������Ϊ�� (grandParent��parent��cur��ֱ����)
					if (cur == parent->_left)
					{
						RotateR(grandParent);

						grandParent->_col = RED;
						parent->_col = BLACK;
					}
					// �������uncle������ �� uncle������Ϊ�� (grandParent��parent��cur��������)
					else
					{
						RotateL(parent);
						RotateR(grandParent);

						grandParent->_col = RED;
						cur->_col = BLACK;
					}

					// ��Ϊ������������������󣬶������յ�grandParent�����Ϊ��ɫ��
					// ���������������parent�γ�����������ɫ����������Դ������break���ɡ�
					break;
				}
			}
			else  // parent��grandParent�ұߵ����
			{
				Node* uncle = grandParent->_left;

				// ���һ��uncle������Ϊ��
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandParent->_col = RED;

					cur = grandParent;
					parent = cur->_parent;
				}
				// ������������
				else
				{
					// �������uncle������ �� uncle������Ϊ�� (grandParent��parent��cur��ֱ����)
					if (cur == parent->_right)
					{
						RotateL(grandParent);

						grandParent->_col = RED;
						parent->_col = BLACK;
					}
					// �������uncle������ �� uncle������Ϊ�� (grandParent��parent��cur��������)
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

		// ������·���ϵĺڽ��������¼��������Ϊ�ο�ֵ
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
			// Υ�����������4
			if (blackNum != ref)
			{
				return false;
			}

			return true;
		}

		// Υ�����������3
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