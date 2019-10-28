#include<stdio.h>
#include<stdbool.h>

void SelectSort(int* a[], int n)
{
    int i,j,k,temp;
    for(i = 0; i < n-1; ++i)
    {
        j = i;
        for(k = i+1; k < n; ++k)
        { 
            if(a[j] > a[k])
                j = k;
        }
        if(j != i)
        {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
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
    int* a[] = {23,25,1,3,2,9,6,0,};
    int len = sizeof(a) / sizeof(a[0]);
    SelectSort(a,len);
    Print(a,len);
    return 0;
}
