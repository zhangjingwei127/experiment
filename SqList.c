#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20 
//存储空间初始分配量
typedef int ElemType;
//ElemType类型根据实际情况而定，这里假设为int
typedef int Status;
//Status是函数的类型，其值是函数结果状态代码，如OK等
typedef struct
{
    ElemType data[MAXSIZE];
    //数组，存储数据元素
    int length;
    //线性表当前长度
}SqList;
//初始化顺序线性表
Status InitList(Sqlist *L)
{
    L->length = 0;
    return OK;
}
//顺序表的建立
SqList Create(SqList L)
{
    int i;
    for(i = 0; i < 10; i++)
    {
        L.data[i] = i;
        L.length++;
    }

    return L;
}
Status ClearList(SqList *L)
{
    L->length = 0;
    return OK;
}
//
