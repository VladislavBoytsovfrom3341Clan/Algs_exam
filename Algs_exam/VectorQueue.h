#pragma once

#include <vector>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class VectorQueue
{
	std::vector<T> m_queue;
	size_t m_head = 0;
	size_t m_tail = 0;

public:

	VectorQueue() = default;

	VectorQueue(std::initializer_list<T> init);

	T& front();
	const T& front() const;

	T& back();
	const T& back() const;

	bool empty() const;

	size_t size() const;

	template<typename Y>
	void push(Y&& val);

	void pop();

	~VectorQueue() = default;
};

template<typename T>
inline VectorQueue<T>::VectorQueue(std::initializer_list<T> init):
	m_queue(init)
{
	m_head = 0;
	m_tail = m_queue.size();
}

template<typename T>
inline T& VectorQueue<T>::front()
{
	if (this->size() == 0)
		throw std::runtime_error("Trying to access to empty queue\n");
	return m_queue[m_head];
}

template<typename T>
inline const T& VectorQueue<T>::front() const
{
	if (this->size() == 0)
		throw std::runtime_error("Trying to access to empty queue\n");
	return m_queue[m_head];
}

template<typename T>
inline T& VectorQueue<T>::back()
{
	if (this->size() == 0)
		throw std::runtime_error("Trying to access to empty queue\n");
	return m_queue[m_tail - 1];
}

template<typename T>
inline const T& VectorQueue<T>::back() const
{
	if (this->size() == 0)
		throw std::runtime_error("Trying to access to empty queue\n");
	return m_queue[m_tail - 1];
}

template<typename T>
inline bool VectorQueue<T>::empty() const
{
	return m_head == m_tail;
}

template<typename T>
inline size_t VectorQueue<T>::size() const
{
	return m_tail - m_head;
}

template<typename T>
inline void VectorQueue<T>::pop()
{
	if (this->size() == 0)
		throw std::runtime_error("Trying to access to empty queue\n");
	m_head++;
	if (m_head > m_queue.size() / 4)	//cut the head if needed
	{
		std::move(m_queue.begin() + m_head, m_queue.begin() + m_tail, m_queue.begin());
		size_t new_size = m_tail - m_head;
		m_queue.resize(new_size);
		m_head = 0;
		m_tail = new_size;
	}
}

template<typename T>
template<typename Y>
inline void VectorQueue<T>::push(Y&& val)
{
	m_queue.push_back(std::forward<Y>(val));
	m_tail++;
}
