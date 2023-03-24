#include <stdio.h>
#define MAX 0xA
#define arr_size1 5
#define arr_size2 3

typedef struct{
	char data;
	int link;
}nodetype;

typedef struct{
	nodetype nodes[MAX];
	int avail;
}VirtualHeap;

typedef int LIST;

// START FROM BOTTOM arr[0] TO TOP arr[MAX-1]
void initVHeap(VirtualHeap *vh){
	int i;
	for(i = 0; i < MAX - 1; i++){
		vh->nodes[i].link = i + 1;
	}
	vh->nodes[i].link = -1;
	vh->avail = 0;
}

void initList(LIST *L){
	*L = -1;
}

// ALLOCATE SPACE FOR INSERT; RETURNS -1 IF NO MORE SPACE
int allocSpace(VirtualHeap *vh){
	int retVal = vh->avail;
	if(retVal != -1){
		vh->avail = vh->nodes[retVal].link;
	}
	return retVal;
}

// FREE SPACE
void deallocSpace(VirtualHeap *vh, int idx){
	if(idx < MAX && idx >= 0){
		vh->nodes[idx].link = vh->avail;
		vh->avail = idx;
	}
}

void insertFirst(VirtualHeap *vh, LIST *L, char elem){
	int temp;
	temp = allocSpace(vh);
	if(temp != -1){
		vh->nodes[temp].data = elem;
		vh->nodes[temp].link = *L;
		*L = temp;
	}	
}

void insertLast(VirtualHeap *vh, LIST *L, char elem){
	LIST *trav;
	for(trav = L; *trav != -1; trav = &vh->nodes[*trav].link){}
	*trav = allocSpace(vh);
	if(*trav != -1){
		vh->nodes[*trav].data = elem;
		vh->nodes[*trav].link = -1;
	}else{
		printf("\nOut of space!\n");
	}
}

void deleteElem(VirtualHeap *vh, LIST *L, char elem){
	LIST *trav, temp;
	for(trav = L; *trav != -1 && vh->nodes[*trav].data != elem; trav = &vh->nodes[*trav].link){}
	if(*trav != -1){
		temp = *trav;
		*trav = vh->nodes[temp].link;
		deallocSpace(vh,temp);
	}
}

void deleteAllOccurence(VirtualHeap *vh, LIST *L, char elem){
	LIST *trav, temp;
	for(trav = L; *trav != -1; ){
		if(vh->nodes[*trav].data == elem){
			temp = *trav;
			*trav = vh->nodes[temp].link;
			deallocSpace(vh,temp);
		}else{
			trav = &vh->nodes[*trav].link;
		}
	}
}

void populateList(VirtualHeap *vh, LIST *L){
	char data[arr_size1] = {'H','E','L','L','O'};
	int i;
	for(i = 0; i < arr_size1; i++){
		insertLast(vh,L,data[i]);
	}
}

void populateList2(VirtualHeap *vh, LIST *L){
	char data[arr_size2] = {'U','S','C'};
	int i;
	for(i = 0; i < arr_size2; i++){
		insertLast(vh,L,data[i]);
	}
}

void displayList(VirtualHeap vh, LIST L){
	for(; L != -1; L = vh.nodes[L].link){
		printf("%c ", vh.nodes[L].data);
	}
}

int main(){
	VirtualHeap VH;
	LIST L;
	LIST L2;

	printf("TASK 1: Insert last\n");
	initVHeap(&VH);
	initList(&L);
	populateList(&VH,&L);
	displayList(VH,L);
	
	printf("\n\nDELETE E\n");
	deleteElem(&VH,&L,'E');
	displayList(VH,L);
	
	printf("\n\nTASK 2: Create new list L2\n");
	initList(&L2);
	populateList2(&VH,&L2);
	displayList(VH,L2);
	
	printf("\n\nTASK 3: Delete all occurence L\n");
	deleteAllOccurence(&VH,&L,'L');
	displayList(VH,L);
	
	printf("\n\nINSERT FIRST: I\n");
	insertFirst(&VH,&L,'I');
	displayList(VH,L);
	printf("\n\nINSERT FIRST: J\n");
	insertFirst(&VH,&L,'J');
	displayList(VH,L);
	
	printf("\n\nL1: %d\nL2: %d\navail: %d\n-------------\n", L, L2, VH.avail);
	printf("Links: ");
	for(int i = 0; i < MAX; i++){
		printf("%d ", VH.nodes[i].link);
	}
	printf("\n-------------\n");
	
	return 0;
}
