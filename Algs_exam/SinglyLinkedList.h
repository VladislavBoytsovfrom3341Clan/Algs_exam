#pragma once

#include <stdexcept>

template<typename T>
struct SinglyLinkedListNode
{
	T data;
	SinglyLinkedListNode* next = nullptr;

	SinglyLinkedListNode();

	SinglyLinkedListNode(T val, SinglyLinkedListNode* ptr = nullptr);
};

template<typename T>
class SinglyLinkedListIterator
{
	SinglyLinkedListNode<T>* node;

public:

	SinglyLinkedListIterator(SinglyLinkedListNode<T>* node);

	SinglyLinkedListIterator(const SinglyLinkedListIterator<T>& copy);

	SinglyLinkedListIterator(SinglyLinkedListIterator<T>&& moved);

	SinglyLinkedListIterator<T>& operator=(const SinglyLinkedListIterator<T>& copy);

	SinglyLinkedListIterator<T>& operator=(SinglyLinkedListIterator<T>&& moved);

	SinglyLinkedListIterator<T>& operator++();

	SinglyLinkedListIterator<T> operator++(int);

	T& operator*();

	bool operator==(const SinglyLinkedListIterator<T>& other) const;

	bool operator!=(const SinglyLinkedListIterator<T>& other) const;
};

template<typename T>
class SinglyLinkedList
{
	SinglyLinkedListNode<T>* m_head = nullptr;
	SinglyLinkedListNode<T>* m_tail = nullptr;
	size_t m_size = 0;

public:

	SinglyLinkedList();

	SinglyLinkedList(T val);

	bool empty() const;

	size_t size() const;

	void push_front(T val);

	void push_back(T val);

	void pop_front();

	void pop_back();

	T& front();

	const T& front() const;

	T& back();

	const T& back() const;

	SinglyLinkedListIterator<T> begin();

	SinglyLinkedListIterator<T> end();

	T& operator[] (int n);

	const T& operator[] (int n) const;

	~SinglyLinkedList();
};

template<typename T>
inline SinglyLinkedListNode<T>::SinglyLinkedListNode()
{
	next = nullptr;
}

template<typename T>
inline SinglyLinkedListNode<T>::SinglyLinkedListNode(T val, SinglyLinkedListNode* ptr):
	data(val), next(ptr)
{
}

template<typename T>
inline SinglyLinkedList<T>::SinglyLinkedList()
{
	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
}

template<typename T>
inline SinglyLinkedList<T>::SinglyLinkedList(T val)
{
	m_head = new SinglyLinkedListNode<T>(val);
	m_tail = m_head;
	m_size = 1;
}

template<typename T>
inline bool SinglyLinkedList<T>::empty() const
{
	return(m_head == nullptr);
}

template<typename T>
inline size_t SinglyLinkedList<T>::size() const
{
	return m_size;
}

template<typename T>
inline void SinglyLinkedList<T>::push_front(T val)
{
	SinglyLinkedListNode<T>* new_head = new SinglyLinkedListNode<T>(val, m_head);
	if (m_tail == nullptr)
		m_tail = new_head;
	m_head = new_head;
	m_size++;
}

template<typename T>
inline void SinglyLinkedList<T>::push_back(T val)
{
	SinglyLinkedListNode<T>* new_tail = new SinglyLinkedListNode<T>(val);
	if (m_tail == nullptr)
	{
		m_tail = new_tail;
		m_head = m_tail;
	}
	else
	{
		m_tail->next = new_tail;
		m_tail = new_tail;
	}
	m_size++;
}

template<typename T>
inline void SinglyLinkedList<T>::pop_front()
{
	if (m_head == nullptr)
		throw std::runtime_error("Trying to pop from empty list\n");
	SinglyLinkedListNode<T>* next = m_head->next;
	delete m_head;
	m_head = next;
	if (m_head == nullptr)
		m_tail = nullptr;
	m_size--;
}

template<typename T>
inline void SinglyLinkedList<T>::pop_back()
{
	if (m_tail == nullptr)
		throw std::runtime_error("Trying to pop from empty list\n");
	SinglyLinkedListNode<T>* prev_tail = m_head;
	if (prev_tail == m_tail)
	{
		delete prev_tail;
		m_head = nullptr;
		m_tail = nullptr;
	}
	else
	{
		while (prev_tail->next != m_tail)
			prev_tail = prev_tail->next;
		prev_tail->next = nullptr;
		delete m_tail;
		m_tail = prev_tail;
	}
	m_size--;
}

template<typename T>
inline T& SinglyLinkedList<T>::front()
{
	if (m_head == nullptr)
		throw std::runtime_error("Trying to access empty list element\n");
	return m_head->data;
}

template<typename T>
inline const T& SinglyLinkedList<T>::front() const
{
	if (m_head == nullptr)
		throw std::runtime_error("Trying to access empty list element\n");
	return m_head->data;
}

template<typename T>
inline T& SinglyLinkedList<T>::back()
{
	if (m_tail == nullptr)
		throw std::runtime_error("Trying to access empty list element\n");
	return m_tail->data;
}

template<typename T>
inline const T& SinglyLinkedList<T>::back() const
{
	if (m_tail == nullptr)
		throw std::runtime_error("Trying to access empty list element\n");
	return m_tail->data;
}

template<typename T>
inline SinglyLinkedListIterator<T> SinglyLinkedList<T>::begin()
{
	return SinglyLinkedListIterator<T>(m_head);
}

template<typename T>
inline SinglyLinkedListIterator<T> SinglyLinkedList<T>::end()
{
	return SinglyLinkedListIterator<T>(m_tail->next);
}

template<typename T>
inline T& SinglyLinkedList<T>::operator[](int n)
{
	if (m_head == nullptr)
		throw std::runtime_error("Trying to access empty list element\n");
	SinglyLinkedListNode<T>* ptr = m_head;
	for (n; n > 0; n--)
	{
		ptr = ptr->next;
		if (ptr == nullptr)
			throw std::runtime_error("Invalid list element index\n");
	}
	return ptr->data;
}

template<typename T>
inline const T& SinglyLinkedList<T>::operator[](int n) const
{
	if (m_head == nullptr)
		throw std::runtime_error("Trying to access empty list element\n");
	const SinglyLinkedListNode<T>* ptr= m_head;
	for (n; n > 0; n--)
	{
		ptr = ptr->next;
		if (ptr == nullptr)
			throw std::runtime_error("Invalid list element index\n");
	}
	return ptr->data;
}

template<typename T>
inline SinglyLinkedList<T>::~SinglyLinkedList()
{
	while (m_head != nullptr)
	{
		SinglyLinkedListNode<T>* next = m_head->next;
		delete m_head;
		m_head = next;
	}
}

template<typename T>
inline SinglyLinkedListIterator<T>::SinglyLinkedListIterator(SinglyLinkedListNode<T>* node)
{
	this->node = node;
}

template<typename T>
inline SinglyLinkedListIterator<T>::SinglyLinkedListIterator(const SinglyLinkedListIterator<T>& copy)
{
	this->node = copy.node;
}

template<typename T>
inline SinglyLinkedListIterator<T>::SinglyLinkedListIterator(SinglyLinkedListIterator<T>&& moved)
{
	this->node = moved.node;
	moved.node = nullptr;
}

template<typename T>
inline SinglyLinkedListIterator<T>& SinglyLinkedListIterator<T>::operator=(const SinglyLinkedListIterator& copy)
{
	if (this == &copy)
		return *this;
	this->node = copy.node;
	return *this;
}

template<typename T>
inline SinglyLinkedListIterator<T>& SinglyLinkedListIterator<T>::operator=(SinglyLinkedListIterator<T>&& moved)
{
	if (this == &moved)
		return *this;
	this->node = moved.node;
	moved.node = nullptr;
}

template<typename T>
inline SinglyLinkedListIterator<T>& SinglyLinkedListIterator<T>::operator++()
{
	node = node->next;
	return *this;
}

template<typename T>
inline SinglyLinkedListIterator<T> SinglyLinkedListIterator<T>::operator++(int)
{
	SinglyLinkedListIterator<T> copy(*this);
	this->node = this->node->next;
	return copy;
}

template<typename T>
inline T& SinglyLinkedListIterator<T>::operator*()
{
	return this->node->data;
}

template<typename T>
inline bool SinglyLinkedListIterator<T>::operator==(const SinglyLinkedListIterator<T>& other) const
{
	return this->node == other.node;
}

template<typename T>
inline bool SinglyLinkedListIterator<T>::operator!=(const SinglyLinkedListIterator<T>& other) const
{
	return this->node != other.node;
}
