#include<stdio.h>

void QuickSort(int* a[], int left, int right)
{
    if( left > right)
        return;
    int low = left;//数组的左边
    int high = right;
    int base = a[low];//基准数字
    while(low<high)
    {
        while(base<a[high] && low<high)
        {
            high--;
        }
        a[low] = a[high];
        while(base>a[low] && low<high)
            ++low;
        a[high] = a[low];
    }
    a[low] = base;
    QuickSort(a,0,low-1);
    QuickSort(a,high+1,right);
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
    int* a[] = {1,2,3,4,5,6,7,8,9};
    int len = sizeof(a)/sizeof(a[0]);
    QuickSort(a,0,len-1);
    Print(a,len);
    return 0;
}



