#include <stdio.h>
#include <stdlib.h>
#include "processDef.h"

/* HEAP SORT */
void maxHeapify(Pr *arr, int i, int size)
{
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int max;
	Pr t;

	if (l < size && arr[l].at > arr[i].at)
		max = l;
	else
		max = i;

	if (r < size && arr[r].at > arr[max].at)
		max = r;

	if (max != i)
	{
		t = arr[i];
		arr[i] = arr[max];
		arr[max] = t;
		maxHeapify(arr, max, size);
	}
}

void buildMaxHeap(Pr *arr, int size)
{
	int i;
	for (i = size / 2 - 1; i >= 0; i--)
		maxHeapify(arr, i, size);
}

Pr *sortProcesses(Pr *arr, int n)
{
	buildMaxHeap(arr, n);
	int i;
	Pr t;

	for (i = n - 1; i >= 1; i--)
	{
		t = arr[0];
		arr[0] = arr[i];
		arr[i] = t;
		n--;

		maxHeapify(arr, 0, n);
	}

	return arr;
}
