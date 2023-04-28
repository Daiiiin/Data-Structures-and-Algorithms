#include <stdio.h>
#define SIZE 10

typedef struct{
	int Elem[SIZE];
	int count;
}LIST;

/* 
	NOTE: LIST must be sorted in ascending order
*/

void initList(LIST *L){
	L->count = 0;
}

int findElem(LIST L, int x){
	int LB = 0, UB = L.count - 1;
	int mid = (LB + UB) / 2;
	while(LB <= UB && x != L.Elem[mid]){
		(x < L.Elem[mid])? (UB = mid - 1) : (LB = mid + 1);
		mid = (LB + UB) / 2;
	}
	return (LB <= UB)? 1 : 0;
}

void populate(LIST *L){
	int i;
	int data[SIZE] = {12,18,21,41,54,56,61,76,87,98};
	for(i = 0; i < SIZE; i++){
		L->Elem[L->count] = data[i];
		L->count++;
	}
}

void display(LIST L){
	int i;
	printf("LIST: ");
	for(i = 0; i < SIZE; i++){
		printf("%d ", L.Elem[i]);
	}
	printf("\nCount: %d", L.count);
}

int main(){
	LIST L;
	initList(&L);
	populate(&L);
	display(L);
	
	printf("\n\nSearching using Binary Search:");
	printf("\n41 is a member? %s", findElem(L,41) == 1? "TRUE" : "FALSE");
	printf("\n10 is a member? %s", findElem(L,10) == 1? "TRUE" : "FALSE");
	printf("\n61 is a member? %s", findElem(L,61) == 1? "TRUE" : "FALSE");
	printf("\n18 is a member? %s", findElem(L,18) == 1? "TRUE" : "FALSE");
	
	return 0;
}