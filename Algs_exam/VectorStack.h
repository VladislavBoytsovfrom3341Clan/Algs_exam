#pragma once

#include <vector>
#include <stdexcept>
#include <initializer_list>

template<typename T>
class VectorStack
{
	std::vector<T> m_stack;

public:

	VectorStack() = default;

	VectorStack(std::initializer_list<T> init);

	template<typename Y>
	void push(Y&& val);

	void pop();

	T& top();

	const T& top() const;

	bool empty() const;

	size_t size() const;

	~VectorStack() = default;
};

template<typename T>
inline VectorStack<T>::VectorStack(std::initializer_list<T> init):
	m_stack(init)
{
}

template<typename T>
template<typename Y>
inline void VectorStack<T>::push(Y&& val)
{
	m_stack.push_back(std::forward<Y>(val));
}

template<typename T>
inline void VectorStack<T>::pop()
{
	if (m_stack.empty())
		throw std::runtime_error("Trying to pop from empty stack\n");
	m_stack.pop_back();
}

template<typename T>
inline T& VectorStack<T>::top()
{
	if (m_stack.empty())
		throw std::runtime_error("Trying to access to an empty stack\n");
	return m_stack.back();
}

template<typename T>
inline const T& VectorStack<T>::top() const
{
	if (m_stack.empty())
		throw std::runtime_error("Trying to access to an empty stack\n");
	return m_stack.back();
}

template<typename T>
inline bool VectorStack<T>::empty() const
{
	return m_stack.empty();
}

template<typename T>
inline size_t VectorStack<T>::size() const
{
	return m_stack.size();
}

