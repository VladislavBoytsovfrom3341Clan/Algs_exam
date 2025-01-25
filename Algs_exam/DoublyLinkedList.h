#pragma once

#include <stdexcept>

template<typename T>
class DoublyLinkedList;

template<typename T>
struct DoublyLinkedListNode
{
	T data;
	DoublyLinkedListNode<T>* prev = nullptr;
	DoublyLinkedListNode<T>* next = nullptr;

	DoublyLinkedListNode() = default;

	DoublyLinkedListNode(T val);
};

template<typename T>
class DoublyLinkedListIterator
{
	DoublyLinkedListNode<T>* node;
	DoublyLinkedListNode<T>* head = nullptr;
	DoublyLinkedListNode<T>* tail = nullptr;

	friend class DoublyLinkedList<T>;

public:

	DoublyLinkedListIterator(DoublyLinkedListNode<T>* node, DoublyLinkedListNode<T>* real_tail);

	DoublyLinkedListIterator(const DoublyLinkedListIterator<T>& copy);

	DoublyLinkedListIterator(DoublyLinkedListIterator<T>&& moved);

	DoublyLinkedListIterator<T>& operator=(const DoublyLinkedListIterator<T>& copy);

	DoublyLinkedListIterator<T>& operator=(DoublyLinkedListIterator<T>&& moved);

	DoublyLinkedListIterator<T>& operator++();

	DoublyLinkedListIterator<T>& operator--();

	DoublyLinkedListIterator<T> operator++(int);

	DoublyLinkedListIterator<T> operator--(int);

	T& operator*();

	bool operator==(const DoublyLinkedListIterator<T>& other) const;

	bool operator!=(const DoublyLinkedListIterator<T>& other) const;
};

template<typename T>
class DoublyLinkedList
{
	DoublyLinkedListNode<T>* m_head = nullptr;
	DoublyLinkedListNode<T>* m_tail = nullptr;
	size_t m_size = 0;

public:

	DoublyLinkedList() = default;

	DoublyLinkedList(T val);

	bool empty() const;

	int size() const;

	void push_front(T val);

	void push_back(T val);

	void insert(DoublyLinkedListIterator<T> pos, T&& val);

	void pop_front();

	void pop_back();

	T& front();

	T& back();

	DoublyLinkedListIterator<T> begin();

	DoublyLinkedListIterator<T> end();

	T& operator[](int n);

	const T& operator[](int n) const;

	~DoublyLinkedList();
};

template<typename T>
inline DoublyLinkedListNode<T>::DoublyLinkedListNode(T val)
{
	data = val;
}

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList(T val)
{
	m_head = new DoublyLinkedListNode<T>(val);
	m_tail = m_head;
	m_size = 1;
}

template<typename T>
inline bool DoublyLinkedList<T>::empty() const
{
	return m_head == nullptr;
}

template<typename T>
inline int DoublyLinkedList<T>::size() const
{
	return m_size;
}

template<typename T>
inline void DoublyLinkedList<T>::push_front(T val)
{
	DoublyLinkedListNode<T>* new_head = new DoublyLinkedListNode<T>(val);
	if (m_head == nullptr)
	{
		m_head = new_head;
		m_tail = new_head;
	}
	else
	{
		m_head->prev = new_head;
		new_head->next = m_head;
		m_head = new_head;
	}
	m_size++;
}

template<typename T>
inline void DoublyLinkedList<T>::push_back(T val)
{
	DoublyLinkedListNode<T>* new_tail = new DoublyLinkedListNode<T>(val);
	if (m_tail == nullptr)
	{
		m_tail = new_tail;
		m_head = new_tail;
	}
	else
	{
		m_tail->next = new_tail;
		new_tail->prev = m_tail;
		m_tail = new_tail;
	}
	m_size++;
}

template<typename T>
inline void DoublyLinkedList<T>::insert(DoublyLinkedListIterator<T> pos, T&& val)
{
	DoublyLinkedListNode<T>* new_node = new DoublyLinkedListNode<T>(std::forward<T>(val));
	if (this->empty())
	{
		m_head = new_node;
		m_tail = new_node;
		m_size++;
		return;
	}
	if (pos.node == nullptr)
	{
		m_tail->next = new_node;
		new_node->prev = m_tail;
		m_tail = new_node;
		m_size++;
		return;
	}
	DoublyLinkedListNode<T>* prev = pos.node->prev;
	new_node->next = pos.node;
	new_node->prev = prev;
	pos.node->prev = new_node;
	if (prev != nullptr)
		prev->next = new_node;
	else
		m_head = new_node;
	m_size++;
}

template<typename T>
inline void DoublyLinkedList<T>::pop_front()
{
	if(m_head == nullptr)
		throw std::runtime_error("Trying to pop from empty list\n");
	DoublyLinkedListNode<T>* ptr = m_head->next;
	if (ptr == nullptr)
	{
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
	}
	else
	{
		delete m_head;
		ptr->prev = nullptr;
		m_head = ptr;
	}
	m_size--;
}

template<typename T>
inline void DoublyLinkedList<T>::pop_back()
{
	if(m_tail == nullptr)
		throw std::runtime_error("Trying to pop from empty list\n");
	DoublyLinkedListNode<T>* ptr = m_tail->prev;
	if (ptr == nullptr)
	{
		delete m_tail;
		m_tail = nullptr;
		m_head = nullptr;
	}
	else
	{
		delete m_tail;
		ptr->next = nullptr;
		m_tail = ptr;
	}
	m_size--;
}

template<typename T>
inline T& DoublyLinkedList<T>::front()
{
	if(m_head == nullptr)
		throw std::runtime_error("Trying to access to empty list\n");
	return m_head->data;
}

template<typename T>
inline T& DoublyLinkedList<T>::back()
{
	if (m_tail == nullptr)
		throw std::runtime_error("Trying to access to empty list\n");
	return m_tail->data;
}

template<typename T>
inline DoublyLinkedListIterator<T> DoublyLinkedList<T>::begin()
{
	return DoublyLinkedListIterator<T>(m_head, m_tail);
}

template<typename T>
inline DoublyLinkedListIterator<T> DoublyLinkedList<T>::end()
{
	return DoublyLinkedListIterator<T>(nullptr, m_tail);
}

template<typename T>
inline T& DoublyLinkedList<T>::operator[](int n)
{
	if (m_head == nullptr)
		throw std::runtime_error("Trying to access to empty list\n");
	DoublyLinkedListNode<T>* ptr = m_head;
	for (n; n > 0; n--)
	{
		ptr = ptr->next;
		if (ptr == nullptr)
			throw std::runtime_error("Invalid list element index\n");
	}
	return ptr->data;
}

template<typename T>
inline const T& DoublyLinkedList<T>::operator[](int n) const
{
	if (m_head == nullptr)
		throw std::runtime_error("Trying to access to empty list\n");
	const DoublyLinkedListNode<T>* ptr = m_head;
	for (n; n > 0; n--)
	{
		ptr = ptr->next;
		if (ptr == nullptr)
			throw std::runtime_error("Invalid list element index\n");
	}
	return ptr->data;
}

template<typename T>
inline DoublyLinkedList<T>::~DoublyLinkedList()
{
	DoublyLinkedListNode<T>* ptr = m_head;
	while (ptr != nullptr)
	{
		ptr = m_head->next;
		delete m_head;
		m_head = ptr;
	}
}

template<typename T>
inline DoublyLinkedListIterator<T>::DoublyLinkedListIterator(DoublyLinkedListNode<T>* node, DoublyLinkedListNode<T>* real_tail)
{
	this->node = node;
	this->tail = real_tail;
}

template<typename T>
inline DoublyLinkedListIterator<T>::DoublyLinkedListIterator(const DoublyLinkedListIterator<T>& copy)
{
	this->node = copy.node;
}

template<typename T>
inline DoublyLinkedListIterator<T>::DoublyLinkedListIterator(DoublyLinkedListIterator<T>&& moved)
{
	this->node = moved.node;
	moved.node = nullptr;
}

template<typename T>
inline DoublyLinkedListIterator<T>& DoublyLinkedListIterator<T>::operator=(const DoublyLinkedListIterator<T>& copy)
{
	if (this == &copy)
		return *this;
	this->node = copy.node;
	return *this;
}

template<typename T>
inline DoublyLinkedListIterator<T>& DoublyLinkedListIterator<T>::operator=(DoublyLinkedListIterator<T>&& moved)
{
	if (this == &moved)
		return *this;
	this->node = moved.node;
	moved.node = nullptr;
	return *this;
}

template<typename T>
inline DoublyLinkedListIterator<T>& DoublyLinkedListIterator<T>::operator++()
{
	this->node = this->node->next;
	return *this;
}

template<typename T>
inline DoublyLinkedListIterator<T>& DoublyLinkedListIterator<T>::operator--()
{
	if (this->node == nullptr)
		this->node = this->tail;
	else
		this->node = this->node->prev;
	return *this;
}

template<typename T>
inline DoublyLinkedListIterator<T> DoublyLinkedListIterator<T>::operator++(int)
{
	DoublyLinkedListIterator<T> temp(*this);
	this->node = this->node->next;
	return temp;
}

template<typename T>
inline DoublyLinkedListIterator<T> DoublyLinkedListIterator<T>::operator--(int)
{
	DoublyLinkedListIterator<T> temp(*this);
	if (this->node == nullptr)
		this->node = this->tail;
	else
		this->node = this->node->prev;
	return temp;
}

template<typename T>
inline T& DoublyLinkedListIterator<T>::operator*()
{
	return this->node->data;
}

template<typename T>
inline bool DoublyLinkedListIterator<T>::operator==(const DoublyLinkedListIterator<T>& other) const
{
	return this->node == other.node;
}

template<typename T>
inline bool DoublyLinkedListIterator<T>::operator!=(const DoublyLinkedListIterator<T>& other) const
{
	return node != other.node;
}
