#include<stdio.h>
#include<stdbool.h>

void BubbleSort(int* a[],int n)
{
    int i,j,temp;
    bool chance=true;
    for(i=n-1;i>0 && chance;--i)
    {
        chance=false;
        for(j=0;j < i; ++j)
        {
            if(a[j] > a[j+1])
            {
                chance = true;
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }//if
        }//for
    }//for
}//BubbleSort
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
    BubbleSort(a,len);
    Print(a,len);
    return 0;
}
