#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node* next;
}node, *LL;

void initLL(LL*);
void insertSorted(LL*, int);
void insertFirst(LL*, int);
void insertLast(LL*, int);
int member(LL, int);
void deleteMem(LL*, int);
void deleteMults(LL*, int);
void display(LL);

int main(void)
{
	LL list;
	initLL(&list);	
	insertSorted(&list, 8);
	insertSorted(&list, 3);
	insertSorted(&list, 4);
	insertSorted(&list, 1);
	display(list);
	
	printf("\n");
	
	deleteMults(&list, 2);
	display(list);
	
	return 0;
}

void initLL(LL* list)
{
	*list = NULL;
}

void insertSorted(LL* head, int data)
{
	LL temp, *trav;

	for(trav = head; *trav != NULL && (*trav)->data <= data; trav = &(*trav)->next){}
	temp = (LL) malloc (sizeof(node));
	if(temp != NULL){
		temp->data = data;
		temp->next = *trav;
		*trav = temp;
	}
}

void insertLast(LL* head, int data)
{
	LL temp, *trav;
	
	for(trav = head; *trav != NULL; trav = &(*trav)->next){}
	temp = (LL) malloc (sizeof(node));
	if(temp != NULL){
		temp->data = data;
		temp->next = *trav;
		*trav = temp;
	}
}

void insertFirst(LL* head, int data)
{
	LL temp;
	
	temp = (LL) malloc (sizeof(node));
	if(temp != NULL){
		temp->data = data;
		temp->next = *head;
		*head = temp;
	}	
}

int member(LL head, int data)
{
	LL trav;
	for(trav = head; trav != NULL && trav->data != data; trav = trav->next){}
	return trav == NULL ? 0 : 1;
}

void deleteMem(LL* head, int data)
{	
	LL temp, *trav;

	for(trav = head; *trav != NULL && (*trav)->data != data; trav = &(*trav)->next){}
	if(*trav != NULL){
		temp = *trav;
		*trav = temp->next;
		free(temp);
	}else{
		printf("\nItem does not belong in the list");
	}
}

void deleteMults(LL* head, int data)
{
	LL temp, *trav;
	for(trav = head; *trav != NULL;){
	
		if((*trav)->data % data == 0){
			temp = *trav;
			*trav = temp->next;
			free(temp);
		}else{
			trav = &(*trav)->next;
		}
	}
}

void display(LL head)
{
	printf("The Linked List Contains the ff: values:\n");
	for(;head != NULL; head = head->next){
		printf("%d, ", head->data);
	}
}
