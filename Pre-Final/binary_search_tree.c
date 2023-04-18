#include <stdio.h>
#include <stdlib.h>
#define a_size 10

typedef struct cell{
	int data;
	struct cell *LC;
	struct cell *RC;
}cType, *BST;

typedef enum {TRUE, FALSE} boolean;

/*
	Visual Representation of tree
				20
			  /   \
			15     34
		   /  \   /  \
		  7   16 21   38
	 	/  \       \
	   5   13       30
*/

/* 
	/_ preorder

	_\ postorder

	/\_ inorder
*/

void initBST(BST *S){
	*S = NULL;
}

void preOrder(BST S){
	if(S != NULL){
		printf("%d, ", S->data);
		preOrder(S->LC);
		preOrder(S->RC);
	}
}

void inOrder(BST S){
	if(S != NULL){
		inOrder(S->LC);
		printf("%d, ", S->data);
		inOrder(S->RC);
	}
}

void postOrder(BST S){
	if(S != NULL){
		postOrder(S->LC);
		postOrder(S->RC);
		printf("%d, ", S->data);
	}
}

void insert(BST *S, int data){
	BST *trav;
	for(trav = S; *trav != NULL && (*trav)->data != data;){
		trav = ((*trav)->data < data)? &(*trav)->RC : &(*trav)->LC;
	}
	if(*trav != NULL){
		printf("\nData already exist.\n");
	}else{
		*trav = (BST)malloc(sizeof(cType));
		if(*trav != NULL){
			(*trav)->data = data;
			(*trav)->LC = NULL;
			(*trav)->RC = NULL;
		}
	}
}

boolean isMember(BST S, int x){
	while(S != NULL && S->data != x){
		S = (S->data < x)? S->RC : S->LC;
	}
	return (S != NULL)? TRUE : FALSE;
}

void populate(BST *S){
	int data[a_size] = {20,34,38,21,15,16,30,7,13,5};
	int i;
	for(i = 0; i < a_size; i++){
		insert(S,data[i]);
	}
}

int main(){
	BST S;
	initBST(&S);
	populate(&S);
	
	printf("Preordered List: ");
	preOrder(S);
	
	printf("\n\nInordered List: ");
	inOrder(S);
	
	printf("\n\nPostordered List: ");
	postOrder(S);
	
	printf("\n\nInsert test case with data that exists: 38");
	insert(&S,38);
	
	printf("\nisMember Function:\n");
	printf("5 is a member? %s\n", isMember(S,5) == TRUE? "TRUE" : "FALSE");
	printf("1 is a member? %s\n", isMember(S,1) == TRUE? "TRUE" : "FALSE");
	printf("84 is a member? %s\n", isMember(S,84) == TRUE? "TRUE" : "FALSE");
	printf("38 is a member? %s\n", isMember(S,38) == TRUE? "TRUE" : "FALSE");
	
	return 0;
}
