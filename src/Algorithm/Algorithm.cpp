#include "Algorithm.h"

double Hazel::Sqrt(const double& x)
{
	double l = 0.0, r = std::max(1.0, x); // 一定不能小于1，不然就无法处理 x < 1 的情况了

	// 如果题目要求保留k位小数，则 r - l > 1e-(k+2)
	// ag. 保留4位小数，则 r - l > 1e-6
	// ag. 保留5位小数，则 r - l > 1e-7

	//for(int i = 0; i < 100; i++) // 另一种方法，循环100次
	while (r - l > 1e-8) // 第一种写法
	{
		double mid = (l + r) / 2;
		if (mid * mid >= x) r = mid;
		else l = mid;
	}
	return l;
}

int Hazel::get_random_integer(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(gen);
}

double Hazel::get_random_double(double min, double max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(gen);
}
