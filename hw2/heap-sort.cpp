#include <iostream>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;

template <class Item>
void fix_heap(Item H[], size_t i, size_t n)
{
	while ((2*i) + 1 <= n )
	{
		size_t largest = i;
		size_t left = 2*i+1;
		size_t right = left + 1;

		largest = (H[i] >= H[left]) ? i : left;
		if (right <= n && H[right] > H[largest])
			largest = right;
		if (largest == i)
			return;
		swap(H[i], H[largest]);
		i = largest;
	}
}

template <class Item>
void make_heap(Item H[], size_t n)
{
	for (size_t i = ((n-1)/2); i >= 0; --i)
		fix_heap(H, i, n);
}

template <class Item>
void heap_sort(Item H[], size_t n)
{
	make_heap(H, n-1);
	for (size_t i = n-1; i > 0; --i)
	{
		swap(H[0], H[i]);
		fix_heap(H, 0, i);
	}
}


int main()
{
	srand(time(0));

	size_t n;
	cout << "Enter n: ";
	cin >> n;

	int H[n];

	for (size_t i = 0; i < n; ++i)
		H[i] = i;

	for (size_t i = n-1; i > 0; --i)
	{
		size_t j = (rand() % n);
		swap(H[i], H[j]);
	}

	for (size_t i = 0; i < n; ++i)
		cout << H[i] << " ";
	cout << endl;

	heap_sort(H, n);

	for (size_t i = 0; i < n; ++i)
	{
		cout << H[i] << " ";
		if (H[i] != i)
		{
			cout << "Error!";
			exit(1);
		}
	}
	cout << "Sorted!" << endl;
}

