#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
void _MergeSort(int* a[],int* temp,int left,int right)
{
    //对数组进行划分
    if(left >= right)
        return;
    int mid = left + ((right - left) / 2);
    _MergeSort(a, temp, left, mid);
    _MergeSort(a, temp, mid+1, right);
    //开始进行归并
    int begin1 = left, begin2 = mid + 1;
    int end1 = mid, end2 = right;
    int index = left;
    while(begin1 <= end1 && begin2 <= end2)
    {
        if(a[begin1] < a[begin2])
        {
            temp[index++] = a[begin1++];
        }
        else
            temp[index++] = a[begin2++];
    }
    while(begin1 <= end1)
    {
        temp[index++] = a[begin1++];
    }
    while(begin2 <= end2)
    {
        temp[index++] = a[begin2++];
    }
    //将temp数组的内容赋值给a数组
    index = left;
    while(index <= right)
    {
        a[index] = temp[index];
        index++;
    }
}
void MergeSort(int* a[], int len)
{
    assert(a);
    int* temp = (int*)malloc(sizeof(int) * len);
    _MergeSort(a,temp,0,len-1);
    free(temp);//将申请的空间释放
}
void Print(int* a[], int len)
{
    for(int i = 0; i < len; ++i)
    {
        printf("%d  ",a[i]);
    }
    printf("\n");
}
int main()
{
    int* a[] = {9,6,7,5,8,3,5,4,8,1,0};
    int len = sizeof(a) / sizeof(a[0]);
    MergeSort(a,len);
    Print(a, len);
    return 0;
}


