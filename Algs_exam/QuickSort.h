#pragma once

#include <vector>
#include <random>

template<typename T>
int partition(std::vector<T>& a, int p, int r)
{
	T x = a.at(r);
	int i = p - 1;
	for (int j = p; j < r ; j++)
	{
		if (a.at(j) <= x)
		{
			i++;
			std::swap(a.at(i), a.at(j));
		}
	}
	std::swap(a[i+1], a[r]);
	return i + 1;
}

template<typename T>
void quickSort(std::vector<T>& a, int p, int r)
{
	if (p < r)
	{
		int q = partition(a, p, r);
		quickSort(a, p, q - 1);
		quickSort(a, q + 1, r);
	}
}