#include <stdio.h>
#define MAX 10

typedef struct{
	char Elem[MAX];
	int count;
}LIST;

void initList(LIST* A){
	A->count = 0;
}

void insertPosition(LIST *A, char data, int pos){
	int ctr;
	if(A->count < MAX && pos <= A->count){
		for(ctr = A->count; ctr > pos; ctr--){
			A->Elem[ctr] = A->Elem[ctr-1];
		}
		A->Elem[pos] = data;
		A->count++;
	}else{
		printf("Array is full or position is invalid.\n");
	}
}

void deleteElem(LIST* A, char data){
	int i;
	for(i = 0; i < A->count && A->Elem[i] != data; i++){}
	if(i != A->count){
		for(; i < A->count; i++){
			A->Elem[i] = A->Elem[i+1];
		}
		A->count--;	
	}else{
		printf("Element was not found in the array.\n");
	}
}

void display(LIST A){
	for(int i = 0; i < A.count; i++){
		printf("Index[%d]: %c\n", i, A.Elem[i]);
	}
}

int main(){
	LIST L;
	
	initList(&L);
	// Insert First
	printf("Insert A in position 0:\n");
	insertPosition(&L,'A',0);
	display(L);
	printf("Insert B in position 0:\n");
	insertPosition(&L,'B',0);
	display(L);
	printf("Insert C in position 1:\n");
	insertPosition(&L,'C',1);
	display(L);
	printf("Insert F in position 2:\n");
	insertPosition(&L,'F',2);
	display(L);
	printf("Insert G in position 1:\n");
	insertPosition(&L,'G',1);
	display(L);
	printf("Insert J in position 8:\n");
	insertPosition(&L,'G',8);
	
	printf("\ncount: %d\n", L.count);
	
	// DELETE ELEMENT A
	printf("\nDELETE ELEMENT A\n");
	deleteElem(&L,'A');
	display(L);
	printf("\ncount: %d\n", L.count);
	// DELETE ELEMENT C
	printf("\nDELETE ELEMENT C\n");
	deleteElem(&L,'C');
	display(L);
	printf("\ncount: %d\n", L.count);
	
	return 0;
}
