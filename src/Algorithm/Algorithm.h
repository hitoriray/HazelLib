#include "../hazel.h"
//#include <ctime>
#include <random> // 用于生成随机数

namespace Hazel
{
	// 获取范围[min, max)内随机整数
	int get_random_integer(int min, int max);
	// 获取范围[min, max)内随机浮点数
	double get_random_double(double min, double max);

	// 判断数组是否是排序的
	template <typename T, typename Comp = std::less<T>>
	bool is_sorted(const Vector<T>& v)
	{
		int n = v.size();
		for (int i = 1; i < n; i++)
			if (cmp(v[i], v[i - 1]))
				return false;
	}

	template <typename T, typename Comp = std::less<T>>
	bool cmp(const T& a, const T& b)
	{
		Comp c;
		return c(a, b);
	}

	template <typename T>
	void swap(T& a, T& b)
	{
		T t = a;
		a = b;
		b = t;
	}

	template <typename T>
	void shuffle(Vector<T>& q)
	{
		//srand((unsigned)time(nullptr)); // 初始化随机数种子
		//int n = q.size();
		//for (int i = n - 1; i >= 0; i--)
		//{
		//	int random_index = rand() % n; // random_index: [0, n)
		//	T tmp = q[random_index];
		//	q[random_index] = q[i];
		//	q[i] = tmp;
		//}

		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(q.begin(), q.end(), gen);
	}

	

	// !排序算法
	/* 
		1. 排序算法怎么选择？
		数据量规模较小，考虑直接插入或直接选择。当元素分布有序时直接插入将大大减少比较和移动记录的次数，如果不要求稳定性，可以使用直接选择，效率略高于直接插入。

		数据量规模中等，选择希尔排序。

		数据量规模较大，考虑堆排序（元素分布接近正序或逆序）、快速排序（元素分布随机）和归并排序（稳定性）。

		一般不使用冒泡。
	*/

	// !1. 快速排序 ———— 分治（时间复杂度：O(n) = nlogn）
	// 是对冒泡排序的一种改进，不稳定，平均/最好时间复杂度 O(nlogn)，元素基本有序时最坏时间复杂度 O(n²)，空间复杂度 O(logn)
	// 最坏情况是每次所选中间数是当前序列中的最大或最小元素，这使每次划分所得子表其中一个为空表 ，这样长度为 n 的数据表需要 n 趟划分，整个排序时间复杂度 O(n²)
	template <typename T, typename Comp = std::less<T>>
	void quick_sort(Vector<T>& q)
	{
		quick_sort(q, 0, q.size() - 1);
	}

	template <typename T, typename Comp = std::less<T>>
	void quick_sort(Vector<T>& q, int l, int r)
	{
		if (l >= r) return;
		// 1. 确定分界点：q[x] 如：q[l] / q[(l+r)/2] / q[r] / q[random_index]
		int i = l - 1, j = r + 1;
		T x = q[l]; // 选取最左侧数字为基准数字
		// 2. 根据q[x]的值将数组分成两部分（保证左部分的值都<=x，右部分的值都>=x）【难点】
		while (i < j)
		{
			do i++; while (cmp(q[i], x) /* q[i] < x */);
			do j--; while (cmp(x, q[j]) /* x < q[j] */);
			if (i < j) swap(q[i], q[j]);
		}
		// 3. 递归处理左右两部分
		quick_sort(q, l, j);
		quick_sort(q, j + 1, r);
	}

	// !2. 归并排序 ———— 分治（时间复杂度：O(n) = nlogn）
	// 归并排序基于归并操作，是一种稳定的排序算法，任何情况时间复杂度都为 O(nlogn)，空间复杂度为 O(n)
	// 适用场景：数据量大且对稳定性有要求的情况。
	template <typename T, typename Comp = std::less<T>>
	void merge_sort(Vector<T>& q)
	{
		Vector<T> tmp(q.size()); // 需要一个额外空间存放归并后的数组
		merge_sort(q, 0, q.size() - 1, tmp);
	}

	template <typename T, typename Comp = std::less<T>>
	void merge_sort(Vector<T>& q, int l, int r, Vector<T>& tmp)
	{
		if (l >= r) return;
		// 1. 确定分界点mid
		int mid = l + r >> 1;
		// 2. 递归排序左右两个部分
		merge_sort(q, l, mid, tmp);
		merge_sort(q, mid + 1, r, tmp);
		// 3. 归并 ———— 合二为一【难点】
		int k = 0, i = l, j = mid + 1;
		while (i <= mid && j <= r)
			if (q[i] <= q[j]) tmp[k++] = q[i++];
			else tmp[k++] = q[j++];
		while (i <= mid) tmp[k++] = q[i++];
		while (j <= r) tmp[k++] = q[j++];

		for (i = l, j = 0; i <= r; i++, j++) q[i] = tmp[j];
	}

	// !3. 冒泡排序（时间复杂度：O(n) = n^2）
	// 稳定，平均/最坏时间复杂度 O(n²)，元素基本有序时最好时间复杂度 O(n)，空间复杂度 O(1)。
	// 当序列已经有序时仍会进行不必要的比较，可以设置一个标志记录是否有元素交换，如果没有直接结束比较。
	template <typename T, typename Comp = std::less<T>>
	void bubble_sort(Vector<T>& q)
	{
		int n = q.size();
		bool swaped = false; // 标志是否有元素交换
		for (int i = 0; i < n - 1; i++)
		{
			swaped = true;
			for (int j = 0; j < n - i - 1; j++)
			{
				if (cmp(q[j + 1], q[j]))
				{
					swap(q[j], q[j + 1]);
					swaped = false;
				}
			}
			if (swaped) break; // 如果没有直接结束比较
		}
	}

	// !4. 选择排序（时间复杂度：O(n) = n^2）
	// 不稳定，时间复杂度 O(n²)，空间复杂度 O(1)。
	template <typename T, typename Comp = std::less<T>>
	void selection_sort(Vector<T>& q)
	{
		int n = q.size();
		for (int i = 0; i < n - 1; i++)
		{
			int select = i;
			for (int j = i + 1; j < n; j++)
				if (cmp(q[j], q[select])) 
					select = j;
			swap(q[i], q[select]);
		}
	}

	// !5. 插入排序（时间复杂度：O(n) = n^2）
	// 稳定，平均/最差时间复杂度 O(n²)，元素基本有序时最好时间复杂度 O(n)，空间复杂度 O(1)
	template <typename T, typename Comp = std::less<T>>
	void insertion_sort(Vector<T>& q)
	{
		int n = q.size();
		for (int i = 1; i < n; i++)
			for (int j = i; j >= 0 && cmp(q[j], q[j - 1]); j--)
				swap(q[j], q[j - 1]);
	}

	// !6. 希尔排序（时间复杂度：O(n) = n^1.3）
	// 又称缩小增量排序，是对直接插入排序的改进
	// 不稳定，平均时间复杂度 O(n^1.3)，最差时间复杂度 O(n²)，最好时间复杂度 O(n)，空间复杂度 O(1)。
	template <typename T, typename Comp = std::less<T>>
	void shell_sort(Vector<T>& q)
	{
		int n = q.size();
		int h = 1;
		while (h < n / 3) h = 3 * h + 1; // 1, 4, 13, 40, 121, 364, 1093, ...
		while (h >= 1)
		{
			// 将数组变为h有序
			for (int i = h; i < n; i++)
				for (int j = i; j >= h && cmp(q[j], q[j - h]); j -= h)
					swap(q[j], q[j - h]);
			h /= 3;
		}
	}

	// 7. 优先队列（堆）排序




	// !二分
	template <typename T, typename Filter = std::less<T>>
	bool check(const T& mid, const T& x)
	{
		Filter ft;
#ifndef FIND_RIGHT
		return !ft(mid, x); // 如果mid元素的性质与x元素的性质不同
#else
		return !ft(x, mid);
#endif // FIND_RIGHT

	}

	template <typename T, typename Filter = std::less<T>>
	int binary_search(Vector<T>& q, int target, int l = -1, int r = -1)
	{
		// !注意：二分的本质并不是单调！
		// !二分的本质是：一个数组：左部分满足性质1，右部分满足性质2。此时就可以使用二分了
		// 此时，默认二分查找整个数组
		if (l == -1) l = 0, r = q.size() - 1;
		// 1. 找到中间值
		// 2. 判断mid是否满足性质1
		Filter ft;
		// !二分模板
		while (l < r)
		{
#ifndef FIND_RIGHT // 这种情况是寻找第一个满足性质的元素下标
			int mid = l + r >> 1;
			// 如果mid元素的性质与x元素的性质不同
			// 此时去mid左边寻找满足性质的元素
			if (check(q[mid], target)) r = mid;
			// 否则就去mid右边寻找满足性质的元素
			else l = mid + 1;
#else // 这种情况是寻找最后一个满足满足性质的元素下标
			int mid = l + r + 1 >> 1; // 必须+1，不然在 l == r-1 时会陷入死循环
			// 如果mid元素的性质与x元素的性质不同
			// 此时去mid右边寻找满足性质的元素
			if (check(q[mid], target)) l = mid;
			// 否则就去mid左边寻找满足性质的元素
			else r = mid - 1;
#endif // FIND_RIGHT
		}
		return l;
	}

	// !浮点数二分 ———— 不需要处理边界
	// ag.
	double Sqrt(const double& x);



}