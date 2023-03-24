#include <stdio.h>

typedef unsigned short int SET;
typedef enum {FALSE, TRUE} boolean;

void initSet(SET *s){
	*s = 0;
}

void insert(SET *s, int x){
	if(x < (int)sizeof(SET) * 8){
		*s |= 1 << x;
	}
}

void deleteS(SET *s, int x){
	if(x < (int)sizeof(SET) * 8){
		*s ^= 1 << x;
	}
}

SET Union(SET A, SET B){
	return A | B;
}

SET Intersection(SET A, SET B){
	return A & B;
}

SET Difference(SET A, SET B){
	return A & ~B;
}

SET Complement(SET A){
	return ~A;
}

boolean isSubset(SET A, SET B){
	return(A & ~B) == 0? TRUE : FALSE;
}

void populateA(SET *s){
	int arr[6] = {1,2,4,7,8,9};
	int i;
	for(i = 0; i < 6; i++){
		insert(s, arr[i]);
	}
}

void populateB(SET *s){
	int arr[4] = {7,3,1,0};
	int i;
	for(i = 0; i < 4; i++){
		insert(s, arr[i]);
	}
}

void display(SET s){
	int gap, mask, bit = (int)sizeof(SET) * 8;
	for(mask = 0, gap = 1; mask < bit; mask++, gap++){
		printf("%d", (s >> mask) & 1);
		if(gap % 4 == 0){
			printf(" ");
		}
	}
}

int main(){
	SET A, B, C, D, E, F;
	
	initSet(&A);
	printf("SET A:\n");
	populateA(&A);
	display(A);
	
	initSet(&B);
	printf("\nSET B:\n");
	populateB(&B);
	display(B);
	
	printf("\n\nDelete 8:\n");
	printf("SET A:\n");
	deleteS(&A, 8);
	display(A);
	
	printf("\n\nDelete 1:\n");
	printf("SET B:\n");
	deleteS(&B, 1);
	display(B);
	
	initSet(&C);
	initSet(&D);
	initSet(&E);
	initSet(&F);
	
	printf("\n\nUnion of SET A and B:\n");
	C = Union(A, B);
	display(C);
	
	printf("\n\nIntersection of SET A and B:\n");
	D = Intersection(A, B);
	display(D);
	
	printf("\n\nDifference of SET A - B:\n");
	E = Difference(A, B);
	display(E);
	
	printf("\n\nComplement of SET A:\n");
	F = Complement(A);
	display(F);
	
	printf(isSubset(A,C) == TRUE? "\n\nTRUE" : "\n\nFALSE");
	
	return 0;
}
