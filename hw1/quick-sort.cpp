#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// works for arrays of any type
//

template <class Item>
int partition(Item A[], int left, int right)
{
  Item pivot = 0;
  int i = left;

  for (int j = left; j <= right; ++j)	//Include final element
    if (A[j] < pivot)
	swap(A[i++], A[j]);

  return i;
}

template <class Item>
void quick_sort(Item A[], int left, int right)
{
	if (left < right)
	{
	  int pindex = partition(A, left, right);
	  quick_sort(A, left, pindex-1);
	  quick_sort(A, pindex+1, right);
	}
}

int main(){
	int A[] = {1, -4, 5, 6, 7, -8, -1, 0, 4, -3};
	for(int i = 0; i < 10; i++)
		cout << A[i] << ' ';
	cout << endl;
	partition(A, 0, 9);
	for(int i = 0; i < 10; i++)
		cout << A[i] << ' ';
	cout << endl;
	return 0;
}
