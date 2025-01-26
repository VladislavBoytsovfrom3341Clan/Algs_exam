#include <list>
#include <stack>
#include <deque>

#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"
#include "VectorStack.h"
#include "LLStack.h"
#include "VectorQueue.h"
#include "ListQueue.h"
#include "DLLDeque.h"
#include "TwoStackDeque.h"
#include "InsertionSort.h"
#include "mergeSort.h"
#include "QuickSort.h"
#include "CountingSort.h"
#include "MaxHeap.h"
#include "AVLTree.h"

#include <chrono>
#include <random>
#include <iostream>

typedef std::chrono::milliseconds ms;
typedef std::chrono::microseconds mc;
typedef std::chrono::nanoseconds ns;

template<typename t>
std::string time_type()
{
	if (typeid(t) == typeid(ms))
		return " ms ";
	if (typeid(t) == typeid(mc))
		return " mc ";
	if (typeid(t) == typeid(ns))
		return " ns ";
	return " ";
}

template<typename t>
void single_time_test()
{
	//INIT STRUCTURE	

	AVLTree<int> avl;

	auto start = std::chrono::high_resolution_clock::now();

	//RUN TEST	
	avl.insert(5);

	auto end = std::chrono::high_resolution_clock::now();
	t time = std::chrono::duration_cast<t>(end - start);
	std::cout << static_cast<double>(time.count()) <<time_type<t>()<< '\n';
}

template<typename t>
void multiple_time_test(size_t num)
{
	//INIT STRUCTURE	

	AVLTree<int> avl;

	auto start = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < num; i++)
	{
		//RUN TEST	
		avl.insert(5);
	}

	auto end = std::chrono::high_resolution_clock::now();
	t time = std::chrono::duration_cast<t>(end - start);
	std::cout << static_cast<double>(time.count()) << time_type<t>() << '\n';
}

template<typename t>
void prepared_single_time_test(size_t prepared)
{
	//INIT STRUCTURE	

	AVLTree<int> avl;

	for (size_t i = 0; i < prepared; i++)
	{
		//DO PREPARATIONS
		avl.insert(rand() % 500);
	}

	auto start = std::chrono::high_resolution_clock::now();

	//RUN TEST	
	avl.insert(5);

	auto end = std::chrono::high_resolution_clock::now();
	t time = std::chrono::duration_cast<t>(end - start);
	std::cout << static_cast<double>(time.count()) << time_type<t>() << '\n';
}

template<typename t>
void prepared_multiple_time_test(size_t prepared, size_t num)
{
	//INIT STRUCTURE	

	AVLTree<int> avl;

	for (size_t i = 0; i < prepared; i++)
	{
		//DO PREPARATIONS
		avl.insert(rand() % 500);
	}

	auto start = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < num; i++)
	{
		//RUN TEST	
		avl.insert(5);
	}

	auto end = std::chrono::high_resolution_clock::now();
	t time = std::chrono::duration_cast<t>(end - start);
	std::cout << static_cast<double>(time.count()) << time_type<t>() << '\n';
}

template<typename t>
void run_test_batch()
{
	static std::vector<size_t> batches = {10, 100, 1000, 10000, 100000, 1000000};
	for (auto& batch : batches)
	{
		//USE TESTS
		prepared_single_time_test<t>(batch);
	}
}

//int main()
//{
//	srand(time(NULL));
//	single_time_test<ns>();
//	multiple_time_test<ms>(100000);
//	prepared_single_time_test<ns>(1000000);
//	prepared_multiple_time_test<ms>(100000, 100000);
//	run_test_batch<mc>();
//}