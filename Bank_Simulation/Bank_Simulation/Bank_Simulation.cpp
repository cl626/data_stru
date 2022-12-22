// Bank_Simulation.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//随机数的生成:http://c.biancheng.net/view/2043.html

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "listqueue.h"

//链表*3
EventList* ev;
Queue* wait1, * wait2;
//总体参数
int total;
//时间相关
int curr;	//当前时间
int closetime;
int Totaltime;	//逗留总时间
int customer_number;
int max_save;
int max_lend;
//美好的一天开始
void OpenForDay(int smax,int lmin) {
	Totaltime = 0;
	customer_number = 0;
	ev = InitList();
	wait1=InitQueue();
	wait2=InitQueue();
	OrderInsert(ev, mkENode(0, 0, NULL));
	printf("Open for one day!\n");
}

//原来这个处理到达事件
void CustomerArrived(EventList *ev,Elemtype *en,int closetime,int smax,int lmin){
//Ntype==0
	printf("A customer arrived at %d\n", en->OccurTime);	//debug ;
	customer_number=customer_number+1;
	printf("customer number:%d\n", customer_number);
//	srand((unsigned)time(NULL));
	int interval = rand() % 10+1;
	if (en->OccurTime + interval < closetime)
		OrderInsert(ev, mkENode(en->OccurTime + interval, 0, NULL));
	QNode* qnew = mkQNode(en->OccurTime, NULL, smax, lmin);
	printf("duration:%d,bill:%d\n", qnew->Duration, qnew->bill);
	EnQueue(wait1, qnew);
	if (QueueLength(wait1) == 1&&(QueueLength(wait2)==0?1:(total+GetHead(wait2)->bill<0))){	//wait1为空且wait2不能继续执行
		if (total + qnew->bill >= 0)	OrderInsert(ev, mkENode(en->OccurTime + qnew->Duration, 1, NULL));
		else	OrderInsert(ev, mkENode(en->OccurTime , 3, NULL));
	}
}

void CustomerDeparture(EventList* ev, Elemtype* en, Queue* wait1, Queue* wait2, int totaltime) {
	//离开先处理
	if (en->Ntype == 1) {
		printf("A customer arrived at %d leaved at %d from queue1\n", GetHead(wait1)->Arrivtime, en->OccurTime);	//debug
		total += GetHead(wait1)->bill;
		Totaltime += en->OccurTime - GetHead(wait1)->Arrivtime;
		DelQueue(wait1);
		if (!QueueEmpty(wait2)&& (total + GetHead(wait2)->bill >= 0)) 	//先处理可以处理的wait2，
				OrderInsert(ev, mkENode(en->OccurTime + GetHead(wait2)->Duration, 2, NULL));	//wait1不空处理wait1
		else if (!QueueEmpty(wait1)) {	//只能接着处理wait1的下一个
			if (total + GetHead(wait1)->bill >= 0)				OrderInsert(ev, mkENode(en->OccurTime + GetHead(wait1)->Duration, 1, NULL));
			else OrderInsert(ev, mkENode(en->OccurTime, 3, NULL));
		}
	}
	else if (en->Ntype == 2) {			//先处理可以处理的wait2，
		printf("A customer arrived at %d leaved at %d from queue2\n", GetHead(wait2)->Arrivtime, en->OccurTime);	//debug
		total += GetHead(wait2)->bill;
		Totaltime += en->OccurTime - GetHead(wait2)->Arrivtime;
		DelQueue(wait2);
		if (!QueueEmpty(wait2) && (total + GetHead(wait2)->bill >= 0))
			OrderInsert(ev, mkENode(en->OccurTime + GetHead(wait2)->Duration, 2, NULL));
		else if (!QueueEmpty(wait1)) {		////wait1不空处理wait1
			if (total + GetHead(wait1)->bill >= 0)	OrderInsert(ev, mkENode(en->OccurTime + GetHead(wait1)->Duration, 1, NULL));
			else OrderInsert(ev, mkENode(en->OccurTime, 3, NULL));
		}
	}
	else {//Ntype==3
		printf("A customer convert to queue2 at %d\n", en->OccurTime);	//debug
		QNode* qnew = GetHead(wait1);	//wait1->head移入wait2
		DelQueue(wait1);
		EnQueue(wait2, qnew);
		if (!QueueEmpty(wait1)) {			//wait1不空处理wait1
			if (total + GetHead(wait1)->bill >= 0)	OrderInsert(ev, mkENode(en->OccurTime + GetHead(wait1)->Duration, 1, NULL));
			else OrderInsert(ev, mkENode(en->OccurTime, 3, NULL));
		}
		//else 等待下一个customerArrived
	}
}

//Ntype==0 用户到达
//Ntype==1 customer离开队伍1
//Ntype==2 customer离开队伍2
//Ntype==3 custoemr离开队伍1进入队伍2

int main(){
	printf("input total:");
	scanf_s("%d", &total);
//	printf("total:%d\n", total);
	printf("input closetime:");
	scanf_s("%d", &closetime);
	printf("input max_save and max_lend:");
	scanf_s("%d %d", &max_save, &max_lend);
	OpenForDay(max_save,max_lend);	//变量在OpenForday()中初始化
	srand((unsigned)time(NULL));
//	printf("total:%d\n", total);
	while (!ListEmpty(ev)) {
		printf("total:%d\n", total);
		if (EGetHead(ev)->Ntype == 0)	CustomerArrived(ev, EGetHead(ev), closetime,max_save,max_lend);
		else	CustomerDeparture(ev, EGetHead(ev), wait1, wait2, Totaltime);
		DelList(ev);
	}
	printf("结束后的:\n");
	printf("wait2 长度=%d\n", QueueLength(wait2));
/*	int q2_len = QueueLength(wait2);
	for (int i = 0; i < q2_len; i++) {
		Totaltime += closetime - GetHead(wait2)->Arrivtime;
		DelQueue(wait2);
		printf("这是第%d次\n", i);
	}*/
	printf("结束金额：%d\n", total);
	printf("人数：%d\n", customer_number);
	printf("人均用时:%d\n", Totaltime/customer_number);
}