#pragma once

#include <vector>

template<typename T>
void insertionSort(std::_Vector_iterator<T> start, std::_Vector_iterator<T> end);

template<typename T>
inline void insertionSort(std::_Vector_iterator<T> start, std::_Vector_iterator<T> end)
{
	for (auto j = start + 1; j < end; j++)
	{
		auto key = *j;
		auto i = j - 1;
		while (i != end && *i > key)
		{
			*(i + 1) = *i;
			if (i > start)
				i--;
			else
				i = end;
		}
		if (i != end)
			*(i + 1) = key;
		else
			*start = key;
	}
}
