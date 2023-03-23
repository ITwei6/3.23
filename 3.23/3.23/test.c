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
//������ṹ
typedef struct Queue
{
	QNode* head;
	QNode* tail;
	int size;
}Queue;
//��ͷָ���βָ���װ���� 
//��ʼ������
void  QueueInit(Queue* pq);
//���ٶ���
void  QueueDestroy(Queue* pq);
//�����
void  QueuePush(Queue* pq, QDatatype x);
//������
void  QueuePop(Queue* pq);
//��ȡ���е���Ч���ݵĴ�С
int  QueueSize(Queue* pq);
//�ж϶����Ƿ�Ϊ��
bool  QueueEmpty(Queue* pq);
//��ȡ��ͷ����
QDatatype  QueueFront(Queue* pq);
//��ȡ��β����
QDatatype  QueueBack(Queue* pq);
#include "Queue.h"
//��ʼ������
void  QueueInit(Queue* pq)
{
	assert(pq);
	pq->head = pq->tail = NULL;
	pq->size = 0;
}
//���ٶ���
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
	//������һ���ͷţ�������һ���ͷ�
	pq->head = pq->tail = NULL;
	pq->size = 0;
}
//�����
void  QueuePush(Queue* pq, QDatatype x)
{
	assert(pq);
	//��ӣ�����β��һ����㣬��������һ���½��
	QNode* newnode = (QNode*)malloc(sizeof(QNode));
	newnode->next = NULL;//��Ҫ�ÿգ���Ȼ�����Ұָ��
	newnode->data = x;//�����ݸ�ֵ
	if (newnode == NULL)
	{
		perror("malloc");
	}
	//�����ڱ�������һ��ʼhead��tail��Ϊ�գ���һ��ֱ�ӽ���㸳ֵ��ȥ��Ȼ��������������β��
	if (pq->head == NULL)
	{
		pq->head = pq->tail = newnode;
	}
	else
	{
		//β��
		pq->tail->next = newnode;
		pq->tail = newnode;//��β--����
	}
	pq->size++;
}
//������
void  QueuePop(Queue* pq)
{
	assert(pq);
	//��ɾ������֮ǰ��Ҫ���Ƕ����Ƿ�Ϊ��;
	assert(!pq->head == NULL);
	//��������ʵ����ͷɾ��ͷɾ������ͷָ�벻�ϸı䣬��ͷָ��ǰ��Ľ���ͷ�


	QNode* next = pq->head->next;
	free(pq->head);
	pq->head = next;
	//���ϵ�ͷɾ
	//��Ҫע��tail��ָ�����һ������ָ�롣
	//��headָ�����һ�������ͷţ���ôtailָ��Ŀռ䱻�ͷţ���tail�ͱ��Ұָ����
	//���������Ҫ��tail��NULL
	//�����з�ʽ����һ�֣���ֻ��ͷɾ������ٽ�tail��NULL
	//�ڶ��У�һ��ʼ�Ϳ��Ƕ�����������һ�����֮ǰ�������һ�����
	// //��Ϊһ�����Ͷ�����
	//����1��
	if (pq->head == NULL)
	{
		pq->tail = NULL;
	}
	//////�ڶ��ַ�����
	//if (pq->head->next == NULL)
	//{
	//	//ֱ���ͷ����һ�����
	//	free(pq->head);
	//	pq->head = pq->tail = NULL;
	//}
	//else
	//{
	//	//ͷɾ
	//}
	pq->size--;
}
//��ȡ���е���Ч���ݵĴ�С 
QueueSize(Queue* pq)
{
	assert(pq);
	return pq->size;//����ո��ڷ�װ�ṹ���в���size�Ļ���Ҫ��õ����еĳ��ȣ�����Ҫ��������ģ���ʱ�临�Ӷ�O��N��
	//���÷�������ȥ�����O��1��������Ҫ�������������������������ٵõ�����Ĵ�С��
	//Ҳ����ʹ�ø÷�������ͷָ���size��װ��һ���ṹ�壬���ýṹ�崫��push��pop����������
	//�����������ڱ�ͷ���size�ǲ����Ե� ����֪����������
}

//̸һ̸����������˳��������?
// �ռ俪�ٵ�λ��2.14
//�ж϶����Ƿ�Ϊ��
bool  QueueEmpty(Queue* pq)
{
	assert(pq);
	return pq->size == 0;
}
//��ȡ��ͷ����
QDatatype  QueueFront(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));
	return pq->head->data;
}
//��ȡ��β����
QDatatype  QueueBack(Queue* pq)
{
	assert(pq);
	assert(!QueueEmpty(pq));
	return pq->tail->data;

}
#include "Queue.h"

typedef struct //����������ʽΪ�����ṹ�壬û�����ֵ���Ч
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
	//���ȳ�ʼ��Mystack��������������������
	QueueInit(&st->q1);
	QueueInit(&st->q2);
	return st;
}

void myStackPush(MyStack* obj, int x)
{
	assert(obj);
	if (!QueueEmpty(&obj->q1))//���q1��Ϊ��
	{
		QueuePush(&obj->q1, x);//�ͽ����ݲ���q1��
	}
	else//���q1Ϊ�գ���q2��Ϊ�գ�����q2�в�������
	{
		QueuePush(&obj->q2, x);//���߶�Ϊ�գ�������һ��
	}
}

int myStackPop(MyStack* obj)
{
	Queue* empty = &obj->q1;//����һ��ʼq1�ǿն���
	Queue* nonempty = &obj->q2;//����q2�Ƿǿն���
	if (!QueueEmpty(empty))//������������q1���Ƿǿն��У�q2�ǿն���
	{
		empty = &obj->q2;
		nonempty = &obj->q1;
	}
	//�������ǾͲ��ù�˭�ǿ�˭�Ƿǿ��ˣ�empty���ǿգ�nonempty���Ƿǿ�
	//���ǿն���ǰn-1��Ԫ�ص���ն����л�
	//�������ݡ�
	while (QueueSize(nonempty) - 1 > 0)
	{
		QueuePush(empty, QueueFront(nonempty));
		//����ն���   //��ȡ��ͷԪ��
		QueuePop(nonempty);//������pop��
	}
	//�ߵ���ʱ˵���ǿն��о�ʣ���һ��Ԫ���ˣ���ջ��Ԫ��
	//Ҫ�󷵻�ջ��Ԫ�أ�����������Ҫ��������
	int top = QueueFront(nonempty);
	QueuePop(nonempty);//ɾ�����һ��Ԫ��
	return top;
}

int myStackTop(MyStack* obj) {
	assert(obj);

	if (!QueueEmpty(&obj->q1))//���q1��Ϊ��
	{
		return QueueBack(&obj->q1);//��β���ݼ�ջ������
	}
	else//���q1Ϊ�գ���q2��Ϊ�գ�
	{
		return QueueBack(&obj->q2);//��β���ݼ�ջ������
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

//����������Ҫ--���ϵ���
//ɾ��������Ҫ--���µ���
