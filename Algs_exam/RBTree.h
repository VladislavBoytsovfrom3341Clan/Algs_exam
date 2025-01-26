#pragma once

#include <string>

enum class Color
{
	black,
	red
};

template<typename T>
struct RBNode
{
	T data;

	RBNode<T>* right = nullptr;
	RBNode<T>* left = nullptr;
	RBNode<T>* p = nullptr;

	Color color = Color::red;


	RBNode() = default;

	RBNode(T val) : data(val) {}
};

template<typename T>
class RBTree
{
	RBNode<T>* m_root = nullptr;
	RBNode<T>* nil = nullptr;


	void in_order(RBNode<T>* x, std::string& output);

	void leftRotate(RBNode<T>* x);

	void rightRotate(RBNode<T>* y);

	void eraseSubTree(RBNode<T>* root);

	void insertFixup(RBNode<T>* z);

	void transplant(RBNode<T>* u, RBNode<T>* v);

	RBNode<T>* treeMinimum(RBNode<T>* root);

	void eraseFixup(RBNode<T>* x);

	RBNode<T>* find(RBNode<T>* root, T k);

public:

	RBTree();

	void insert(T val);

	void erase(T val);

	bool contains(T val);

	std::string in_order();

	void clear();

	~RBTree();
};

template<typename T>
inline RBTree<T>::RBTree()
{
	nil = new RBNode<T>();
	nil->color = Color::black;
	nil->p = nil;
	nil->left = nil;
	nil->right = nil;
	m_root = nil;
}

template<typename T>
inline void RBTree<T>::insert(T val)
{
	RBNode<T>* z = new RBNode<T>(val);

	RBNode<T>* y = this->nil;
	RBNode<T>* x = m_root;

	while (x != this->nil)
	{
		y = x;
		if (z->data < x->data)
			x = x->left;
		else
			x = x->right;
	}

	z->p = y;
	if (y == this->nil)
		m_root = z;
	else if (z->data < y->data)
		y->left = z;
	else
		y->right = z;

	z->left = this->nil;
	z->right = this->nil;
	z->color = Color::red;
	insertFixup(z);
}

template<typename T>
inline void RBTree<T>::erase(T val)
{
	RBNode<T>* z = find(m_root, val);
	if (z == nullptr || z == nil)
		return;
	RBNode<T>* y = z;
	RBNode<T>* x = this->nil;
	Color yOriginalColor = y->color;
	if (z->left == this->nil)
	{
		x = z->right;
		transplant(z, z->right);
	}
	else if (z->right == this->nil)
	{
		x = z->left;
		transplant(z, z->left);
	}
	else
	{
		y = treeMinimum(z->right);
		yOriginalColor = y->color;
		x = y->right;
		if (y->p == z)
			x->p = y;
		else
		{
			transplant(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->p = y;
		y->color = z->color;
	}
	if (yOriginalColor == Color::black)
		eraseFixup(x);
}

template<typename T>
inline bool RBTree<T>::contains(T val)
{
	return find(m_root, val) != nullptr;
}

template<typename T>
inline void RBTree<T>::in_order(RBNode<T>* x, std::string& output)
{
	if (x == nullptr || x == this->nil)
		return;
	in_order(x->left, output);
	output += std::to_string(x->data)+" ";
	in_order(x->right, output);
}

template<typename T>
inline void RBTree<T>::leftRotate(RBNode<T>* x)
{
	RBNode<T>* y = x->right;
	x->right = y->left;

	if (y->left != this->nil)
		y->left->p = x;
	y->p = x->p;
	if (x->p == this->nil)
		this->m_root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;
}

template<typename T>
inline void RBTree<T>::rightRotate(RBNode<T>* y)
{
	RBNode<T>* x = y->left;
	y->left = x->right;

	if (x->right != this->nil)
		x->right->p = y;
	x->p = y->p;
	if (y->p == this->nil)
		this->m_root = x;
	else if (y == y->p->left)
		y->p->left = x;
	else
		y->p->right = x;
	x->right = y;
	y->p = x;
}

template<typename T>
inline void RBTree<T>::eraseSubTree(RBNode<T>* root)
{
	if (root == nullptr || root == this->nil)
		return;
	eraseSubTree(root->left);
	eraseSubTree(root->right);

	if (root->p != nullptr && root->p != this->nil)
	{
		if (root == root->p->left)
			root->p->left = this->nil;
		else
			root->p->right = this->nil;
	}

	delete root;
}

template<typename T>
inline void RBTree<T>::insertFixup(RBNode<T>* z)
{
	while (z->p->color == Color::red)
	{
		if (z->p == z->p->p->left)
		{
			RBNode<T>* y = z->p->p->right;
			if (y->color == Color::red)			//case 1
			{
				z->p->color = Color::black;
				y->color = Color::black;
				z->p->p->color = Color::red;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->right)			//case 2
				{
					z = z->p;
					leftRotate(z);
				}
				z->p->color = Color::black;		//case 3
				z->p->p->color = Color::red;
				rightRotate(z->p->p);
			}
		}
		else
		{
			RBNode<T>* y = z->p->p->left;
			if (y->color == Color::red)			//case 1
			{
				z->p->color = Color::black;
				y->color = Color::black;
				z->p->p->color = Color::red;
				z = z->p->p;
			}
			else
			{
				if (z == z->p->left)			//case 2
				{
					z = z->p;
					rightRotate(z);
				}
				z->p->color = Color::black;		//case 3
				z->p->p->color = Color::red;
				leftRotate(z->p->p);
			}
		}
	}
	m_root->color = Color::black;
}

template<typename T>
inline void RBTree<T>::transplant(RBNode<T>* u, RBNode<T>* v)
{
	if (u->p == this->nil)
		m_root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else u->p->right = v;
	v->p = u->p;
}

template<typename T>
inline RBNode<T>* RBTree<T>::treeMinimum(RBNode<T>* root)
{
	while (root->left != this->nil)
		root = root->left;
	return root;
}

template<typename T>
inline void RBTree<T>::eraseFixup(RBNode<T>* x)
{
	while (x != m_root && x->color == Color::black)
	{
		if (x == x->p->left)
		{
			RBNode<T>* w = x->p->right;
			if (w->color == Color::red)		//case 1
			{
				w->color = Color::black;
				x->p->color = Color::red;
				leftRotate(x->p);
				w = x->p->right;
			}
			if (w->left->color == Color::black && w->right->color == Color::black)
			{
				w->color = Color::red;		//case 2
				x = x->p;
			}
			else
			{
				if (w->right->color == Color::black)	//case 3
				{
					w->left->color = Color::black;
					w->color = Color::red;
					rightRotate(w);
					w = x->p->right;
				}
				w->color = x->p->color;
				x->p->color = Color::black;
				w->right->color = Color::black;
				leftRotate(x->p);
				x = m_root;
			}
		}
		else
		{
			RBNode<T>* w = x->p->left;
			if (w->color == Color::red)		//case 1
			{
				w->color = Color::black;
				x->p->color = Color::red;
				rightRotate(x->p);
				w = x->p->left;
			}
			if (w->right->color == Color::black && w->left->color == Color::black)
			{
				w->color = Color::red;		//case 2
				x = x->p;
			}
			else
			{
				if (w->left->color == Color::black)	//case 3
				{
					w->right->color = Color::black;
					w->color = Color::red;
					leftRotate(w);
					w = x->p->left;
				}
				w->color = x->p->color;
				x->p->color = Color::black;
				w->left->color = Color::black;
				rightRotate(x->p);
				x = m_root;
			}
		}
	}
	x->color = Color::black;
}

template<typename T>
inline RBNode<T>* RBTree<T>::find(RBNode<T>* root, T k)
{
	if (root == nullptr|| root == nil || k == root->data)
		return root;
	if (k < root->data)
		return find(root->left, k);
	return find(root->right, k);
}

template<typename T>
inline std::string RBTree<T>::in_order()
{
	std::string output;
	in_order(m_root, output);
	return output;
}

template<typename T>
inline void RBTree<T>::clear()
{
	eraseSubTree(m_root);
}

template<typename T>
inline RBTree<T>::~RBTree()
{
	eraseSubTree(m_root);
}
