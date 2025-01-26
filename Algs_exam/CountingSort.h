#pragma once

#include <vector>

template<typename T>
void countingSort(std::vector<T>& a)
{
	T k = *std::max_element(a.begin(), a.end());
	std::vector<int> c(k+1);
	for (int j = 0; j < a.size(); j++)
		c[a[j]]++;
	for (int i = 1; i <= k; i++)
		c[i] += c[i - 1];
	std::vector<T> b(a.size());
	for (int j = a.size() - 1; j >= 0; j--)
	{
		b[c[a[j]] - 1] = a[j];
		c[a[j]]--;
	}
	a = std::move(b);
}