//字符串逆置，2019.4.1 J
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void reverse(char a[], int len)
{
    char *p;//用作头
    char *q;//用作尾
    char temp;
    p = a;
    q = a + (len - 1);

    while(p < q)
    {
        temp = *p;
        *p = *q;
        *q = temp;

        p++;
        q--;
    }
}

int main()
{
    char s[100];
    gets(s);
    int length = strlen(s);
    reverse(s,length);
    puts(s);
    return 0;
}
