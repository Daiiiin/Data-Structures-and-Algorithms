#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int SET[MAX];

/*
	1 = TRUE, 0 = FALSE
	The elements of the SET are represented by 1 in the array.
	EXAMPLE.
	index:	[0,1,2,3,4,5,6,7]
	SET A = {0,1,1,0,1,0,0,1}, this means that the elements of SET A are 1,2,4,7
*/

SET *Union(SET A, SET B){
	SET *retVal;
	int i;
	retVal = (SET*)malloc(sizeof(SET));
	if(retVal != NULL){
		for(i = 0; i < MAX; i++){
			(*retVal)[i] = A[i] | B[i];
		}
	}
	return retVal;
}

SET *Intersection(SET A, SET B){
	SET *retVal;
	int i;
	retVal = (SET*)malloc(sizeof(SET));
	if(retVal != NULL){
		for(i = 0; i < MAX; i++){
			(*retVal)[i] = A[i] & B[i];
		}
	}
	return retVal;
}

SET *Difference(SET A, SET B){
	SET *retVal;
	int i;
	retVal = (SET*)malloc(sizeof(SET));
	if(retVal != NULL){
		for(i = 0; i < MAX; i++){
			(*retVal)[i] = A[i] & ~B[i];
		}
	}
	return retVal;
}

void displaySet(SET A){
	int i;
	for(i = 0; i < MAX; i++){
		if(A[i] == 1){
			printf("%d ", i);
		}
	}
}

int main(){
	SET A = {0,1,0,1,1};
	SET B = {1,1,0,1,0,0,0,1};
	SET *C = Union(A,B);
	SET *D = Intersection(A,B);
	SET *E = Difference(A,B);
	
	printf("SET A:\n");
	displaySet(A);
	printf("\nSET B:\n");
	displaySet(B);
	printf("\nUnion of SET A and B:\n");
	displaySet(*C);
	printf("\nIntersection of SET A and B:\n");
	displaySet(*D);
	printf("\nDifference of SET A and B:\n");
	displaySet(*E);
	
	return 0;
}