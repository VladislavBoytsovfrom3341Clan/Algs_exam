#pragma once
#include "SinglyLinkedList.h"

#include <stdexcept>

template<typename T>
class LLStack
{
	SinglyLinkedList<T> m_list;

public:

	LLStack() = default;

	LLStack(std::initializer_list<T> init);

	template<typename Y>
	void push(Y&& val);

	void pop();

	T& top();

	const T& top() const;

	bool empty() const;

	size_t size() const;

	~LLStack() = default;
};

template<typename T>
inline LLStack<T>::LLStack(std::initializer_list<T> init)
{
	for (auto& i : init)
		m_list.push_front(i);
}

template<typename T>
inline void LLStack<T>::pop()
{
	m_list.pop_front();
}

template<typename T>
inline T& LLStack<T>::top()
{
	if (m_list.empty())
		throw std::runtime_error("trying to access to an empty stack\n");
	return m_list.front();
}

template<typename T>
inline const T& LLStack<T>::top() const
{
	if (m_list.empty())
		throw std::runtime_error("trying to access to an empty stack\n");
	return m_list.front();
}

template<typename T>
inline bool LLStack<T>::empty() const
{
	return m_list.empty();
}

template<typename T>
inline size_t LLStack<T>::size() const
{
	return m_list.size();
}

template<typename T>
template<typename Y>
inline void LLStack<T>::push(Y&& val)
{
	m_list.push_front(std::forward<Y>(val));
}
