#include <stdio.h>
#define SIZE 10

typedef struct{
	int Elem[SIZE];
	int lastNdx;
}LIST;

void initList(LIST *L){
	L->lastNdx = -1;
}

void insert(LIST *L, int x){
	int child, parent;
	
	if(L->lastNdx < SIZE - 1){
		L->lastNdx++;
		child = L->lastNdx;
		parent = (child - 1) / 2;
		while(child > 0 && L->Elem[parent] > x){
			L->Elem[child] = L->Elem[parent];
			child = parent;
			parent = (child - 1) / 2;
		}
		L->Elem[child] = x;
	}
}

void populate(LIST *L){
	int data[SIZE] = {21,87,12,76,98,8,15,65,43,5};
	int i;
	for(i = 0; i < SIZE; i++){
		insert(L,data[i]);
	}
	
}

void display(LIST L){
	int i;
	for(i = 0; i != L.lastNdx; i++){
		printf("%d, ", L.Elem[i]);
	}
}

int main(){
	LIST L;
	initList(&L);
	
	populate(&L);
	printf("Queue: ");
	display(L);
	
	return 0;
}