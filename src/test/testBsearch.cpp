#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "../Vector/Vector.h"
#include "../Algorithm.h"

using namespace Hazel;

int mainbs()
{
    Vector<int> q = { 1, 2, 2, 3, 3, 4, 5 };

    int x;
    while (scanf("%d", &x))
    {
        int l = 0, r = q.size() - 1;
        // !寻找第一个满足>=x的元素下标
        while (l < r)
        {
            int mid = l + r >> 1;
            if (q[mid] >= x) r = mid;
            else l = mid + 1;
        }

        if (q[l] != x) std::cout << "-1 -1" << std::endl;
        else
        {
            std::cout << l << " ";
            l = 0, r = q.size() - 1;
			// !寻找最后一个满足>=x的元素下标
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (q[mid] <= x) l = mid;
                else r = mid - 1;
            }
            std::cout << l << std::endl;
        }
    }

    return 0;
}
