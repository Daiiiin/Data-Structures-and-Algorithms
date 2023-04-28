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

void deleteNode(BST *S, int x){
	BST *trav, *trav2, temp;
	for(trav = S; *trav != NULL && (*trav)->data != x; ){
		trav = ((*trav)->data < x)? &(*trav)->RC : &(*trav)->LC;
	}
	if(*trav != NULL){
		if((*trav)->LC == NULL && (*trav)->RC == NULL){ // if node is a leaf
			temp = *trav;
			*trav = NULL;
			free(temp);
		}else if((*trav)->LC != NULL && (*trav)->RC == NULL){ // if node has 1 child and child is in left side
			temp = *trav;
			*trav = (*trav)->LC;
			free(temp);
		}else if((*trav)->LC == NULL && (*trav)->RC != NULL){ // if node has 1 child and child is in right side
			temp = *trav;
			*trav = (*trav)->RC;
			free(temp);
		}else{ // if node has 2 child
			for(trav2 = &(*trav)->RC; (*trav2)->LC != NULL; trav2 = &(*trav2)->LC){}
			temp = *trav2;
			*trav2 = temp->RC;
			(*trav)->data = temp->data;
			free(temp);
		}
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

int min(BST S){
	for(; S->LC != NULL; S = S->LC){}
	return S->data;
}

int max(BST S){
	for(; S->RC != NULL; S = S->RC){}
	return S->data;
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
	
	printf("\nMin data in the tree:\n");
	printf("Min: %d\n", min(S));
	
	printf("\nMax data in the tree:\n");
	printf("Max: %d\n", max(S));
	
	printf("\nDelete data: 34\n");
	deleteNode(&S,34);
	
	printf("\nPreordered List: ");
	preOrder(S);
	
	printf("\n\nInordered List: ");
	inOrder(S);
	
	printf("\n\nPostordered List: ");
	postOrder(S);
	
	return 0;
}