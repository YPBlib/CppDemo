#include <stdio.h>
#include <stdlib.h>
int partion(int a[], int l, int r);
void quicksort(int a[], int l, int r)
{
	if (l >= r)
		return;
	int pivot = partion(a,l,r);
	quicksort(a, l, pivot-1);
	quicksort(a, pivot + 1, r);

}

int partion(int a[], int l, int r)
{
	if (r-l<=7)
	{
		int i, j;
		for (i = l; i < r; ++i)
		{
			int e = a[i + 1];
			for (j = i; j >= l && a[j] > e; --j)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = e;
		}
		return (l + r) / 2;
	}
	else
	{
		int pi = a[(l + r) / 2], i, j, tmp;
		a[(l + r) / 2] = a[r];
		a[r] = pi;
		i = l - 1;
		for (j = l; j <= r - 1; ++j)
		{
			if (a[j] <= pi)
			{
				++i;
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}
		}
		tmp = a[i + 1];
		a[i + 1] = a[r];
		a[r] = tmp;
		return i + 1;
	}

}
