#include <stdio.h>
#define SIZE 10

typedef int Tree[SIZE];

void initTree(Tree T){
	int i;
	for(i = 0; i < SIZE; i++){
		T[i] = -2;
	}
}

void insert(Tree T, int child, int parent){
	if(child < SIZE){
		T[child] = parent;
	}
}

int PARENT(Tree T, int child){
	return T[child];
}

int LEFTMOST_CHILD(Tree T, int parent){
	int i;
	for(i = 0; i < SIZE && T[i] != parent; i++){}
	return (i < SIZE)? i : -2;
}

int RIGHT_SIBLING(Tree T, int child){
	int i;
	for(i = child + 1; i < SIZE && T[i] != T[child]; i++){}	
	return (i < SIZE)? i : -2;
}

int ROOT(Tree T){
	int i;
	for(i = 0; i < SIZE && T[i] != -1; i++){}
	return (i < SIZE)? i : -2;
}

void MAKENULL(Tree T){
	initTree(T);
}

void populate(Tree T){
	int parent[SIZE] = {5,6,5,6,1,-1,5,1,2,-2};
	int i;
	for(i = 0; i < SIZE; i++){
		insert(T,i,parent[i]);
	}
}

void display(Tree T){
	int i;
	printf("The root of the tree is %d\n\n", ROOT(T));
	for(i = 0; i < SIZE; i++){
		printf("[%d] :: %d\n", i, T[i]);
	}
}

int main(){
	Tree T;
	initTree(T);
	populate(T);
	display(T);
	
	printf("\nParent of node 1 is %d", PARENT(T,1));
	printf("\nParent of node 5 is %d", PARENT(T,5));
	printf("\nParent of node 6 is %d", PARENT(T,6));
	printf("\nParent of node 9 is %d", PARENT(T,9));
	
	printf("\n\nLeft child of 1 is %d", LEFTMOST_CHILD(T,1));
	printf("\nLeft child of 5 is %d", LEFTMOST_CHILD(T,5));
	printf("\nLeft child of 6 is %d", LEFTMOST_CHILD(T,6));
	printf("\nLeft child of 8 is %d", LEFTMOST_CHILD(T,8));
	
	printf("\n\nRight sibling of 2 is %d", RIGHT_SIBLING(T,2));
	printf("\nRight sibling of 6 is %d", RIGHT_SIBLING(T,6));
	printf("\nRight sibling of 1 is %d", RIGHT_SIBLING(T,1));
	printf("\nRight sibling of 4 is %d", RIGHT_SIBLING(T,4));
	
	printf("\n\n");
	MAKENULL(T);
	display(T);
	
	return 0;
}