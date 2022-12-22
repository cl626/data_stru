#ifndef __LISTQUEUE_H__
#define __LISTQUEUQ_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//构造排队队列Queue
typedef struct QNode {
	int Arrivtime;
	QNode* next;
	int Duration;
	int bill;	//+表示存钱，-表示取钱
}QNode;

typedef struct {
	QNode* front;
	QNode* rear;
}Queue;

//队列基本操作
Queue* InitQueue() {
	QNode* front = (QNode*)malloc(sizeof(QNode));
	QNode* rear = (QNode*)malloc(sizeof(QNode));
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = front;
	q->rear = rear;
	q->front->next=NULL;
	q->rear->next=NULL;
	return q;
}
//void DestroyQueue(Queue* Q);
//void ClearQueue(Queue* Q);
int QueueEmpty(Queue* Q) {
	return (Q->front->next == NULL) ? 1 : 0;
}
int QueueLength(Queue* Q) {
	int len = 0;
	QNode* a = Q->front->next;
	while (a!=NULL) {
//		printf("aaa  ");
		a = a->next;
		len++;
	}
	return len;
}

QNode* GetHead(Queue* Q) {
	return Q->front->next;
}
void EnQueue(Queue* Q, QNode* e) {	
	Q->rear->next = e;
	Q->rear = e;
	if (Q->front->next == NULL)
		Q->front->next = e;
}
void DelQueue(Queue* Q) {
	QNode* fr = Q->front->next;
	Q->front->next = fr->next;
	if (Q->front->next == NULL) Q->rear->next = NULL;
//	free(fr);
}

//自定义事件链表
typedef struct Elemtype{
	int OccurTime;
	int Ntype;	//Ntype==0表示到达事件，Ntype==1表示为离开事件，
	Elemtype *next;
}Elemtype;

typedef struct EventList{
	Elemtype* head;
	Elemtype* tail;
}EventList;

//链表操作
EventList* InitList() {
	Elemtype *head = (Elemtype*)malloc(sizeof(Elemtype));
	Elemtype *tail = (Elemtype*)malloc(sizeof(Elemtype));
	EventList *e = (EventList*)malloc(sizeof(EventList));
	e->head = head;
	e->tail = tail;
	e->head->next = NULL;
	e->tail->next = NULL;
	return e;
}


void OrderInsert(EventList* Q, Elemtype* e) {
	Elemtype* p = Q->head;
	Elemtype* q = p->next;
	if (Q->head->next == NULL) {
		Q->head->next = e;
		Q->tail->next = e;
	}
	else {
		while (q != NULL) {
			if (q->OccurTime <= e->OccurTime) {
				p = q;	q = q->next;
			}
			else break;
		}
		if (q == NULL) {	//tail<e
			p->next = e;
			e->next = NULL;
			Q->tail->next = e;
		}
		else   //p<=e<q ,include p=Q->head;
		{
			p->next = e;
			e->next = q;
		}
	}
}

int ListEmpty(EventList* Q) {
	return (Q->head->next == NULL) ? 1 : 0;
}

void DelList(EventList* Q){
	Elemtype* tou = Q->head->next;
	Q->head->next = tou->next;
	if (Q->head->next == NULL)	Q->tail->next = NULL;
//	free(tou);
}

Elemtype* EGetHead(EventList* Q) {
	return Q->head->next;
}

//Duration和bill随机
Elemtype* mkENode(int Occurtime, int Ntype, Elemtype* next) {
	Elemtype* mk = (Elemtype*)malloc(sizeof(Elemtype));
	mk->OccurTime = Occurtime;
	mk->Ntype = Ntype;
	mk->next = next;
	return mk;
};

QNode* mkQNode(int Arrivtime, QNode* next, int smax, int lmin) {
	QNode* mk = (QNode*)malloc(sizeof(QNode));
	mk->Arrivtime = Arrivtime;
	mk->next = next;
//	srand((unsigned)time(NULL));
	mk->bill = rand() % (smax - lmin) +lmin;
//	srand((unsigned)time(NULL));
	mk->Duration = rand() % 10+1;
	return mk;
};
#endif