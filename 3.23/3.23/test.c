#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
typedef int QDatatype;
typedef struct QNode
{
	struct QNode* next;
	QDatatype data;
}QNode;
//定义结点结构
typedef struct Queue
{
	QNode* head;
	QNode* tail;
	int size;
}Queue;
//将头指针和尾指针分装起来 
//初始化队列
void  QueueInit(Queue* pq);
//销毁队列
void  QueueDestroy(Queue* pq);
//入队列
void  QueuePush(Queue* pq, QDatatype x);
//出队列
void  QueuePop(Queue* pq);
//获取队列的有效数据的大小
int  QueueSize(Queue* pq);
//判断队列是否为空
bool  QueueEmpty(Queue* pq);
//获取队头数据
QDatatype  QueueFront(Queue* pq);
//获取队尾数据
QDatatype  QueueBack(Queue* pq);
#include "Queue.h"
//初始化队列
void  QueueInit(Queue* pq)
{
	assert(pq);
	pq->head = pq->tail = NULL;
	pq->size = 0;
}
//销毁队列
void  QueueDestroy(Queue* pq)
{
	assert(pq);
	QNode* cur = pq->head;
	while (cur)
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}
	//保存下一个释放，保存下一个释放
	pq->head = pq->tail = NULL;
	pq->size = 0;
}
//入队列
void  QueuePush(Queue* pq, QDatatype x)
{
	assert(pq);
	//入队，就是尾插一个结点，首先生成一个新结点
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	newnode->next = NULL;//需要置空，不然会出现野指针
	newnode->data = x;//将数据赋值
	if (newnode == NULL)
	{
		perror("malloc");
	}
	//不带哨兵，所以一开始head和tail都为空，第一步直接将结点赋值过去，然后后面才是真正的尾插
	if (pq->head == NULL)
	{
		pq->head = pq->tail = newnode;
	}
	else
	{
		//尾插
		pq->tail->next = newnode;
		pq->tail = newnode;//找尾--更新
	}
	pq->size++;
}
//出队列
void  QueuePop(Queue* pq)
{
	assert(pq);
	//在删除数据之前需要考虑队列是否为空;
	assert(!pq->head == NULL);
	//出队列其实就是头删，头删就是让头指针不断改变，让头指针前面的结点释放


	QNode* next = pq->head->next;
	free(pq->head);
	pq->head = next;
	//不断的头删
	//但要注意tail是指向最后一个结点的指针。
	//当head指向最后一个结点后释放，那么tail指向的空间被释放，那tail就变成野指针了
	//所以最后需要将tail置NULL
	//有两中方式：第一种，，只管头删，最后再将tail置NULL
	//第二中，一开始就考虑二种情况，最后一个结点之前，和最后一个结点
	// //分为一个结点和多个结点
	//方法1：
	if (pq->head == NULL)
	{
		pq->tail = NULL;
	}
	//////第二种方法：
	//if (pq->head->next == NULL)
	//{
	//	//直接释放最后一个结点
	//	free(pq->head);
	//	pq->head = pq->tail = NULL;
	//}
	//else
	//{
	//	//头删
	//}
	pq->size--;
}
//获取队列的有效数据的大小 
QueueSize(Queue* pq)
{
	assert(pq);
	return pq->size;//如果刚刚在分装结构体中不加size的话，要想得到队列的长度，是需要遍历链表的，那时间复杂度O（N）
	//而该方法加上去后就是O（1），不需要遍历。在链表中我们如果想快速得到链表的大小，
	//也可以使用该方法，将头指针和size分装成一个结构体，将该结构体传给push和pop操作函数。
	//还有在链表哨兵头里放size是不可以的 ，不知道数据类型
}

//谈一谈柔性数组与顺序表的区别?
// 空间开辟的位置2.14
//判断队列是否为空
bool  QueueEmpty(Queue* pq)
{
	assert(pq);
	return pq->size == 0;
}
//获取队头数据
QDatatype  QueueFront(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));
	return pq->head->data;
}
//获取队尾数据
QDatatype  QueueBack(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));
	return pq->tail->data;

}
#include "Queue.h"

typedef struct //该重命名方式为匿名结构体，没有名字但有效
{
	Queue q1;
	Queue q2;
} MyStack;

MyStack* myStackCreate()
{
	MyStack* st = (MyStack*)malloc(sizeof(MyStack));
	if (st == NULL)
	{
		perror("malloc");
	}
	//首先初始化Mystack两个变量，即两个队列
	QueueInit(&st->q1);
	QueueInit(&st->q2);
	return st;
}

void myStackPush(MyStack* obj, int x)
{
	assert(obj);
	if (!QueueEmpty(&obj->q1))//如果q1不为空
	{
		QueuePush(&obj->q1, x);//就将数据插入q1中
	}
	else//如果q1为空，则q2不为空，就往q2中插入数据
	{
		QueuePush(&obj->q2, x);//或者都为空，随便进入一个
	}
}

int myStackPop(MyStack* obj)
{
	Queue* empty = &obj->q1;//假设一开始q1是空队列
	Queue* nonempty = &obj->q2;//假设q2是非空队列
	if (!QueueEmpty(empty))//如果假设错误那q1就是非空队列，q2是空队列
	{
		empty = &obj->q2;
		nonempty = &obj->q1;
	}
	//这样我们就不用管谁是空谁是非空了，empty就是空，nonempty就是非空
	//将非空队列前n-1个元素导入空队列中华
	//【导数据】
	while (QueueSize(nonempty) - 1 > 0)
	{
		QueuePush(empty, QueueFront(nonempty));
		//插入空队列   //获取队头元素
		QueuePop(nonempty);//将数据pop掉
	}
	//走到这时说明非空队列就剩最后一个元素了，即栈顶元素
	//要求返回栈顶元素，所以我们需要保存下来
	int top = QueueFront(nonempty);
	QueuePop(nonempty);//删除最后一个元素
	return top;
}

int myStackTop(MyStack* obj) {
	assert(obj);

	if (!QueueEmpty(&obj->q1))//如果q1不为空
	{
		return QueueBack(&obj->q1);//队尾数据即栈顶数据
	}
	else//如果q1为空，则q2不为空，
	{
		return QueueBack(&obj->q2);//队尾数据即栈顶数据
	}

}

bool myStackEmpty(MyStack* obj)
{
	assert(obj);
	return QueueEmpty(&obj->q1) && QueueEmpty(&obj->q2);
}

void myStackFree(MyStack* obj)
{
	assert(obj);
	QueueDestroy(&obj->q1);
	QueueDestroy(&obj->q2);
	free(obj);
	obj = NULL;
}
int main()
{
	Queue pq;
}

//插入数据需要--向上调整
//删除数据需要--向下调整
