#pragma once

#include <stdexcept>
#include <string>

template<typename T>
struct BSTNode
{
	T data;
	BSTNode<T>* p = nullptr;
	BSTNode<T>* left = nullptr;
	BSTNode<T>* right = nullptr;

	BSTNode() = default;

	BSTNode(T val);
};

template<typename T>
class BinarySearchTree
{
	BSTNode<T>* m_root = nullptr;

	BSTNode<T>* find(BSTNode<T>* root, T val);

	void in_order(BSTNode<T>* root, std::string& output);

	void transplant(BSTNode<T>* u, BSTNode<T>* v);

	BSTNode<T>* get_min(BSTNode<T>* root);

public:

	BinarySearchTree() = default;

	std::string in_order();

	bool contains(T val);

	void insert(T val);

	void erase(T val);

	~BinarySearchTree() = default;
};

template<typename T>
inline BSTNode<T>::BSTNode(T val):
	data(val)
{
}

template<typename T>
inline BSTNode<T>* BinarySearchTree<T>::find(BSTNode<T>* root, T val)
{
	if (root == nullptr || val == root->data)
		return root;
	if (val < root->data)
		return find(root->left, val);
	return find(root->right, val);
}

template<typename T>
inline void BinarySearchTree<T>::in_order(BSTNode<T>* root, std::string& output)
{
	if (root == nullptr)
		return;
	in_order(root->left, output);
	output += std::to_string(root->data) + " ";
	in_order(root->right, output);
}

template<typename T>
inline void BinarySearchTree<T>::transplant(BSTNode<T>* u, BSTNode<T>* v)
{
	if (u->p == nullptr)
		m_root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if (v != nullptr)
		v->p = u->p;
}

template<typename T>
inline BSTNode<T>* BinarySearchTree<T>::get_min(BSTNode<T>* root)
{
	if (root == nullptr)
		return root;
	if (root->left == nullptr)
		return root;
	return get_min(root->left);
}

template<typename T>
inline std::string BinarySearchTree<T>::in_order()
{
	std::string output;
	in_order(m_root, output);
	return output;
}

template<typename T>
inline bool BinarySearchTree<T>::contains(T val)
{
	return find(m_root, val) != nullptr;
}

template<typename T>
inline void BinarySearchTree<T>::insert(T val)
{
	BSTNode<T>* z = new BSTNode<T>(val);
	BSTNode<T>* y = nullptr;
	BSTNode<T>* x = m_root;
	while (x != nullptr)
	{
		y = x;
		if (z->data < x->data)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == nullptr)
		m_root = z;
	else if (z->data < y->data)
		y->left = z;
	else 
		y->right = z;
}

template<typename T>
inline void BinarySearchTree<T>::erase(T val)
{
	BSTNode<T>* z = find(m_root, val);
	if (z == nullptr)
		throw std::runtime_error("No such an element\n");
	if (z->left == nullptr)
		transplant(z, z->right);
	else if (z->right == nullptr)
		transplant(z, z->left);
	else
	{
		BSTNode<T>* y = get_min(z->right);
		if (y->p != z)
		{
			transplant(y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(z, y);
		y->left = z->left;
		y->left->p = y;
	}
}
