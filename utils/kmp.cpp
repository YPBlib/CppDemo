template <size_t M,size_t N>
int* kmp(char s[M], char p[N])
{
	// pre-process stage
	auto next = new int[N];
	next[0] = 0;
	for (int i = 1; i < N; ++i)
	{
		;
	}
}





void tsort(int* l, int* r)
{
	if (l >= r)return;
	int *cl = l, *cr = r;
	int* mid = l + (r - l) / 2;
	while (mid<r)
	{
		if (*r<*mid)
		{
			int tmp = *mid;
			*mid = *r;
			*r = tmp;
		}
		r--;
	}
	while (l<mid)
	{
		if (*mid<*l)
		{
			int tmp = *l;
			*l = *mid;
			*mid = tmp;
		}
		l++;
	}
	tsort(cl, mid);
	tsort(mid, cr);
}


#include <cstdio>
#include <algorithm>
int main()
{
	int x[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int y[10] = { 15168, 28139, 13714, 27801, 22208, 32524, 21653, 8353 ,28341, 25922 };
	int* l = x, *r = x + 9;
	printf("%d", *(l + (r - l) / 2));
	std::swap((*x), (*(x+9) ));
	printf("\n%d %d", x[0], x[9]);
	tsort(y, y + 9);
	return 0;
}

