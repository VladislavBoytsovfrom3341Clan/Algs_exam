#pragma once

#include <vector>

template<typename T>
class MaxHeap
{
	std::vector<T> m_heap;

	size_t left(size_t i);

	size_t right(size_t i);

	void max_heapify(size_t i);

public:

	MaxHeap(std::vector<T> init);

	std::vector<T>& deheap() { return m_heap; }

	template<typename Y>
	void insert(Y&& val);

	void pop_max();

	T& max();

};

template<typename T>
inline size_t MaxHeap<T>::left(size_t i)
{
	return 2*i + 1;
}

template<typename T>
inline size_t MaxHeap<T>::right(size_t i)
{
	return 2*i + 2;
}

template<typename T>
inline void MaxHeap<T>::max_heapify(size_t i)
{
	size_t l = left(i);
	size_t r = right(i);
	size_t largest;
	if (l < m_heap.size() && m_heap[l] > m_heap[i])
		largest = l;
	else
		largest = i;
	if (r<m_heap.size() && m_heap[r]>m_heap[largest])
		largest = r;
	if (largest != i)
	{
		std::swap(m_heap[i], m_heap[largest]);
		max_heapify(largest);
	}
}

template<typename T>
inline MaxHeap<T>::MaxHeap(std::vector<T> init):
	m_heap(init)
{
	for (int i = m_heap.size() / 2; i >= 0; i--)
		max_heapify(i);
}

template<typename T>
inline void MaxHeap<T>::pop_max()
{
	if (m_heap.empty())
		throw std::out_of_range("Heap is empty");

	T max_val = m_heap.front();
	m_heap[0] = m_heap.back();
	m_heap.pop_back();

	if (!m_heap.empty())
		max_heapify(0);
}

template<typename T>
inline T& MaxHeap<T>::max()
{
	return m_heap.front();
}

template<typename T>
template<typename Y>
inline void MaxHeap<T>::insert(Y&& val)
{
	m_heap.push_back(std::forward<Y>(val));
	size_t i = m_heap.size() - 1;

	while (i > 0 && m_heap[(i - 1) / 2] < m_heap[i])
	{
		std::swap(m_heap[i], m_heap[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}
