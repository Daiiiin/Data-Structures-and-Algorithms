#include <stdio.h>
#define SIZE 10

typedef struct{
	int Elem[SIZE];
	int lastNdx;
}HEAP;

/*
	Visual Represntation of POT
				  5
			 /   	 \
			8      	  12
		  /  \		/   \
	   65    43    21	15
	 /  \   /
	87  76 98
*/

void initList(HEAP *L){
	L->lastNdx = -1;
}

void insert(HEAP *L, int x){
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

void MinHeapify(HEAP *L){
	int lowP, parNdx, child, temp;
	if(L->lastNdx != -1){
		lowP = (L->lastNdx - 1) / 2;
		while(lowP >= 0){
			parNdx = lowP;
			child = (parNdx * 2) + 1;
			if(child + 1 <= L->lastNdx && L->Elem[child + 1] < L->Elem[child]){
				child++;
			}
			if(L->Elem[parNdx] > L->Elem[child]){
				temp = L->Elem[parNdx];
				L->Elem[parNdx] = L->Elem[child];
				L->Elem[child] = temp;
				parNdx = child;
				child = (parNdx * 2) + 1;
			}
			lowP--;
		}
	}
}

int deleteMin(HEAP *L){
	int retVal, p = 0, child, temp;
	
	if(L->lastNdx == -1){ // P.O.T is empty
		retVal = -1;
	}else{
		retVal = L->Elem[p];
		L->Elem[p] = L->Elem[L->lastNdx];	
		L->lastNdx--;
		child = 1;
		while(child <= L->lastNdx){
			if(child <= L->lastNdx && L->Elem[child + 1] < L->Elem[child]){
				child++;
			}
			if(L->Elem[p] > L->Elem[child]){
				temp = L->Elem[p];
				L->Elem[p] = L->Elem[child];
				L->Elem[child] = temp;
				p = child;
				child = (p * 2) + 1;
			}
		}
	}
	return retVal;
}

void MinHeapSort(HEAP *L){
	int orig, temp;
	orig = L->lastNdx;
	while(L->lastNdx != -1){
		temp = deleteMin(L);
		L->Elem[L->lastNdx+1] = temp;
	}
	L->lastNdx = orig;
}

void populate(HEAP *L){
	int data[SIZE] = {21,87,12,76,98,8,15,65,43,5};
	int i;
	for(i = 0; i < SIZE; i++){
		insert(L,data[i]);
	}
	
}

void display(HEAP L){
	int i;
	for(i = 0; i <= L.lastNdx; i++){
		printf("[%d] :: %d\n", i, L.Elem[i]);
	}
	printf("Last Index: %d\n", L.lastNdx);
}

int main(){
	HEAP L;
	initList(&L);

	populate(&L);
	printf("P.O.T\n");
	display(L);
	
	printf("\nDelete Min:\n");
	printf("Min: %d\n", deleteMin(&L));
	display(L);
	
	printf("\nHeapify:\n");
	MinHeapify(&L);
	display(L);
	
	printf("\nHeap Sort:\n");
	MinHeapSort(&L);
	display(L);
	
	return 0;
}
