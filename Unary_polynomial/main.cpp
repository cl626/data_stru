#include<stdio.h>
#include<stdlib.h>
using namespace std;
struct ListNode {
	float coef;	//系数
	int expn;	
	ListNode* next;
};
struct polynomial {
	ListNode* head;
	ListNode* tail;
};
void CreatePolyn(polynomial* p,int m) {
	float coef;
	int expn;
	p->head = (ListNode*)malloc(sizeof(ListNode));
	p->tail = (ListNode*)malloc(sizeof(ListNode));
	printf("input your expn:");
	if (m == 0) {
		p->head->next = NULL;
		p->tail = NULL;
		printf("\n");
	}
	for (int i = 0; i < m; i++) {
		scanf_s("%f %d", &coef, &expn);
		ListNode* node = (ListNode*)malloc(sizeof(ListNode));
//		if (node == NULL)	return;
		node->coef = coef;
		node->expn = expn;
		if (i == 0) {
			p->head->next = node;
			p->tail = node;
			node->next = NULL;
		}
		else {
			p->tail->next = node;
			node->next = NULL;
			p->tail = node;
		}
	}
	return;
}

void DestroyPolyn(polynomial* p) {
	ListNode* trav = (ListNode*)malloc(sizeof(ListNode));
	ListNode* next = (ListNode*)malloc(sizeof(ListNode));
	trav=p->head->next;
	free(p->head);
	while (trav!= NULL) {
		next = trav->next;
		free(trav);
		trav = next;
	}
}

void PrintPolyn(polynomial* p) {
//	printf("p->head:%d\n", p->head);
//	printf("p->head->next:%d\n", p->head->next);
//	printf("p->tail:%d\n", p->tail);
//	printf("input unary_polynomial:");
	ListNode* trav = (ListNode*)malloc(sizeof(ListNode));
//	ListNode* next = (ListNode*)malloc(sizeof(ListNode));
	trav = p->head->next;
//	printf("  trava is:%d", trav);
	if (trav == NULL) {
		printf("0\n");
		return;
	}
	printf("%.2f x^%d ", trav->coef, trav->expn);
	trav = trav->next;
	while (trav != NULL) {
		if (trav->expn == 0)	printf("+ %.2f ", trav->coef);
		else printf("+ %.2f x^%d", trav->coef, trav->expn);
		trav = trav->next;
	}
	printf("\n");
}

int PolynLength(polynomial* p) {	//返回多项式项数
	int item = 0;
	ListNode* trav = (ListNode*)malloc(sizeof(ListNode));
	trav = p->head;
	while (trav != NULL) {
		trav = trav->next;
		item++;
	}
	return item;
}

void AddPolyn(polynomial* pa, polynomial* pb) {
	ListNode* trava = (ListNode*)malloc(sizeof(ListNode));
	ListNode* trava_ah = (ListNode*)malloc(sizeof(ListNode));
	ListNode* travb = (ListNode*)malloc(sizeof(ListNode));
//	ListNode* travb_ah = (ListNode*)malloc(sizeof(ListNode));
	ListNode* tema = (ListNode*)malloc(sizeof(ListNode));
	ListNode* temb = (ListNode*)malloc(sizeof(ListNode));
	trava_ah = pa->head;
//	travb_ah = pb->head;
	trava = pa->head->next;
	travb = pb->head->next;
//用头结点不用考虑pa只有一项
	while (trava != NULL && travb != NULL) {
		if (trava->expn > travb->expn) {	//trava指数小于travb，将travb插入到trava与trava_ah之间,并释放travb_ah,
			temb = travb->next;
			trava_ah->next = travb;
			travb->next = trava;
			trava_ah = travb;
			travb = temb;
		}
//trava->next==travb->expn isn't thoroughly considered
		else if (trava->expn < travb->expn) {
			while (trava->next != NULL && trava->next->expn <= travb->expn) {
				trava_ah = trava;
				trava = trava->next;	//trava<travb<trava->next||trava->next=NULL,trava->travb->trava->next;
			}
			if (trava->expn == travb->expn) {
				goto equal;
			}
			tema = trava->next;
			trava->next = travb;
			temb = travb->next;
			travb->next = tema;
			trava_ah = travb;	//travb成为trava->next的ah
			trava = tema;
			travb = temb;
		}
		else {
		equal:			
			trava->coef += travb->coef;
			if (trava->coef == 0) {
				tema = trava->next;
				trava_ah->next = tema;
				free(trava);
				trava = tema;
			}
//			else {
//				trava_ah = trava;
//				trava = trava->next;
//			}
			temb = travb->next;
			free(travb);
			travb = temb;
		}
	}
//trava==NULL或travb==NULL
	if (trava == NULL) {
		trava_ah->next = travb;
	}
	free(pb->head);
	free(pb);
}

int invert_list(polynomial* p) {	//when p至少有一项
	if (p->head->next == NULL)	return 0;
	ListNode* trav1 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* trav2 = (ListNode*)malloc(sizeof(ListNode));
	ListNode* stor = (ListNode*)malloc(sizeof(ListNode));
	trav1 = p->head->next;
	trav2 = trav1->next;
	while (trav2 != NULL) {
		stor = trav2->next;
		trav2->next = trav1;
		trav1 = trav2;
		trav2 = stor;
	}
	stor = p->head->next;
	p->head->next = trav1;
	p->tail = stor;
	stor->next = NULL;
	return 1;
}

void SubPolyn(polynomial* pa, polynomial* pb) {
	ListNode* trava = (ListNode*)malloc(sizeof(ListNode));
	ListNode* trava_ah = (ListNode*)malloc(sizeof(ListNode));
	ListNode* travb = (ListNode*)malloc(sizeof(ListNode));
	//	ListNode* travb_ah = (ListNode*)malloc(sizeof(ListNode));
	ListNode* tema = (ListNode*)malloc(sizeof(ListNode));
	ListNode* temb = (ListNode*)malloc(sizeof(ListNode));
	trava_ah = pa->head;
	//	travb_ah = pb->head;
	trava = pa->head->next;
	travb = pb->head->next;
	//用头结点不用考虑pa只有一项
	while (trava != NULL && travb != NULL) {
		if (trava->expn > travb->expn) {	//trava指数小于travb，将travb插入到trava与trava_ah之间,并释放travb_ah,
			travb->coef = travb->coef * (-1);
			temb = travb->next;
			trava_ah->next = travb;
			travb->next = trava;
			trava_ah = travb;
			travb = temb;
		}
		//trava->next==travb->expn isn't thoroughly considered
		else if (trava->expn < travb->expn) {
			while (trava->next != NULL && trava->next->expn <= travb->expn) {
				trava_ah = trava;
				trava = trava->next;	//trava<travb<trava->next||trava->next=NULL,trava->travb->trava->next;
			}	
			if (trava->expn == travb->expn) {
				goto equal;
			}
			travb->coef *= (-1);
			tema = trava->next;
			trava->next = travb;
			temb = travb->next;
			travb->next = tema;
			trava_ah = travb;	//travb成为trava->next的ah
			trava = tema;
			travb = temb;
		}
		else {
		equal:			
			trava->coef -= travb->coef;
			if (trava->coef == 0) {
				tema = trava->next;
				trava_ah->next = tema;
				free(trava);
				trava = tema;
			}
//			else {
//				trava_ah = trava;
//				trava = trava->next;
//			}
			temb = travb->next;
			free(travb);
			travb = temb;
		}
	}
	//trava==NULL或travb==NULL
	if (trava == NULL) {
		trava_ah->next = travb;
	}
	free(pb->head);
	free(pb);
}

int main() {
	polynomial* pa = (polynomial*)malloc(sizeof(polynomial));
	polynomial* pb = (polynomial*)malloc(sizeof(polynomial));
	char func;	//指示"+","-"法
	int item_a, item_b;
	printf("input your function:");
	scanf_s("%c", &func);
	printf("input items of pa,pb in order:");
	scanf_s("%d %d", &item_a, &item_b);
	CreatePolyn(pa, item_a);
	CreatePolyn(pb, item_b);
	invert_list(pa);
	printf("第一个多项式为：");
	PrintPolyn(pa);
	invert_list(pa);
	invert_list(pb);
	printf("第二个多项式为：");
	PrintPolyn(pb);
	invert_list(pb);
	if (func == '+')	AddPolyn(pa, pb);
	else	SubPolyn(pa, pb);
	invert_list(pa);
	printf("运算结果为：");
	PrintPolyn(pa);
	return 0;
}

void MultiPolyn(polynomial* pa, polynomial* pb) {

}