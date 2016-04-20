#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void bubblesort(vector<int>A, int n);
void insertionsort(vector<int>B, int b);
void swap(int*x, int *y);
void qsort(vector<int>A, int low, int high);
int partition(vector<int>A, int low, int high);
void shellsort(vector<int>A, int n);
void merge(vector<int>A, int low, int high, int mid);
void mergesort(vector<int>A, int low, int high);

int main()
{
	int number, max; string file; vector<int>numbers;
	ifstream in;
	//cout << "File to read:  " << endl;
	//cin >> file;
	in.open("new 1.txt");
	while (in.is_open() == false)
	{
		cout << "Not found, try again:  ";
		cin >> file;
		in.open(file);
	}
	while (in >> number)
		numbers.push_back(number);
	max = numbers.size();

	bubblesort(numbers, max);
	cout << "\n";
	insertionsort(numbers, max);
	cout << "\n";
	//qsort(numbers, 0, max-1); NOT WORKING

	shellsort(numbers, max);

	//mergesort(numbers, 0, max - 1); NOT WORKING
	
    return 0;
}

void bubblesort(vector<int>A, int n)
{
	int i, j, temp, compCount, exCount;
	compCount = exCount = 0;
	for (i = 1; i<n; i++)
	{
		for (j = 0; j<n - 1; j++)
		{
			if (A[j]>A[j + 1])
			{
				temp = A[j];
				A[j] = A[j + 1];
				A[j + 1] = temp;
				exCount++;
			}
			compCount++;
		}
	}
	cout << "Sorted (bubble):  \n";
	for (int q = 0; q < A.size(); ++q)
		cout << A[q] << ' ';
	cout << "\nExchange count:  " << exCount << "\nComparison count:  " << compCount << endl;
}

void insertionsort(vector<int>B, int b)
{
	int i, j, element, compCount, exCount;
	compCount = exCount = 0;
	for (i = 1; i < b; i++)
	{
		element = B[i];
		j = i;
		while ((j > 0) && (B[j - 1] > element))
		{
			B[j] = B[j - 1];
			j = j - 1;
			exCount++;
		}
		B[j] = element;
		compCount++;
	}
	cout << "Sorted (insertion):  \n";
	for (int q = 0; q < B.size(); ++q)
		cout << B[q] << ' ';
	cout << "\nExchange count:  " << exCount << "\nComparison count:  " << compCount << endl;
}

void swap(int*x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int partition(vector<int>A, int low, int high)
{
	int pivot, i, j;
	i = 0;
	pivot = A[low];
	j = high + 1;
	do
	{
		i++;
		while (A[i] < pivot && low <= high)
		{
			do
			{
				j++;
			} while (pivot < A[j]);
			if (i < j)
				swap(A[i], A[j]);
		}
	} while (i < j);
	A[low] = A[j];
	A[j] = pivot;
	return j;
}

void qsort(vector<int>A, int low, int high)
{
	int k, compCount;
	string exCount = "?";
	compCount = 0;
	if (low < high)
	{
		k = partition(A, low, high);
		qsort(A, low, k - 1);
		compCount++;
		qsort(A, k + 1, high);
		compCount++;
	}
	cout << "Sorted (quick):  \n";
	for (int q = 0; q < A.size(); ++q)
		cout << A[q] << ' ';
	cout << "\nExchange count:  " << exCount << "\nComparison count:  " << compCount << endl;
}

void shellsort(vector<int>A, int n)
{
	int temp, gap, i, swapped, exCount, compCount;
	exCount = compCount = 0;
	gap = n / 2;
	do 
	{
		do
		{
			swapped = 0;
			for (i = 0; i < n - gap; i++)
			{
				if (A[i] > A[i + gap])
				{
					temp = A[i];
					A[i] = A[i + gap];
					A[i + gap] = temp;
					swapped = 1;
					exCount++;
				}
				compCount++;
			}
		} while (swapped == 1);
	} while ((gap = gap / 2) >= 1);
	cout << "Sorted (shell):  \n";
	for (int q = 0; q < A.size(); ++q)
		cout << A[q] << ' ';
	cout << "\nExchange count:  " << exCount << "\nComparison count:  " << compCount << endl;
}

void merge(vector<int>A, int low, int high, int mid)
{
	int i, j, k, exCount, compCount;
	vector<int>C;
	i = low;
	j = mid + 1;
	k = 0;
	exCount = compCount = 0;
	while ((i <= mid) && (j <= high))
	{
		if (A[i] < A[j])
			C[k] = A[i++];
		else
			C[k] = A[j++];
		k++;
	}
	while (i <= mid)
	{
		C[k++] = A[i++];
		compCount++;
	}
	while (j <= high)
	{
		C[k++] = A[j++];
		compCount++;
	}
	for (i = low, j = 0; i <= high; i++, j++)
		A[i] = C[j];
	cout << "Sorted (shell):  \n";
	for (int q = 0; q < A.size(); ++q)
		cout << A[q] << ' ';
	cout << "\nExchange count:  " << exCount << "\nComparison count:  " << compCount << endl;
}

void mergesort(vector<int>A, int low, int high)
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		mergesort(A, low, mid);
		mergesort(A, mid + 1, high);
		merge(A, low, high, mid);
	}
}