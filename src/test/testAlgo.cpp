#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5010;

int n, r;
int s[N][N];

int main_algo()
{
	scanf("%d%d", &n, &r);
	r = min(r, 5001);
	int x, y, w;
	int max_x = r, max_y = r;
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &x, &y, &w);
		s[x + 1][y + 1] += w;
		max_x = max(max_x, x + 1);
		max_y = max(max_y, y + 1);
	}

	for (int i = 1; i <= max_x; i++)
		for (int j = 1; j <= max_y; j++)
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + s[i][j];

	int ans = 0;
	for (int i = r; i <= max_x; i++)
	{
		for (int j = r; j <= max_y; j++)
		{
			ans = max(ans, s[i][j] - s[i - r][j] - s[i][j - r] + s[i - r][j - r]);
		}
	}

	printf("%d\n", ans);

	return 0;
}