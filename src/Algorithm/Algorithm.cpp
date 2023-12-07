#include "Algorithm.h"

double Hazel::Sqrt(const double& x)
{
	double l = 0.0, r = std::max(1.0, x); // һ������С��1����Ȼ���޷����� x < 1 �������

	// �����ĿҪ����kλС������ r - l > 1e-(k+2)
	// ag. ����4λС������ r - l > 1e-6
	// ag. ����5λС������ r - l > 1e-7

	//for(int i = 0; i < 100; i++) // ��һ�ַ�����ѭ��100��
	while (r - l > 1e-8) // ��һ��д��
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
