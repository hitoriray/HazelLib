#define _CRT_NO_SECURE_WARNINGS

#include <iostream>
#include "../Vector/Vector.h"
#include "../Algorithm/Algorithm.h"
#include "../Timer/Timer.h"

using namespace Hazel;

#define QUICK_SORT
//#define MERGE_SORT
//#define SELECTION_SORT
//#define INSERTION_SORT
//#define SHELL_SORT
//#define BUBBLE_SORT

const int CNT = 100;
const int LEN = 100;
const int START_INT = 0, END_INT = 100001;
const double START_DB = 0.0, END_DB = 1e6;

// O(n) = nlogn
void QuickSort(Vector<int>& v)
{
	Timer t;
	for (int i = 0; i < CNT; i++)
	{
		shuffle(v);
		quick_sort(v);
	}
}

// O(n) = nlogn
void MergeSort(Vector<int>& v)
{
	Timer t;
	for (int i = 0; i < CNT; i++)
	{
		shuffle(v);
		merge_sort(v);
	}
}

// O(n) = n^2
void SelectionSort(Vector<int>& v)
{
	Timer t;
	for (int i = 0; i < CNT; i++)
	{
		shuffle(v);
		selection_sort(v);
	}
}

// O(n) = n^2
void InsertionSort(Vector<int>& v)
{
	Timer t;
	for (int i = 0; i < CNT; i++)
	{
		shuffle(v);
		insertion_sort(v);
	}
}

// O(n) = n^2
void ShellSort(Vector<int>& v)
{
	Timer t;
	for (int i = 0; i < CNT; i++)
	{
		shuffle(v);
		shell_sort(v);
	}
}

// O(n) = n^2
void BubbleSort(Vector<int>& v)
{
	Timer t;
	for (int i = 0; i < CNT; i++)
	{
		shuffle(v);
		bubble_sort(v);
	}
}

int main_sort()
{
	Vector<int>* v = new Vector<int>();
	srand((unsigned)time(nullptr));
	for (int i = 0; i < 100000; i++)
	{
		int random = rand() % END_INT + START_INT;
		v->push_back(random);
	}
#ifdef QUICK_SORT
	std::cout << "========== QUICK SORT ==========\n";
	QuickSort(*v);
	std::cout << std::endl;
#endif
#ifdef MERGE_SORT
	std::cout << "========== MERGE SORT ==========\n";
	MergeSort(*v);
	std::cout << std::endl;
#endif
#ifdef SELECTION_SORT
	std::cout << "========== SELECTION SORT ==========\n";
	SelectionSort(*v);
	std::cout << std::endl;
#endif
#ifdef INSERTION_SORT
	std::cout << "========== INSERTION SORT ==========\n";
	InsertionSort(*v);
	std::cout << std::endl;
#endif
#ifdef SHELL_SORT
	std::cout << "========== SHELL SORT ==========\n";
	ShellSort(*v);
	std::cout << std::endl;
#endif
#ifdef BUBBLE_SORT
	std::cout << "========== BUBBLE SORT ==========\n";
	BubbleSort(*v);
	std::cout << std::endl;
#endif

	return 0;
}
