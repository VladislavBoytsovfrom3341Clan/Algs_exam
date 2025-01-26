#pragma once

#include <stdexcept>
#include <initializer_list>

template<typename T>
class DoublyLinkedList;

template<typename T>
struct DoublyLinkedListNode
{
	T data;
	DoublyLinkedListNode<T>* prev = nullptr;
	DoublyLinkedListNode<T>* next = nullptr;

	DoublyLinkedListNode() = default;

	template<typename Y>
	DoublyLinkedListNode(Y&& val);
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

	DoublyLinkedList(std::initializer_list<T> init);

	bool empty() const;

	size_t size() const;

	template<typename Y>
	void push_front(Y&& val);

	template<typename Y>
	void push_back(Y&& val);

	template<typename Y>
	void insert(DoublyLinkedListIterator<T> pos, Y&& val);

	void pop_front();

	void pop_back();

	void erase(DoublyLinkedListIterator<T> pos);

	T& front();

	const T& front() const;

	T& back();

	const T& back() const;

	DoublyLinkedListIterator<T> begin();

	DoublyLinkedListIterator<T> end();

	T& operator[](int n);

	const T& operator[](int n) const;

	~DoublyLinkedList();
};

template<typename T>
template<typename Y>
inline DoublyLinkedListNode<T>::DoublyLinkedListNode(Y&& val):
	data(std::forward<Y>(val))
{
}

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList(T val)
{
	m_head = new DoublyLinkedListNode<T>(val);
	m_tail = m_head;
	m_size = 1;
}

template<typename T>
inline DoublyLinkedList<T>::DoublyLinkedList(std::initializer_list<T> init)
{
	for (auto& i : init)
	{
		this->push_back(std::move(i));
	}
}

template<typename T>
inline bool DoublyLinkedList<T>::empty() const
{
	return m_head == nullptr;
}

template<typename T>
inline size_t DoublyLinkedList<T>::size() const
{
	return m_size;
}

template<typename T>
template<typename Y>
inline void DoublyLinkedList<T>::push_front(Y&& val)
{
	DoublyLinkedListNode<T>* new_head = new DoublyLinkedListNode<T>(std::forward<Y>(val));
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
template<typename Y>
inline void DoublyLinkedList<T>::push_back(Y&& val)
{
	DoublyLinkedListNode<T>* new_tail = new DoublyLinkedListNode<T>(std::forward<Y>(val));
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
template<typename Y>
inline void DoublyLinkedList<T>::insert(DoublyLinkedListIterator<T> pos, Y&& val)
{
	DoublyLinkedListNode<T>* new_node = new DoublyLinkedListNode<T>(std::forward<Y>(val));
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
inline void DoublyLinkedList<T>::erase(DoublyLinkedListIterator<T> pos)
{
	if (pos.node == nullptr)
		throw std::runtime_error("Invalid iterator\n");
	if (m_head == nullptr)
		throw std::runtime_error("Trying to erase from empty list\n");
	if (pos.node == m_head && m_head == m_tail)
	{
		delete pos.node;
		m_tail = nullptr;
		m_head = nullptr; 
		m_size = 0;
		return;
	}
	if (pos.node == m_head)
	{
		pos.node->next->prev = nullptr;
		m_head = pos.node->next;
		delete pos.node;
	}
	else if (pos.node == m_tail)
	{
		pos.node->prev->next = nullptr;
		m_tail = pos.node->prev;
		delete pos.node;
	}
	else
	{
		pos.node->prev->next = pos.node->next;
		pos.node->next->prev = pos.node->prev;
		delete pos.node;
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
inline const T& DoublyLinkedList<T>::front() const
{
	if (m_head == nullptr)
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
inline const T& DoublyLinkedList<T>::back() const
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
