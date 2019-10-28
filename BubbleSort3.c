#include <stdio.h>
#include <stdbool.h>

void BubbleSort(int* a[], int n)
{
    int i,j,temp;
    bool change = true;
    for(i = n-1; change == true, i>0; --i)
    {
        change = false;
        for(j = 0; j < i; ++j)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
                change = true;
            }
        }
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
    int* a[] = {95,65,7,3,567,233,54,45,235,0,1};
    int len = sizeof(a) / sizeof(a[0]);
    BubbleSort(a, len);
    Print(a, len);
    return 0;
}

