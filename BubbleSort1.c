//写冒泡排序
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>//用bool类型时要用的头文件
void BubbleSort(int** a, int n)
{
    int i;
    int j;
    int temp;
    bool change;
    for(i=n-1; change == true, i>1; --i)
    {
        change = false;//false要用小写，大写的话报错
        for(j=0; j<i; ++j)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                change = true;
            }
        }
    }
}
void Veist(int** a, int n)
{
    int i;
    for(i=0; i<n; ++i)
    {
        printf("%d  ",a[i]);
    }
}
int main()
{
    int* a[]={2,5,3,4,8,14,17,0,1};//64位操作系统中一个指针占用8个字节
    int len = sizeof(a)/sizeof(a[0]);
    printf("%d\n",len);
    BubbleSort(a,len);
    Veist(a,len);
    return 0;
}
