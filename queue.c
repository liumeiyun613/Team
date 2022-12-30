#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

//定义队列最大长度
const int MaxSize=50;

//创建队列
Queue* CreateQueue()
{
    Queue* h=(Queue*)malloc(sizeof(Queue));
    if(h==NULL)
    {
        printf("Malloc failed!\n");
        return NULL;
    }
    h->next=NULL;
    return h; 
}

//删除队列
void DestroyQueue(Queue* h)
{
    Queue* p=h;
    while(p!=NULL)
    {
        Queue* tmp=p;
        p=p->next;
        free(tmp);
    }
}

//进队操作
int Push(Queue* h, T t)
{
	//创建节点
    Queue* tmp=(Queue*)malloc(sizeof(Queue));
    if(tmp==NULL)
    {
        printf("Malloc failed!\n");
        return;
    }
    strcpy(tmp->data, t);    
    tmp->next=NULL;
    
    if(length>=MaxSize)
    {
        printf("Queue is full!\n");
        return -1;
    }
	
    Queue* p=h;
    //找到队列尾
	while(p->next!=NULL)
    {
        p=p->next;
    }
	//插入队列尾
    p->next=tmp;
    length++;
	
	return 0;
}

//出队操作
int Pop(Queue* h, T t)
{
    Queue* res=h->next; //从队列头出队
    if(h->next==NULL)
    {
        printf("Queue is empty!\n");
        return -1;
    }
	
	//摘下队列头
    h->next=h->next->next;
    length--;
	//返回节点数据
	strcpy(t, res->data);
	//释放节点
	free(res);
	
    return 0;
}

//显示队列
void Print(Queue* h)
{
    Queue* p=h->next;
    while(p!=NULL)
    {
        printf("%s\n",p->data);
        p=p->next;
    }
    printf("Above is the Queue!\n");
    printf("\n");
}
