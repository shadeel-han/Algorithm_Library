/*
    Library: Linked List
    Algorithm: practice operations of queue/stack
    Input: int
    Output: the list
    Operation:  FrontPush	=> insert element to the front
    			EndPush		=> insert element to the end
                FrontPop    => pop the first element
                EndPop		=> pop the last element
*/

#include <stdio.h>
#include <stdlib.h>		/* for malloc */

#define IS_EMPTY(x) (!(x))

typedef struct Node *ListPtr;	/*self-referential structure */
typedef struct Node{
	int data;
	ListPtr pre, next;
}Node;

ListPtr CreateNode(int data){
	ListPtr tmp;
	tmp = (ListPtr)malloc(sizeof(Node));
	tmp->data = data;
	tmp->pre = NULL;	tmp->next = NULL;
	return tmp;
}

void FrontPrint(ListPtr ptr){
	printf("Front->End:");
	for(; ptr!=NULL; ptr=ptr->next)
		printf(" %d", ptr->data);
	putchar('\n');
}

void EndPrint(ListPtr ptr){
	printf("End->Front:");
	for(; ptr!=NULL; ptr=ptr->pre)
		printf(" %d", ptr->data);
	putchar('\n');
}

void FrontPush(ListPtr *head, ListPtr *tail, int data){	/* call by pointer */
	ListPtr tmp = CreateNode(data);
	if( IS_EMPTY(*head) )	*tail = tmp;
	else					tmp->next = *head, (*head)->pre = tmp;
	*head = tmp;
}

void EndPush(ListPtr *head, ListPtr *tail, int data){
	ListPtr tmp = CreateNode(data);
	if( IS_EMPTY(*head) )	*head = tmp;
	else					tmp->pre = *tail, (*tail)->next = tmp;
	*tail = tmp;
}

int FrontPop(ListPtr *head, ListPtr *tail){	// return type according to stored data
	if( IS_EMPTY(*head) )	return -1;
	ListPtr tmp = *head;
	*head = tmp->next;
	if( IS_EMPTY(*head) )	*tail = NULL;
	else					(*head)->pre = NULL;
	int data = tmp->data;
	free(tmp);
	return data;
}

int EndPop(ListPtr *head, ListPtr *tail){	// return type according to stored data
	if( IS_EMPTY(*tail) )	return -1;
	ListPtr tmp = *tail;
	*tail = tmp->pre;
	if( IS_EMPTY(*tail) )	*head = NULL;
	else					(*tail)->next = NULL;
	int data = tmp->data;
	free(tmp);
	return data;
}

int main(void){
	ListPtr head = NULL, tail = NULL;
	int i, j;
	
	while(1){
		puts("1.Front Push\n2.End Push\n3.Front Pop\n4.End Pop");
		printf("Choose operation: ");
		scanf("%d", &i);	if(i==0)	break;
		if(i<3){
			printf("Input integer: ");	scanf("%d", &j);
			if( i==1 )	FrontPush(&head, &tail, j);
			else		EndPush(&head, &tail, j);
		}else{
			if( i==3 )	j = FrontPop(&head, &tail);
			else		j = EndPop(&head, &tail);
			printf(">> Pop out: %d\n", j);
		}
		FrontPrint(head);EndPrint(tail);putchar('\n');
	}
	
	return 0;
}

