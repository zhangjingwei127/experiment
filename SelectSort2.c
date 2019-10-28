#include<stdio.h>

void SelectSort(int* a[], int n)
{
    int i,j,k,temp;
    for(i = 0; i < n; ++i)
    {
        j = i;
        for(k = i+1; k < n; ++k)
        {
            if(a[j] > a[k])
                j = k;
        }
        if(j != i)
        {
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
    }
}
void Print(int* a[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("%d  ",a[i]);
    }
    printf("\n");
}
int main()
{
    int* a[] = {1,23,45,6,70,5,2,5,0};
    int len = sizeof(a) / sizeof(a[0]);
    SelectSort(a, len);
    Print(a, len);
    return 0;
}
