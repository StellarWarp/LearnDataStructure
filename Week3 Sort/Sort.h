#pragma once
#include<iostream>
#include<memory>
#include<stack>
#include<queue>
using namespace std;

/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : 插入排序算法
 *  @param       : 数组指针 a, 数组长度 n
 */
template<class T>
void insertSort(T a[], int n)
{
	if (n <= 1 || !a) return;
	T* end = a + n;
	T* p = a + 1;
	for (p = a + 1; p != end; p++)
	{
		if (*p < *(p - 1))
		{
			T* p1 = a;
			while (*p1 <= *p)
			{
				p1++;
			}
			T temp = *p;
			//移动
			for (T* p2 = p; p2 != p1; p2--)
			{
				p2[0] = p2[-1];
			}
			*p1 = temp;
		}
	}
}


/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
template<class T>
void MergeArray(T a[], int begin, int end, T temp[])
{
	if (begin >= end)
		return;
	int len = end - begin, mid = (len >> 1) + begin;
	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	MergeArray(a, begin1, end1, temp);
	MergeArray(a, begin2, end2, temp);
	int k = begin;
	while (begin1 <= end1 && begin2 <= end2)
		temp[k++] = a[begin1] < a[begin2] ? a[begin1++] : a[begin2++];
	while (begin1 <= end1)
		temp[k++] = a[begin1++];
	while (begin2 <= end2)
		temp[k++] = a[begin2++];
	for (k = begin; k <= end; k++)
		a[k] = temp[k];
}


/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
template<class T>
void MergeSort(T a[], int begin, int end)
{
	//承载数组指针temp
	T* temp = new T[end - begin + 1]{};
	MergeArray(a, begin, end, temp);
	delete[] temp;
}

/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
template<class T>
int Partition(T a[], int begin, int end)
{
	//T pivot_value = a[begin];
	//while (begin < end)
	//{
	//	while (begin < end && pivot_value <= a[end])
	//	{
	//		end--;//后大
	//	}
	//	if (begin == end) break;
	//	swap(a[begin], a[end]);
	//	while (begin < end && pivot_value >= a[begin])
	//	{
	//		begin++;//前小
	//	}
	//	if (begin == end) break;
	//	swap(a[begin], a[end]);
	//}
	//return begin;

	//pivot 表示选中的中间值
	int p_index = end;
	int pivot = a[end];
	end--;
	while (1)
	{
		while (a[begin] < pivot)
		{
			begin++;
		};
		while (end > 0 && a[end] > pivot)
		{
			end--;
		}
		if (begin >= end)
		{
			break;
		}
		else
		{
			swap(a[begin], a[end]);
			begin++;
			end--;
		}
	}
	swap(a[begin], a[p_index]);
	return begin;
}

/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
template<class T>
void QuickSort_Recursion(T a[], int begin, int end)
{
	if (begin < end)
	{
		int pivot = Partition(a, begin, end);
		QuickSort_Recursion(a, begin, pivot - 1);
		QuickSort_Recursion(a, pivot + 1, end);
	}
}

/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针a，数组长度size
 */
template<class T>
void QuickSort(T a[], int size)
{
	vector<int> begin_index;
	vector<int> end_index;
	begin_index.push_back(0);
	end_index.push_back(size - 1);
	begin_index.resize(2);
	end_index.resize(2);
	int* p_b = &begin_index[1];
	int* p_e = &end_index[1];
	int stack_counter = 1;
	while (stack_counter)
	{
		int begin = *--p_b; //begin_index.pop();
		int end = *--p_e; //end_index.pop();
		stack_counter--;
		if (begin < end)
		{
			int pivot = Partition(a, begin, end);
			*p_b++ = begin;
			*p_e++ = pivot - 1;
			*p_b++ = pivot + 1;
			*p_e++ = end;
			stack_counter += 2;
			if (stack_counter >= begin_index.size())
			{
				begin_index.resize(stack_counter * 2);
				end_index.resize(stack_counter * 2);
				p_b = &begin_index[stack_counter];
				p_e = &end_index[stack_counter];
			}
		}
	}
}

/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size，数组最大值max
 */
void CountSort(int a[], int size, int max)
{
	if (!a) return;
	int* countArray = new int[max + 1]{};
	int* b = new int[size] {};
	int i, j, k;
	for (k = 0; k <= max; k++)
		countArray[k] = 0;
	for (i = 0; i < size; i++)
		countArray[a[i]]++;
	for (k = 1; k <= max; k++)
		countArray[k] += countArray[k - 1];
	for (j = size; j > 0; j--)
		b[--countArray[a[j - 1]]] = a[j - 1];
	for (i = 0; i < size; i++)
		a[i] = b[i];
	delete[] countArray;
	delete[] b;
}

template<class T>
class unit
{
	T* map_ptr;
	unsigned char* data_array;
	unsigned char* p;
	//int counted_char = 0;
	//int lenth = 0;
public:
	unit()
	{
		data_array = new unsigned char[sizeof(T)]{};
	}
	inline void set_data(T& data)
	{
		memcpy(data_array, &data, sizeof(T));
		//for (int i = sizeof(T) - 1; i >= 0; i--)
		//{
		//	if (data_array[i]) lenth = sizeof(T) - i;
		//}
		p = data_array + sizeof(T) - 1;
		map_ptr = &data;
	}
	inline unsigned char get()
	{
		return *p;
	}
	inline void next()
	{
		p--;
	}
	inline T& map_array()
	{
		return *map_ptr;
	}
	~unit()
	{
		delete[] data_array;
	}
};
/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
template<class T, bool _signed = true>
void RadixCountSort(T a[], int size)
{
	unit<T>* Array = new unit<T>[size];
	for (int i = 0; i < size; i++)
	{
		Array[i].set_data(a[i]);
	}
	unit<T>** ordering_list = new unit<T>*[size];
	for (int i = 0; i < size; i++)
	{
		ordering_list[i] = Array + i;
	}
	const int base_num = 1 << 8;
	unsigned int counter[base_num]{};
	unit<T>** temp_array = new unit<T>*[size];
	//基排序
	for (int t = 0; t < sizeof(T); t++)
	{
		memset(counter, 0, sizeof(counter));
		for (int i = 0; i < size; i++)
			counter[ordering_list[i]->get()]++;
		for (int i = 1; i < base_num; i++)
			counter[i] = counter[i - 1] + counter[i];
		unit<T>** p = ordering_list;
		//unit<T>* (*test)[10] = (unit<T>*(*)[10])ordering_list;
		for (int i = 0; i < size; i++)
		{
			unsigned char k = ordering_list[i]->get();
			temp_array[counter[k] - 1] = ordering_list[i];
			counter[k]--;
			ordering_list[i]->next();
		}
		memcpy(ordering_list, temp_array, sizeof(T*) * size);
	}
	T* b = new T[size];
	for (int i = 0; i < size; i++)
	{
		b[i] = ordering_list[i]->map_array();
	}
	if (_signed)
	{
		int filp_pos{};
		for (int i = 0; i < size; i++)
		{
			if (b[i] < 0)
			{
				filp_pos = i;
				break;
			}
		}
		memcpy(a, b + filp_pos, sizeof(T) * (size - filp_pos));//负数
		memcpy(a + (size - filp_pos) , b, sizeof(T) * filp_pos);//正数
	}
	else
		memcpy(a, b, sizeof(T) * size);
	delete[] b;
	delete[] Array;
	delete[] ordering_list;
}


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : 颜色排序
 *  @param       : 数组指针a（只含0，1，2元素），数组长度size
 */
void ColorSort(int a[], int size)
{
	int begin = 0;
	int end = size - 1;
	int p = begin + 1;
	while (p < end)
	{
		while (a[begin] == 0)
		{
			begin++;
		}
		while (a[end] == 2)
		{
			end--;
		}
		if (a[begin] == 2)
		{
			swap(a[begin], a[end--]);
		}
		if (a[end] == 0)
		{
			swap(a[begin++], a[end]);
		}
		if (begin > p)
		{
			p = begin + 1;
		}
		while (a[p] == 1 && p != end)
		{
			p++;
		}
		if (p == end) break;
		if (a[p] == 0) swap(a[begin], a[p]);
		else swap(a[end], a[p]);//a[p] == 2

	}
}

template<class T>
T OrderIn_interal(T a[], int size, int K)
{
	if (K == 0) return T{};
	int begin = 0;
	int end = size - 1;
	int pivot = Partition(a, begin, end);
	int len1 = pivot - begin;
	int len2 = end - pivot;
	if (len1 + 1 == -K || len2 + 1 == K)
	{
		return a[pivot];
	}
	if (K < 0 && len1 < -K)
	{
		K = size + K + 1;
	}
	else if (K > 0 && len2 < K)
	{
		K = -(size - K + 1);
	}
	if (K < 0)
		return OrderIn_interal(a, len1, K);
	else if (K > 0)
		return OrderIn_interal(a + pivot + 1, len2, K);
}
/**
 *  @name        : OrderIn
 *  @description : 在一个无序序列中找到第K大/小的数,K为正数时取大，K为负数时取小
 *  @param       : 数组指针a，数组长度size
 */
template<class T>
T OrderIn(T a[], int size, int K)
{
	T* b = new T[size];
	memcpy(b, a, size * sizeof(T));
	T r = OrderIn_interal(b, size, K);
	delete[]b;
	return r;
}