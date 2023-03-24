/*
	Introduction:
	Teacher Kraff is a part-time instructor handling 2 courses SP1101 and SP1102. Incentive
	is given to his students, if they join a community extension service (CES) activity.
	Students enrolled in both classes will only attend 1 CES activity. All students in 
	SP1101 had their CES activity last month. Teacher Kraff would like to know who among
	the students in SP1102 have not yet attended a CES activity.
	
	The courses SP1101 and SP11002 are lists represented in memory using cursor list
	implementations. They are both sorted in ascending order according to ID. Given below
	is the definition of the data structure representing the list.
	
	Write the code of the function findCES(). The function will remove all record of students
	in SP1102 that exist in SP1101 to determine the students who have note yet attended the CES
	activity. Note: No function will be called/invoked in this function. Pass the list by address
	only when needed. Only efficient code will get full credit.
*/

#include <stdio.h>
#include <stdlib.h>
#define VH_MAX 0xFF

typedef struct{
	unsigned int ID;
	char FN[24], LN[16], MI;
	char course[8];
	int yrLevel;
}studRec;

typedef struct{
	studRec stud;
	int link;
}CBnode;

typedef struct{
	CBnode heap[VH_MAX];
	int avail;
}*Vheap;

typedef struct{
	int elemPtr; // ndx of 1st element in the list
	int elemCtr; // # of elements in the list
	Vheap VH;
}cursorList;

void initL(cursorList *L){
	int i;
	L->VH = (Vheap)malloc(sizeof(struct{CBnode heap[VH_MAX]; int avail;}));
	
	for(i = 0; i < VH_MAX - 1; i++){
		L->VH->heap[i].link = i + 1;
	}
	L->VH->heap[i].link = -1;
	L->VH->avail = 0;
	L->elemCtr = 0;
	L->elemPtr = -1;
}

int allocSpace(Vheap vh){
	int retVal = vh->avail;
	if(retVal != -1){
		vh->avail = vh->heap[retVal].link;
	}
	return retVal;
}
	
void deallocSpace(Vheap vh, int idx){
	if(idx < VH_MAX && idx >= 0){
		vh->heap[idx].link = vh->avail;
		vh->avail = idx;
	}
}

void insertSorted(cursorList *cl, studRec stud){
	int temp, *trav;
	for(trav = &cl->elemPtr; *trav != -1 && cl->VH->heap[*trav].stud.ID < stud.ID; trav = &cl->VH->heap[*trav].link){}
	temp = allocSpace(cl->VH);
	if(temp != -1){
		cl->VH->heap[temp].stud = stud;
		cl->VH->heap[temp].link = *trav;
		*trav = temp; 
		cl->elemCtr++;
	}
}

void findCES(cursorList SP1101, cursorList *SP1102){
	int temp;
	int *trav = &SP1102->elemPtr;
	
	while(SP1101.elemPtr != -1 && *trav != -1){
		if(SP1102->VH->heap[*trav].stud.ID == SP1101.VH->heap[SP1101.elemPtr].stud.ID){
			temp = *trav;
			*trav = SP1102->VH->heap[temp].link;
			SP1102->VH->heap[temp].link = SP1102->VH->avail;
			SP1102->VH->avail = temp;
			SP1102->elemCtr--;
			SP1101.elemPtr = SP1101.VH->heap[SP1101.elemPtr].link;
		}else if(SP1101.VH->heap[SP1101.elemPtr].stud.ID < SP1102->VH->heap[*trav].stud.ID){
			SP1101.elemPtr = SP1101.VH->heap[SP1101.elemPtr].link;
		}else{
			trav = &SP1102->VH->heap[*trav].link;
		}
	} 
}

void populateSP1101List(cursorList *cl){
	studRec studs[10] = {	{120, "Sally", "Alex", 'A', "BSIT", 4},
							{154, "Vince", "Nash", 'N', "BSIT", 1},
							{121, "Tony", "Erick", 'E', "BSIT", 1},
							{165, "Harlan", "Jensen", 'J', "BSCS", 1},
							{134, "Terry", "Hum", 'H', "BSCS", 2},
							{187, "Serena", "Black", 'B', "BSCS", 2},
							{321, "Salena", "Francis", 'F', "BSIT", 3},
							{875, "Pruds", "Wilkin", 'W', "BSIS", 3},
							{432, "Felicia", "Garra", 'G', "BSIS", 3},
							{455, "Tom", "Higgins", 'H', "BSIS", 3}
						};
	int i;
	for(i = 0; i < 10; i++){
		insertSorted(cl, studs[i]);
	}
}

void populateSP1102List(cursorList *cl){
	studRec studs[8] = {	{176, "Tyrone", "Barlow", 'B', "BSIS", 1},
							{543, "Algern", "Apple", 'A', "BSIS", 1},
							{121, "Tony", "Erick", 'E', "BSIT", 1},
							{874, "Dani", "Mcbride", 'M', "BSIT", 1},
							{454, "Rowena", "Wolfe", 'W', "BSIT", 2},
							{134, "Terry", "Hum", 'H', "BSCS", 2},
							{321, "Salena", "Francis", 'F', "BSIT", 3},
							{879, "Zea", "Davis", 'D', "BSCS", 2}
						};
	int i;
	for(i = 0; i < 8; i++){
		insertSorted(cl, studs[i]);
	}
}

void displayCL(cursorList cl) {
	printf("ID\tFName\t\tMI\tLName\t\tCourse\tYear\n");
    for(; cl.elemPtr != -1; cl.elemPtr = cl.VH->heap[cl.elemPtr].link) {
        printf("%u\t%s\t\t%c.\t%s\t\t%s\t%d\n",
               cl.VH->heap[cl.elemPtr].stud.ID,
               cl.VH->heap[cl.elemPtr].stud.FN,
               cl.VH->heap[cl.elemPtr].stud.MI,
               cl.VH->heap[cl.elemPtr].stud.LN,
               cl.VH->heap[cl.elemPtr].stud.course,
               cl.VH->heap[cl.elemPtr].stud.yrLevel);
    }
    printf("\n");
}

int main(){
	cursorList SP1101, SP1102;
	
	initL(&SP1101);
	initL(&SP1102);
	
	populateSP1101List(&SP1101);
	printf("CLASS SP1101:\nNumber of Students: %d\nIndex of the 1st Element: %d\n", SP1101.elemCtr, SP1101.elemPtr);
	printf("VH Avail: %d\n", SP1101.VH->avail);
	displayCL(SP1101);
	
	printf("SP1101:\nIndex\tLink\n");
	for(int i = 0; i < 15; i++){
		printf("[%d]\t%d\n", i, SP1101.VH->heap[i].link);
	}
	
	populateSP1102List(&SP1102);
	printf("\nBefore Deletion:\nCLASS SP1102:\nNumber of Students: %d\nIndex of the 1st Element: %d\n", SP1102.elemCtr, SP1102.elemPtr);
	printf("VH Avail: %d\n", SP1102.VH->avail);
	displayCL(SP1102);
	
	printf("Before Deletion:\nSP1102:\nIndex\tLink\n");
	for(int i = 0; i < 15; i++){
		printf("[%d]\t%d\n", i, SP1102.VH->heap[i].link);
	}
	
	findCES(SP1101,&SP1102);
	printf("\nAfter Deletion:\nCLASS SP1102:\nNumber of Students: %d\nIndex of the 1st Element: %d\n", SP1102.elemCtr, SP1102.elemPtr);
	printf("VH Avail: %d\n", SP1102.VH->avail);
	displayCL(SP1102);
	
	printf("After Deletion:\nSP1102:\nIndex\tLink\n");
	for(int i = 0; i < 15; i++){
		printf("[%d]\t%d\n", i, SP1102.VH->heap[i].link);
	}
	
	return 0;
}