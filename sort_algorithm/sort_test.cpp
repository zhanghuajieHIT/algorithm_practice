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
    int left = 2*index+1;
    int right = 2*index+2;
    if (num < 2 || left>num-1)
        return;
    int index_new = 0;
    if (right>num-1)
        index_new = left;
    else
        index_new = arr[right]>arr[left]?right:left;
    if (arr[index]<arr[index_new])
    {
        int tmp = arr[index_new];
        arr[index_new]=arr[index];
        arr[index] = tmp;
        heapAdjust(arr, index_new, num);
    }
    return;
}

void buildHeap(int arr[], int num)
{
    if (num < 2)
        return;
    int start = (num -2)/2;
    for (int i = start; i >= 0; --i)
    {
        heapAdjust(arr, i, num);
    }
}

void heapSort(int arr[], int num)
{
    if(num < 2)
        return;
    buildHeap(arr, num);
    int tmp = arr[num-1];
    arr[num-1] = arr[0];
    arr[0] = tmp;
    while(num >2)
    {
        heapAdjust(arr, 0, num-1);
        int tmp = arr[num-2];
        arr[num-2] = arr[0];
        arr[0] = tmp;
        num--;
    }
    return;
}

//count sort
void countSort(int arr[], int minNum, int maxNum)
{
    int length = maxNum - minNum + 1;
    int tmp[length] = {0};
    for (int i = 0; i< 10; ++i)
    {
        tmp[arr[i]-minNum]++;
    }

    for (int i =0 ,j=0; i < length; ++i)
    {
        while(tmp[i]>0)
        {
            arr[j]=i;
            ++j;
            tmp[i]--;
        }
    }
}

//radix sort
int maxbit(int arr[], int num)
{
    int bitnum = 1, p = 10;
    for (int i=0; i < num; ++i)
    {
        while(arr[i]>=p)
        {
            bitnum++;
            p *= 10;
        }
    }
    return bitnum;
}

void radixSort(int arr[], int num)
{
    int tmp[num];
    int bitnum = maxbit(arr, num);
    int radix = 1;
    for (int i =0; i <bitnum;++i)
    {
        int count[10]={0};
        for (int j = 0; j < num; ++j)
            tmp[j] = arr[j];
        for (int j = 0; j < num;++j)
            count[tmp[j]/radix%10]++;
        for (int j =1;j<10;++j)
            count[j] = count[j-1]+count[j];
        for (int j=num-1;j>=0;--j)
        {
            count[tmp[j]/radix%10]--;
            arr[count[tmp[j]/radix%10]]=tmp[j];
        }
        radix=radix*10;
    }
}

//bucket sort
#define BUCKETNUM 6
#define INTERNAL 10
typedef struct listNode
{
    int val;
    listNode *next;
    listNode(int x){val = x; next = NULL;}
}listNode;

void printList(listNode *head)
{
    while(head != NULL)
    {
        cout << head->val<<endl;
        head = head->next;
    }
}

int getBucketIndex(int num)
{
    return num/INTERNAL;
}

void insertNode(listNode *bucket[], int index, listNode *newNode)
{
    listNode *head = bucket[index];
    if (head == NULL)
    {
        head = newNode;
        bucket[index] = head;
        return;
    }
    while(head->next)
    {
        head = head->next;
    }
    head->next = newNode;
}

void list2arr(listNode *listVar, int arr[])
{
    static int NUM =0;
    while(listVar)
    {
        arr[NUM] = listVar->val;
        NUM++;
        listVar = listVar->next;
    }
}

void sortList(listNode *listVar)
{
    listNode *head= listVar;
    int num = 0;
    while(head)
    {
        head = head->next;
        num++;
    }

    int arr[num]= {0};
    int i = 0;
    head = listVar;
    while(head)
    {
        arr[i] = head->val;
        head = head->next;
        i++;
    }
    heapSort(arr, num);
    head = listVar;
    for(int i =0; i<num;++i)
    {
        head->val = arr[i];
        head = head->next;
    }
}


void bucketSort(int arr[], int num)
{
    listNode *bucket[BUCKETNUM]={NULL};
    int index;
    for (int i =0;i<num;++i)
    {
        index = getBucketIndex(arr[i]);
        listNode *tmp=new listNode(arr[i]);
        insertNode(bucket, index, tmp);
    }

    for (int i = 0; i < BUCKETNUM; ++i)
    {
        if (bucket[i] != NULL)
        {
            sortList(bucket[i]);
            list2arr(bucket[i], arr);
        }
    }

}

int main()
{
    int arr1[LEN] = {3, 10, 45, 6, 4, 9, 0, 56, 8 ,10};
    bucketSort(arr1, 10);
    printArr(arr1);
    return 0;
}

