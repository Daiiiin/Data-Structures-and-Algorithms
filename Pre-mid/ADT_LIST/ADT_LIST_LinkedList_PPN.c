#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char data;
	struct node *link;
}*LIST;

void deleteAllOccurence(LIST *L, char x){
	LIST temp, *trav;
	for(trav = L; *trav != NULL; ){
		if((*trav)->data == x){
			temp = *trav;
			*trav = temp->link;
			free(temp);
		}else{
			trav = &(*trav)->link;
		}
	}
}

void deleteTwoOccurence(LIST *L, char x){
	LIST temp, *trav;
	int ctr = 0;
	for(trav = L; *trav != NULL && ctr != 2; ){
		if((*trav)->data == x){
			temp = *trav;
			*trav = temp->link;
			free(temp);
			ctr++;
		}else{
			trav = &(*trav)->link;
		}
	}
}

void insertSorted(LIST *L, char x){
	LIST *trav;
	for(trav = L; *trav != NULL && (*trav)->data < x; trav = &(*trav)->link){}
	LIST temp = (LIST)malloc (sizeof(struct node));
	if(temp != NULL){
		temp->data = x;
		temp->link = *trav;
		*trav = temp;
	}
}

void insertFirst(LIST *L, char x){
	LIST temp = (LIST)malloc(sizeof(struct node));
	if(temp != NULL){
		temp->data = x;
		temp->link = *L;
		*L = temp;
	}                
}

void displayList(LIST L){
	for(; L != NULL; L = L->link){
		printf("%c ", L->data);
	}
}

void initList(LIST* L){
	*L = NULL;
}

int main(){
	LIST A;
	
	initList(&A);
	insertFirst(&A,'C');
	displayList(A);
	printf("\nInsert Sorted:\n");
	insertSorted(&A,'F');
	insertSorted(&A,'E');
	insertSorted(&A,'A');
	insertSorted(&A,'X');
	insertSorted(&A,'P');
	insertSorted(&A,'F');
	insertSorted(&A,'B');
	insertSorted(&A,'D');
	insertSorted(&A,'F');
	displayList(A);
	printf("\nDelete All Ocuurence: F\n");
	deleteAllOccurence(&A,'F');
	displayList(A);
	printf("\nInsert Sorted: F\n");
	insertSorted(&A,'F');
	insertSorted(&A,'F');
	insertSorted(&A,'F');
	insertSorted(&A,'F');
	displayList(A);
	printf("\nDelete Two Ocuurence: F\n");
	deleteTwoOccurence(&A,'F');
	displayList(A);
	
	return 0;
}