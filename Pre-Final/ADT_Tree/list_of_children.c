#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct node{
	int data;
	struct node *link;
}*LIST;

typedef struct{
	LIST nodes[SIZE];
	int root;
}Tree;

void initTree(Tree *T){
	int i;
	for(i = 0; i < SIZE; i++){
		T->nodes[i] = NULL;
	}
	T->root = -1;
}

void insertRoot(Tree *T, int n){
	if(T->root == -1){
		T->root = n;
	}
}

void insert(Tree *T, int parent, int child){
	LIST *trav, temp;
	if(parent < SIZE){
		for(trav = &T->nodes[parent]; *trav != NULL; trav = &(*trav)->link){}
		temp = (LIST)malloc(sizeof(struct node));
		if(temp != NULL){
			temp->data = child;
			temp->link = *trav;
			*trav = temp;
		}
	}
}

int PARENT(Tree T, int child){
	int i, retVal = -2;
	LIST trav;
	if(child == T.root){
		retVal = -1;
	}else{
		for(i = 0; i < SIZE; i++){
			for(trav = T.nodes[i]; trav != NULL; trav = trav->link){
				if(trav->data == child){
					retVal = i;
				}
			}
		}		
	}
	return retVal;
}

int LEFTMOST_CHILD(Tree T, int parent){
	return (T.nodes[parent] != NULL)? T.nodes[parent]->data : -2;
}

int RIGHT_SIBLING(Tree T, int child){
	int i, p, retVal = -2;
	LIST trav;
	if(child == T.root){
		retVal = -1;
	}else{
		p = PARENT(T,child);
		for(trav = T.nodes[p]; trav != NULL && trav->link != NULL; trav = trav->link){
			if(trav->data == child){
				retVal = trav->link->data;
			}
		}
	}
	return retVal;
}

int ROOT(Tree T){
	return T.root;
}

void populate(Tree *T){
	insertRoot(T,5);
	insert(T,1,4);
	insert(T,1,7);
	insert(T,2,8);
	insert(T,5,0);
	insert(T,5,6);
	insert(T,5,2);
	insert(T,6,3);
	insert(T,6,1);
}

void display(Tree T){
	int i;
	LIST trav;
	printf("The root of the tree is %d\n\n", T.root);
	for(i = 0 ; i < SIZE; i++){
		printf("[%d] :: ", i);
		for(trav = T.nodes[i]; trav != NULL; trav = trav->link){
			printf("%d -> ", trav->data);
		}
		printf("\n");
	}
}

int main(){
	Tree T;
	initTree(&T);
	populate(&T);
	display(T);
	
	printf("\nParent of 1 is %d", PARENT(T,1));
	printf("\nParent of 5 is %d", PARENT(T,5));
	printf("\nParent of 6 is %d", PARENT(T,6));
	printf("\nParent of 9 is %d", PARENT(T,9));
	
	printf("\n\nLeft child of 1 is %d", LEFTMOST_CHILD(T,1));
	printf("\nLeft child of 5 is %d", LEFTMOST_CHILD(T,5));
	printf("\nLeft child of 6 is %d", LEFTMOST_CHILD(T,6));
	printf("\nLeft child of 8 is %d", LEFTMOST_CHILD(T,8));
	
	printf("\n\nRight sibling of 3 is %d", RIGHT_SIBLING(T,3));
	printf("\nRight sibling of 6 is %d", RIGHT_SIBLING(T,6));
	printf("\nRight sibling of 5 is %d", RIGHT_SIBLING(T,5));
	printf("\nRight sibling of 7 is %d", RIGHT_SIBLING(T,7));
	
	return 0;
}