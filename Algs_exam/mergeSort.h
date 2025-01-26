#pragma once

#include <vector>

template<typename T>
void merge(std::vector<T>& A, int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;
    std::vector<T> left;
    for (int i = 0; i < n1; i++)
        left.push_back(A.at(p + i));
    std::vector<T> right;
    for (int i = 0; i < n2; i++)
        right.push_back(A.at(q + i + 1));
    int i = 0, j = 0;
    for (int k = p; k <= r; k++)
    {
        if (i < left.size() && (j >= right.size() || left.at(i) <= right.at(j)))
        {
            A.at(k) = left.at(i);
            i++;
        }
        else
        {
            if (j < right.size())
            {
                A.at(k) = right.at(j);
                j++;
            }
        }
    }
}

template<typename T>
void mergeSort(std::vector<T>& A, int p, int r)
{
    if (p < r)
    {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}
