#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 0x1a  // 25

typedef struct node{
	char lname[16];
	struct node *link;
}*List;

typedef List Dictionary[MAX];

void initDic(Dictionary d){
	int i;
	for(i = 0; i < MAX; i++){
		d[i] = NULL;
	}
}

int hash(char lname[]){
	return lname[0] - 'A';
}

void insert(Dictionary d, char lname[]){
	List *trav, temp;
	int key = hash(lname);
	for(trav = &d[key]; *trav != NULL && (*trav)->lname < lname; trav = &(*trav)->link){}
	// check if element exist to avoid duplication
	if(*trav != NULL || (*trav)->lname != lname){
		temp = (List)malloc(sizeof(struct node));
		if(temp != NULL){
			strcpy(temp->lname,lname);
			temp->link = *trav;
			*trav = temp;
		}
	}
}

int isMember(Dictionary d, char lname[]){
	List trav;
	int key = hash(lname);
	for(trav = d[key]; trav != NULL && strcmp(trav->lname,lname) != 0; trav = trav->link){}
	return trav != NULL? 1 : 0;
}

void deleteMem(Dictionary d, char lname[]){
	List *trav, temp;
	int key = hash(lname);
	for(trav = &d[key]; *trav != NULL && strcmp((*trav)->lname,lname) != 0; trav = &(*trav)->link){}
	if(*trav != NULL){
		temp = *trav;
		*trav = temp->link;
		free(temp);
	}
}

void populateDic(Dictionary d){
	insert(d,"Desabelle");
	insert(d,"Alcisto");
	insert(d,"Abrigos");
	insert(d,"Retuya");
	insert(d,"Torre");
	insert(d,"Zendaya");
	insert(d,"Kamado");
	insert(d,"Bartolomeo");
	insert(d,"Elsher");
	insert(d,"Solace");
	insert(d,"Levine");
	insert(d,"Raven");
	insert(d,"Cromwell");
	insert(d,"Monroe");
	insert(d,"Hope");
	insert(d,"Jenkins");
	insert(d,"Poverly");
	insert(d,"Gonzales");
	insert(d,"Keller");
	insert(d,"Collymore");
	insert(d,"Stoll");
	insert(d,"Verlice");
	insert(d,"Hayes");
}

void displayDic(Dictionary d){
	int i;
	List trav;
	
	for(i = 0; i < MAX; i++){
		printf("Index[%d]: ", i);
		for(trav = d[i]; trav != NULL; trav = trav->link){
			printf("%s -> ", trav->lname);
		}
		printf("NULL\n");
	}
}

int main(){
	Dictionary D;
	
	initDic(D);
	populateDic(D);
	displayDic(D);
	
	printf("\nSearch Member:\n1 = YES, 0 = NO\n\n");
	printf("Is Desablle on the list? %d\n", isMember(D,"Desabelle"));
	printf("Is Alcisto on the list? %d\n", isMember(D,"Alcisto"));
	printf("Is Evans on the list? %d\n", isMember(D,"Evans"));
	printf("Is Boseman on the list? %d\n", isMember(D,"Boseman"));
	
	printf("\nDelete Members: Gonzales, Bartolomeo, Hope\n");
	deleteMem(D,"Gonzales");
	deleteMem(D,"Bartolomeo");
	deleteMem(D,"Hope");
	displayDic(D);
	
	
	return 0;
}