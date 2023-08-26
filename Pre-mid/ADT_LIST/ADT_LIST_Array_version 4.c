#include <stdio.h>
#include <stdlib.h>
#define MAX 10

// HELLO

// kapoya

typedef struct node{
	int *elemPtr;
	int count;
}*LIST;

void initList(LIST* A){
	*A = (LIST)malloc(sizeof(struct node));
	if(*A != NULL){
		(*A)->elemPtr = (int*)malloc(sizeof(int) * MAX);
		(*A)->count = 0;
	}
}

void insert(LIST* A, char data, int pos){
	if((*A)->count < MAX && pos <= (*A)->count){
		for(int ctr = (*A)->count; ctr > pos; ctr--){
			(*A)->elemPtr[ctr] = (*A)->elemPtr[ctr-1];
		}
		(*A)->elemPtr[pos] = data;
		(*A)->count++;
	}else{
		printf("Array is full or position is invalid.\n");
	}
}

void display(LIST A){
	for(int i = 0; i < A->count; i++){
		printf("%c\n", A->elemPtr[i]);
	}
}

int main(){
	LIST L;
	
	initList(&L);
	// FIRST ELEMENT
	printf("Insert A in position 0.\n");
	insert(&L,'A',0);
	display(L);
	printf("\ncount: %d\n", L->count);
	// SECOND ELEMENT
	printf("Insert B in position 0.\n");
	insert(&L,'B',0);
	display(L);
	printf("\ncount: %d\n", L->count);
	// THIRD ELEMENT
	printf("Insert C in position 2.\n");
	insert(&L,'C',2);
	display(L);
	printf("\ncount: %d\n", L->count);
	
	return 0;
}