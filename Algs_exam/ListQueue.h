#pragma once

#include "DoublyLinkedList.h"

#include <stdexcept>
#include <initializer_list>

template<typename T>
class ListQueue
{
	DoublyLinkedList<T> m_queue;

public:

	ListQueue() = default;

	ListQueue(std::initializer_list<T> init);

	T& front();
	const T& front() const;

	T& back();
	const T& back() const;

	bool empty() const;

	size_t size() const;

	template<typename Y>
	void push(Y&& val);

	void pop();

	~ListQueue() = default;
};

template<typename T>
inline ListQueue<T>::ListQueue(std::initializer_list<T> init):
	m_queue(init)
{
}

template<typename T>
inline T& ListQueue<T>::front()
{
	if(m_queue.empty())
		throw std::runtime_error("Trying to access to empty queue\n");
	return m_queue.front();
}

template<typename T>
inline const T& ListQueue<T>::front() const
{
	if (m_queue.empty())
		throw std::runtime_error("Trying to access to empty queue\n");
	return m_queue.front();
}

template<typename T>
inline T& ListQueue<T>::back()
{
	if (m_queue.empty())
		throw std::runtime_error("Trying to access to empty queue\n");
	return m_queue.back();
}

template<typename T>
inline const T& ListQueue<T>::back() const
{
	if (m_queue.empty())
		throw std::runtime_error("Trying to access to empty queue\n");
	return m_queue.back();
}

template<typename T>
inline bool ListQueue<T>::empty() const
{
	return m_queue.empty();
}

template<typename T>
inline size_t ListQueue<T>::size() const
{
	return m_queue.size();
}

template<typename T>
inline void ListQueue<T>::pop()
{
	m_queue.pop_front();
}

template<typename T>
template<typename Y>
inline void ListQueue<T>::push(Y&& val)
{
	m_queue.push_back(std::forward<Y>(val));
}
