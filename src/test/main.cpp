#include <iostream>
#include "../Timer/Timer.h"

using namespace std;

const int N = 1000010;

int a[N];

void reverse_1(int a[], int n)
{
	for (int i = 0, j = n - 1; i < j; i++, j--)
	{
		int t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
}

void reverse_2(int a[], int n)
{
	int* t = new int[n];
	for (int i = 0; i < n; i++) t[i] = a[n - i - 1];
	for (int i = 0; i < n; i++) a[i] = t[i];
	delete[] t;
}

void test_reverse_1(int a[], int n, int cnt)
{
	Timer t;
	for (int i = 0; i < cnt; i++)
		reverse_1(a, n);
}
void test_reverse_2(int a[], int n, int cnt)
{
	Timer t;
	for (int i = 0; i < cnt; i++)
		reverse_2(a, n);
}

int main()
{
	int n, cnt;
	cin >> n >> cnt;
	for (int i = 0; i < n; i++) a[i] = i + 1;

	cout << "reverse1执行" << cnt << "次所需时间：";
	test_reverse_1(a, n, cnt);
	cout << endl;

	cout << "reverse2执行" << cnt << "次所需时间：";
	test_reverse_2(a, n, cnt);
	cout << endl;

	return 0;
}