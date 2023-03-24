/*
	A list is implemented as a pointer to a structure containing two arrays, box and next.
	Each element in the list corresponds to a pair (box[x], next[x]), where box[x]
	is the value of the element, and next[x] is the index to the next element in the list.
	In the given illustration below, next[0] holds the index of the first element of
	the list and the index x whose next[x] is 0 indicates the last element of the list.
	
	Given below is the data type definition of the list:
	
	Write the code of function isMember(). The function will return TRUE if the given
	element is an element of the given list; otherwise return FALSE. Note: Only efficient
	code will be given full credit.
	
	NOTE: Added files for practice, does not affect function isMember().
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

typedef struct list{
	char box[SIZE];
	int next[SIZE];
}*LIST;

typedef enum {TRUE, FALSE} boolean;

void initL(LIST *L){
	*L = (LIST)malloc(sizeof(struct list));
}

boolean isMember(LIST L, char data){
	int trav;
	for(trav = L->next[0]; trav != 0 && L->box[trav] != data; trav = L->next[trav]){}
	return (trav != 0)? TRUE : FALSE;
}

void displayL(LIST L){
	int i;
	for(i = 0; i < SIZE; i++){
		printf("box[%d]: %c\tnext[%d]: %d\n", i, L->box[i], i, L->next[i]);
	}
}

int main(){
	LIST L;
	FILE *fp;
	
	initL(&L);
	
	int i;
	L->box[0] = ' ';
	for(i = 1; i < SIZE; i++){
		L->box[i] = 64 + i;
	}
	L->next[0] = 1;
	L->next[1] = 5;
	L->next[2] = 0;
	L->next[3] = 7;
	L->next[4] = -1;
	L->next[5] = 3;
	L->next[6] = -1;
	L->next[7] = 2;
	L->next[8] = -1;
	L->next[9] = -1;
	
	displayL(L);
	
	printf("\nTRUE = 0, FALSE = 1\n");
	printf("\nisMember: A? %s", isMember(L,'A') == 0? "True" : "False"); // 0 TRUE
	printf("\nisMember: B? %s", isMember(L,'B') == 0? "True" : "False"); // 0 TRUE
	printf("\nisMember: C? %s", isMember(L,'C') == 0? "True" : "False"); // 0 TRUE
	printf("\nisMember: D? %s", isMember(L,'D') == 0? "True" : "False"); // 1 FALSE
	printf("\nisMember: E? %s", isMember(L,'E') == 0? "True" : "False"); // 0 TRUE
	printf("\nisMember: F? %s", isMember(L,'F') == 0? "True" : "False"); // 1 FALSE
	printf("\nisMember: G? %s", isMember(L,'G') == 0? "True" : "False"); // 0 TRUE
	printf("\nisMember: H? %s", isMember(L,'H') == 0? "True" : "False"); // 1 FALSE
	printf("\nisMember: I? %s", isMember(L,'I') == 0? "True" : "False"); // 1 FALSE
	printf("\nisMember: Y? %s", isMember(L,'Y') == 0? "True" : "False"); // 1 FALSE
	printf("\nisMember: W? %s", isMember(L,'W') == 0? "True" : "False"); // 1 FALSE
	
	/* 
		HOW THE FUCK DO YOU USE FILES ???
	*/
	fp = fopen("memberList.txt", "w");
	if(fp != NULL){
		fwrite(&L, sizeof(L), sizeof(struct list), fp);
		fclose(fp);
	}
	
	return 0;
}