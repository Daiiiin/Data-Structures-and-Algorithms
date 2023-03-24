#include <stdio.h>
#include <stdlib.h>
#define MAX 0xA

typedef struct node{
	int Elem[MAX];
	int count;
}*List;

void initList(List *L){
	*L = (List)malloc(sizeof(struct node));
	(*L)->count = 0;
}

void insertLast(List *L, int data){
	if((*L)->count != MAX){
		(*L)->Elem[(*L)->count] = data;
		(*L)->count++;
	}
}

void displayList(List L){
	int i;
	for(i = 0; i < MAX; i++){
		printf("Index[%d]: %d\n", i, L->Elem[i]);
	}
}

void populateList(List *L){
	int data[MAX] = {32,54,12,65,87,31,9,75,54};
	int i;
	for(i = 0; i < MAX; i++){
		insertLast(L,data[i]);
	}
}

int main(){
	List L;
	
	initList(&L);
	populateList(&L);
	displayList(L);
	printf("Count: %d\n", L->count);
	
	return 0;
}