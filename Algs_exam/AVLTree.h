#pragma once

#include <stdexcept>
#include <string>

template<typename T>
struct AVLTreeNode
{
	T data;
	AVLTreeNode* left = nullptr;
	AVLTreeNode* right = nullptr;
	int height = 1;

	AVLTreeNode(T val, AVLTreeNode<T>* l = nullptr, AVLTreeNode<T>* r = nullptr);

	~AVLTreeNode() = default;
};

template<typename T>
class AVLTree
{
	AVLTreeNode<T>* m_root = nullptr;

	int height(AVLTreeNode<T>* root);

	int balance_factor(AVLTreeNode<T>* root);

	void fix_height(AVLTreeNode<T>* root);

	AVLTreeNode<T>* left_rotate(AVLTreeNode<T>* a);

	AVLTreeNode<T>* right_rotate(AVLTreeNode<T>* b);

	AVLTreeNode<T>* balance(AVLTreeNode<T>* node);

	AVLTreeNode<T>* get_min(AVLTreeNode<T>* root);

	AVLTreeNode<T>* get_max(AVLTreeNode<T>* root);

	AVLTreeNode<T>* insert(AVLTreeNode<T>* node, T val);

	AVLTreeNode<T>* remove_min(AVLTreeNode<T>* root);

	AVLTreeNode<T>* remove_max(AVLTreeNode<T>* root);

	AVLTreeNode<T>* remove(AVLTreeNode<T>* node, T val);

	bool contains(AVLTreeNode<T>* node, T val);

	void in_order(AVLTreeNode<T>* root, std::string& output);

public:

	AVLTree() = default;

	void insert(T val);

	void remove(T val);

	bool contains(T val);

	std::string in_order();

	~AVLTree();
};

template<typename T>
inline AVLTreeNode<T>::AVLTreeNode(T val, AVLTreeNode<T>* l, AVLTreeNode<T>* r):
	data(val), left(l), right(r)
{
	height = 1;
}

template<typename T>
inline int AVLTree<T>::height(AVLTreeNode<T>* root)
{
	return (root == nullptr) ? 0 : root->height;
}

template<typename T>
inline int AVLTree<T>::balance_factor(AVLTreeNode<T>* root)
{
	return (root == nullptr) ? 0 : height(root->left) - height(root->right);
}

template<typename T>
inline void AVLTree<T>::fix_height(AVLTreeNode<T>* root)
{
	if (root == nullptr)
		return;
	int left_height = height(root->left);
	int right_height = height(root->right);
	root->height = std::max(left_height, right_height) + 1;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::left_rotate(AVLTreeNode<T>* a)
{
	if (a == nullptr)
		return a;
	AVLTreeNode<T>* b = a->right;
	a->right = b->left;
	b->left = a;
	fix_height(a);
	fix_height(b);
	return b;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::right_rotate(AVLTreeNode<T>* b)
{
	if (b == nullptr)
		return b;
	AVLTreeNode<T>* a = b->left;
	b->left = a->right;
	a->right = b;
	fix_height(b);
	fix_height(a);
	return a;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::balance(AVLTreeNode<T>* node)
{
	fix_height(node);
	if (balance_factor(node) <= -2)
	{
		if (balance_factor(node->right) > 0)
			node->right = right_rotate(node->right);
		return left_rotate(node);
	}
	if (balance_factor(node) >= 2)
	{
		if (balance_factor(node->left) < 0)
			node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	return node;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::get_min(AVLTreeNode<T>* root)
{
	return (root->left == nullptr) ? root : get_min(root->left);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::get_max(AVLTreeNode<T>* root)
{
	return (root->right == nullptr) ? root : get_max(root->right);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>* node, T val)
{
	if (node == nullptr)
		return new AVLTreeNode<T>(val);
	if (val < node->data)
		node->left = insert(node->left, val);
	else
		node->right = insert(node->right, val);
	return balance(node);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::remove_min(AVLTreeNode<T>* root)
{
	if (root == nullptr)
		return root;
	if (root->left == nullptr)
		return root->right;
	root->left = remove_min(root->left);
	return balance(root);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::remove_max(AVLTreeNode<T>* root)
{
	if (root == nullptr)
		return root;
	if (root->right == nullptr)
		return root->left;
	root->right = remove_max(root->right);
	return balance(root);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>* node, T val)
{
	if (node == nullptr) 
		return node;
	if (val < node->data) 
		node->left = remove(node->left, val);
	else if (val > node->data)
		node->right = remove(node->right, val);
	else 
	{
		AVLTreeNode<T>* l = node->left;
		AVLTreeNode<T>* r = node->right;
		delete node;
		if (r == nullptr) 
			return l;
		AVLTreeNode<T>* next = get_min(r);
		next->right = remove_min(r);
		next->left = l;
		return balance(next);
	}
	return balance(node);
}

template<typename T>
inline bool AVLTree<T>::contains(AVLTreeNode<T>* node, T val)
{
	if (node == nullptr)
		return false;
	if (val < node->data)
		return contains(node->left, val);
	if (val > node->data)
		return contains(node->right, val);
	return true;
}

template<typename T>
inline void AVLTree<T>::in_order(AVLTreeNode<T>* root, std::string& output)
{
	if (root == nullptr)
		return;
	in_order(root->left, output);
	output += std::to_string(root->data) + " ";
	in_order(root->right, output);
}

template<typename T>
inline void AVLTree<T>::insert(T val)
{
	m_root = insert(m_root, val);
}

template<typename T>
inline void AVLTree<T>::remove(T val)
{
	m_root = remove(m_root, val);
}

template<typename T>
inline bool AVLTree<T>::contains(T val)
{
	return contains(m_root, val);
}

template<typename T>
inline std::string AVLTree<T>::in_order()
{
	static std::string output;
	output.clear();
	in_order(m_root, output);
	return output;
}

template<typename T>
inline AVLTree<T>::~AVLTree()
{
}
