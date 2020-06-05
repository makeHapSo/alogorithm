#include <iostream>

//起泡排序
void Bubble(int* arr, int len)
{
	for (int i = 0; i < len - 1; ++i)
	{
		bool flage = false;
		for (int j = 0; j < len - 1 - i; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				flage = true;
			}
		}
		if (flage == false) break;
	}
}

//快速排序
void Quick_Sort(int* arr, int low, int hi)
{
	if (low > hi) return;
	int temp = arr[low];
	int i = low;
	int j = hi;
	while (i != j)
	{
		while (i < j && arr[j] >= temp) j--;
		while (i < j && arr[i] <= temp) i++;
		if (i < j)
		{
			int tempa = arr[i];
			arr[i] = arr[j];
			arr[j] = tempa;
		}
	}
	arr[low] = arr[i];
	arr[i] = temp;
	Quick_Sort(arr, low, i - 1);
	Quick_Sort(arr, i + 1, hi);
}

//直接插入排序
void InsertSort(int* arr, int len)
{
	for (int i = 1; i < len; ++i)
	{
		int temp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > temp)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = temp;
	}
}

//希尔排序
void ShellSort1(int* arr, int len)
{
	for (int gap = len / 2; gap >= 1; gap /= 2)
	{
		for (int i = gap; i < len; ++i)
		{
			int temp = arr[i];
			int j = i - gap;
			while (j >= 0 && arr[j] > temp)
			{
				arr[j + gap] = arr[j];
				j -= gap;
			}
			arr[j + gap] = temp;
		}
	}
}

//直接选择排序
void SelectSort(int* arr, int len)
{
	for (int i = 0; i < len - 1; ++i)
	{
		for (int j = i + 1; j < len; ++j)
		{
			if (arr[i] > arr[j])
			{
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

//构建大顶堆
void HeapBuild(int* arr, int root, int len)
{
	int lchild = root * 2 + 1;
	int rchild = root * 2 + 2;
	int maxindex = lchild;
	if (lchild < len)
	{
		if (rchild < len)
		{
			if (arr[lchild] < arr[rchild])
			{
				maxindex = rchild;
			}
		}
		if (arr[maxindex] > arr[root])
		{
			std::swap(arr[maxindex], arr[root]);
			HeapBuild(arr, maxindex, len);
		}
	}
}

//堆排序
void HeapSort(int* arr, int len)
{
	for (int i = len / 2; i >= 0; --i)
	{
		HeapBuild(arr, i, len);
	}
	for (int j = len - 1; j >= 0; j--)
	{
		std::swap(arr[0], arr[j]);
		HeapBuild(arr, 0, j);
	}
}

//归并
void Merge(int* arr, int L, int M, int R) 
{
	int left_size = M - L;
	int right_size = R - M + 1;
	int* L_arr = new int[left_size];
	int* R_arr = new int[right_size];

	for (int i = L; i < M; i++) L_arr[i - L] = arr[i];
	for (int i = M; i <= R; i++) R_arr[i - M] = arr[i];

	int i = 0, j = 0, k = L;
	while (i < left_size && j < right_size)
	{
		if (L_arr[i] < R_arr[j])
			arr[k++] = L_arr[i++];
		else
			arr[k++] = R_arr[j++];
	}

	while (i < left_size)
		arr[k++] = L_arr[i++];
	while (j < right_size)
		arr[k++] = R_arr[j++];
	delete[] L_arr;
	delete[] R_arr;
}

//归并排序
void MergeSort(int* arr, int L, int R) 
{
	if (L == R) return;
	int M = (L + R) / 2;
	MergeSort(arr, L, M);
	MergeSort(arr, M + 1, R);
	Merge(arr, L, M + 1, R);
}

//辅助函数，求数据的最大位数
int Maxbit(int* arr, int n) 
{
	int maxData = arr[0];              ///< 最大数
	/// 先求出最大数，再求其位数，这样有原先依次每个数判断其位数，稍微优化点。
	for (int i = 1; i < n; ++i)
	{
		if (maxData < arr[i])
			maxData = arr[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		//p *= 10; // Maybe overflow
		maxData /= 10;
		++d;
	}
	return d;
	/*    int d = 1; //保存最大的位数
		int p = 10;
		for(int i = 0; i < n; ++i)
		{
			while(data[i] >= p)
			{
				p *= 10;
				++d;
			}
		}
		return d;*/
}

//基数排序
void Radixsort(int* arr, int n) 
{
	int d = Maxbit(arr, n);
	int* tmp = new int[n];
	int* count = new int[10]; //计数器
	int i, j, k;
	int radix = 1;
	for (i = 1; i <= d; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (j = 0; j < n; j++)
		{
			k = (arr[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (arr[j] / radix) % 10;
			tmp[count[k] - 1] = arr[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //将临时数组的内容复制到data中
			arr[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}

int main()
{
	int arr[11] = { 21,13,14,17,16,22,37,17,43,29,11 };
	//Bubble(arr, 11);
	//Quick_Sort(arr, 0, 10);
	//InsertSort(arr, 11);
	//ShellSort1(arr,11);
	//SelectSort(arr,11);
	//HeapSort(arr, 11);
	//MergeSort(arr, 0, 10);
	//Radixsort(arr, 11);
	for (int i = 0; i < 11; ++i)
	{

		std::cout << arr[i] << std::endl;
	}
	return 0;
}
