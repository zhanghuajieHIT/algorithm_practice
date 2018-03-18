//sort algorithm
#include <iostream>
using namespace std;

#define LEN  10

void printArr(int arr[])
{
    for (int i = 0; i < LEN; ++i)
        cout << i<<":"<<arr[i] <<endl;
}

//bubble sort
//这种优化的冒泡算法，在最优的情况下，时间复杂度为O(n)
void bubbleSort(int arr[])
{
    bool didSwap;
    for (int i = 0; i < LEN; ++i)
    {
        didSwap = false;
        for (int j = 1; j < LEN - i; ++j)
        {
            if (arr[j - 1] > arr[j])
            {
                int tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
                didSwap = true;
            }
        }
        if (!didSwap)
            return;
    }
}

//select sort
void selectSort(int arr[])
{
    for (int i = 0; i < LEN; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < LEN; ++j)
        {
            if (arr[minIndex] > arr[j])
            {
                minIndex = j;
            }
        }
        int tmp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = tmp;
    }

}

void selectSort2(int arr[])
{
    for (int i = 0; i < LEN; ++i)
    {
        for (int j = i + 1; j < LEN; ++j)
        {
            if (arr[i] > arr[j])
            {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }

}

//insert sort
void insertSort(int arr[])
{
    for (int i = 1; i < LEN; ++i)
    {
        int tmp = arr[i];
        for (int j = i - 1; j >= 0; --j)
        {
            if (tmp < arr[j])
            {
                arr[j + 1] = arr[j];
                arr[j] = tmp;
                continue;
            }
        }
    }
}

//shell sort
void shellSort(int arr[])
{
    int gap = 5;
    while (gap > 0)
    {
        for (int k = 0; k < gap; ++k)
        {
            for (int i = k + gap; i < LEN; i += gap)
            {
                int tmp = arr[i];
                for (int j = i - gap; j >= 0; j -= gap)
                {
                    if (arr[j + gap] < arr[j])
                    {
                        arr[j + gap] = arr[j];
                        arr[j] = tmp;
                    }
                }
            }
        }
        gap--;
    }
}

//merge sort
void mergeArr(int arr1[], int num1, int arr2[], int num2)
{
    int result[num1 + num2];
    int i = 0, j = 0, k = 0;
    while(i < num1 && j < num2)
    {
        if (arr1[i] > arr2[j])
        {
            result[k] = arr2[j];
            k++;
            j++;
        }
        else
        {
            result[k] = arr1[i];
            k++;
            i++;
        }
    }
    for (; k < num1 + num2; ++k)
    {
        result[k] = i < num1 ? arr1[k - num2] : arr2[k - num1];
    }
    for (int ii = 0; ii < num1 + num2; ++ii)
    {
        arr1[ii] = result[ii];
    }
}

void mergeSort(int arr[], int eleNum)
{
    if (eleNum < 2)
        return;
    int midNum = eleNum/2 - 1;
    int *arr1 = arr;
    int *arr2 = arr + midNum + 1;
    mergeSort(arr1, midNum + 1);
    mergeSort(arr2, eleNum - 1 -midNum);
    mergeArr(arr1, midNum + 1, arr2, eleNum - 1 -midNum);
}

//quick sort
void quickSort(int arr[], int num)
{
    int tmp = arr[0];
    int left = 0;
    int right = num - 1;
    if(left < right)
    {
        while(left < right)
        {
            if (arr[right] < tmp)
            {
                arr[left] = arr[right];
                left++;
                while(left < right)
                {
                    if (arr[left] > tmp)
                    {
                        arr[right] = arr[left];
                        right--;
                        break;
                    }
                    left++;
                }
            }
            right--;
        }
        arr[left] = tmp;
        quickSort(arr, left + 1);
        quickSort(arr + left + 1, num - left -1);
    }
}

//heap sort
void heapAdjust(int arr[], int index, int num)
{
    if (2*index+1 > LEN-2)
    {
        return;
    }
    if (2*index+2 > LEN-2)
    {
        if (arr[index] < arr[2*index+1])
        {
            int tmp = arr[index];
            arr[index] = arr[2*index+1];
            arr[2*index+1] = tmp;
        }
        return;
    }
    int index_new = arr[2*index+2] > arr[2*index+1] ? 2*index+2 : 2*index+1;
    if (arr[index] < arr[index_new])
    {
        int tmp = arr[index_new];
        arr[index_new] = arr[index];
        arr[index] = tmp;
        heapAdjust(&arr[index_new], index_new, num-1);
    }
}

void heapSort(int arr[], int num)
{
    if (num < 2)
        return;
    int start = (num - 2)/2;
    cout << "start:"<<arr[start]<<endl;
    for (int i = start; i >= 0; --i)
    {
        int index = 0;
        if (2*i+2 > num -2)
            index = 2*i+1;
        else
            index = arr[2*i+2] > arr[2*i+1] ? 2*i+2 : 2*i+1;
        if (arr[i] < arr[index])
        {
            int tmp = arr[index];
            arr[index] = arr[i];
            arr[i] = tmp;
            heapAdjust(&arr[index], index, num-1);
        }
    }
    printArr(arr);
    cout<<endl;
    int tmp = arr[num-1];
    arr[num-1] = arr[0];
    arr[0] = tmp;
    heapSort(arr, num - 1);
}


int main()
{
    int arr1[LEN] = {3, 10, 45, 6, 4, -9, 0, -56, 8 ,10};
    heapSort(arr1, 10);
    printArr(arr1);
    return 0;
}

