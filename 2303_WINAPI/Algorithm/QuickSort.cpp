#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Quick Sort
// 불안정 정렬 (같은 값의 원소가 있을 때, 위치를 보장하지 못한다.)
// nlogn ~ n^2
// Partition

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int lowIndex = left + 1;
	int highIndex = right;

	while (true)
	{
		if(lowIndex > highIndex)
			break;

		while(lowIndex <= right && pivot >= v[lowIndex])
			lowIndex++;

		while(highIndex >= left + 1 && pivot <= v[highIndex])
			highIndex--;

		if(lowIndex < highIndex)
			std::swap(v[lowIndex], v[highIndex]);
	}

	std::swap(v[highIndex], v[left]);

	return highIndex;
}

void QuickSort(vector<int>& v, int left, int right)
{
	if(left > right)
		return;

	int pivotIndex = Partition(v, left, right);

	cout << left << " ~ " << pivotIndex - 1 << endl;
	QuickSort(v, left, pivotIndex);
	cout << pivotIndex << " ~ " << right << endl;
	QuickSort(v, pivotIndex + 1, right);
}

int main()
{
	vector<int> v = {55, 30, 15, 100, 1, 5, 70, 30};

	QuickSort(v, 0, 6);

	return 0;
}