#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef int SET[MAX];

/*
	A[i] || B[i] is the same as A[i] == 1 || B[i] == 1
	A[i] && B[i] is the same as A[i] == 1 && B[i] == 1
	This will work since the elements are just 1's and 0's.
	Will not work otherwise.
	
	1 = TRUE, 0 = FALSE
	The elements of the SET are represented by 1 in the array.
	EXAMPLE.
	index:	[0,1,2,3,4,5,6,7]
	SET A = {0,1,1,0,1,0,0,1}, this means that the elements of SET A are 1,2,4,7
*/

void initSet(SET s){
	int i;
	for(i = 0; i < MAX; i++){
		s[i] = 0;
	}
}

SET *Union(SET A, SET B){
	SET *retVal;
	int i;
	retVal = (SET*)malloc(sizeof(SET));
	initSet(*retVal);
	if(retVal != NULL){
		for(i = 0; i < MAX; i++){
			(*retVal)[i] = A[i] || B[i];
		}
	}
	return retVal;
}

SET *Intersection(SET A, SET B){
	SET *retVal;
	int i;
	retVal = (SET*)malloc(sizeof(SET));
	initSet(*retVal);
	if(retVal != NULL){
		for(i = 0; i < MAX; i++){
			(*retVal)[i] = A[i] && B[i];
		}
	}
	return retVal;
}

SET *Difference(SET A, SET B){
	SET *retVal;
	int i;
	retVal = (SET*)malloc(sizeof(SET));
	initSet(*retVal);
	if(retVal != NULL){
		for(i = 0; i < MAX; i++){
			(*retVal)[i] = (A[i] == 1 && B[i] == 0)? 1 : 0;
		}
	}
	return retVal;
}

void displaySet(SET A){
	int i;
	for(i = 0; i < MAX; i++){
		printf("%d ", A[i]);
	}
	printf("\n");
	for(i = 0; i < MAX; i++){
		if(A[i] == 1){
			printf("%d ", i);
		}
	}
}

void insert(SET s, int idx){
	if(idx < MAX){
		s[idx] = 1;
	}
}

void populateA(SET s){
	int A[6] = {1,2,4,7,8,9};
	int i;
	for(i = 0; i < 6; i++){
		insert(s, A[i]);
	}
}

void populateB(SET s){
	int B[4] = {7,3,1,0};
	int i;
	for(i = 0; i < 4; i++){
		insert(s, B[i]);
	}
}

int main(){
	SET A;
	SET B;
	// initialize set
	initSet(A);
	initSet(B);
	// populate set
	populateA(A);
	populateB(B);
	// union
	SET *C = Union(A,B);
	// intersection
	SET *D = Intersection(A,B);
	// difference (complement)
	SET *E = Difference(A,B);
	
	printf("SET A:\n");
	displaySet(A);
	printf("\nSET B:\n");
	displaySet(B);
	printf("\nUnion of SET A and B:\n");
	displaySet(*C);
	printf("\nIntersection of SET A and B:\n");
	displaySet(*D);
	printf("\nDifference of SET A - B:\n");
	displaySet(*E);
	
	return 0;
}
