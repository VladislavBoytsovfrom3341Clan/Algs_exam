#pragma once

#include "VectorStack.h"
#include "LLStack.h"

#include <initializer_list>
#include <stack>
#include <stdexcept>

template<typename T, template<typename T> typename Stack>
class TwoStackDeque
{
	Stack<T> m_left_stack;
	Stack<T> m_right_stack;

public:

	TwoStackDeque() = default;

	TwoStackDeque(std::initializer_list<T> init);

	bool empty();

	size_t size();

	template<typename Y>
	void push_back(Y&& val);

	template<typename Y>
	void push_front(Y&& val);

	void pop_back();

	void pop_front();

	T front();

	T back();

	~TwoStackDeque() = default;
};
template<typename T, template<typename T> typename Stack>
TwoStackDeque<T, Stack>::TwoStackDeque(std::initializer_list<T> init)
{
	for (auto i : init)
		this->push_back(i);
}

template<typename T, template<typename T> typename Stack>
template<typename Y>
inline void TwoStackDeque<T, Stack>::push_back(Y&& val)
{
	m_left_stack.push(std::forward<Y>(val));
}

template<typename T, template<typename T> typename Stack>
template<typename Y>
inline void TwoStackDeque<T, Stack>::push_front(Y&& val)
{
	m_right_stack.push(std::forward<Y>(val));
}

template<typename T, template<typename T> typename Stack>
inline bool TwoStackDeque<T, Stack>::empty()
{
	return m_left_stack.empty() && m_right_stack.empty();
}

template<typename T, template<typename T> typename Stack>
inline size_t TwoStackDeque<T, Stack>::size()
{
	return m_left_stack.size() + m_right_stack.size();
}

template<typename T, template<typename T> typename Stack>
inline void TwoStackDeque<T, Stack>::pop_back()
{
	if (!m_left_stack.empty())
		m_left_stack.pop();
	else
	{
		size_t r_size = m_right_stack.size();
		Stack<T> local;
		for (int i = 0; i < r_size / 2; i++)
		{
			local.push(m_right_stack.top());
			m_right_stack.pop();
		}
		while (!m_right_stack.empty())
		{
			m_left_stack.push(m_right_stack.top());
			m_right_stack.pop();
		}
		while (!local.empty())
		{
			m_right_stack.push(local.top());
			local.pop();
		}
		m_left_stack.pop();
	}
}

template<typename T, template<typename T> typename Stack>
inline void TwoStackDeque<T, Stack>::pop_front()
{
	if (!m_right_stack.empty())
		m_right_stack.pop();
	else
	{
		size_t l_size = m_left_stack.size();
		Stack<T> local;
		for (int i = 0; i < l_size / 2; i++)
		{
			local.push(m_left_stack.top());
			m_left_stack.pop();
		}
		while (!m_left_stack.empty())
		{
			m_right_stack.push(m_left_stack.top());
			m_left_stack.pop();
		}
		while (!local.empty())
		{
			m_left_stack.push(local.top());
			local.pop();
		}
		m_right_stack.pop();
	}
}

template<typename T, template<typename T> typename Stack>
inline T TwoStackDeque<T, Stack>::back()
{
	if (!m_left_stack.empty())
		return m_left_stack.top();
	else
	{
		size_t r_size = m_right_stack.size();
		Stack<T> local;
		for (int i = 0; i < r_size / 2; i++)
		{
			local.push(m_right_stack.top());
			m_right_stack.pop();
		}
		while (!m_right_stack.empty())
		{
			m_left_stack.push(m_right_stack.top());
			m_right_stack.pop();
		}
		while (!local.empty())
		{
			m_right_stack.push(local.top());
			local.pop();
		}
		return m_left_stack.top();
	}
}

template<typename T, template<typename T> typename Stack>
inline T TwoStackDeque<T, Stack>::front()
{
	if (!m_right_stack.empty())
		return m_right_stack.top();
	else
	{
		size_t l_size = m_left_stack.size();
		Stack<T> local;
		for (int i = 0; i < l_size / 2; i++)
		{
			local.push(m_left_stack.top());
			m_left_stack.pop();
		}
		while (!m_left_stack.empty())
		{
			m_right_stack.push(m_left_stack.top());
			m_left_stack.pop();
		}
		while (!local.empty())
		{
			m_left_stack.push(local.top());
			local.pop();
		}
		return m_right_stack.top();
	}
}
