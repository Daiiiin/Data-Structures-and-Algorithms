#include <stdio.h>
#include <stdlib.h>
#include "STACK_LL.h"
#define size_arr 0xA

void populateList(StackL *sl){
	char data[size_arr] = {'a','f','d','n','z','e','l','j','k','s'};
	int i;
	for(i = 0; i < size_arr; i++){
		push(sl,data[i]);
	}
}

void insertSorted(StackL *sl, char elem){
	StackL temp;
	initStack(&temp);
	
	while(isEmpty(*sl) == FALSE && top(*sl) > elem){
		push(&temp,top(*sl));
		pop(sl);
	}
	push(sl,elem);
	while(isEmpty(temp) == FALSE){
		push(sl,top(temp));
		pop(&temp);
	}
}

void sortStack(StackL *sl){
	StackL temp;
	initStack(&temp);
	
	while(isEmpty(*sl) == FALSE){
		push(&temp,top(*sl));
		pop(sl);
	}
	while(isEmpty(temp) == FALSE){
		insertSorted(sl,top(temp));
		pop(&temp);
	}
}

void insertBottom(StackL *sl, char elem){
	StackL temp;
	initStack(&temp);
	
	while(isEmpty(*sl) == FALSE){
		push(&temp,top(*sl));
		pop(sl);
	}
	push(sl,elem);
	while(isEmpty(temp) == FALSE){
		push(sl,top(temp));
		pop(&temp);
	}
}

int main(){
	StackL SL;
	
	initStack(&SL);
	populateList(&SL);
	printf("Initial List:\n");
	display(SL);
	
	printf("\nPOP 2 then PUSH h:\n");
	pop(&SL);
	pop(&SL);
	push(&SL,'h');
	display(SL);
	
	printf("\nInsert Sorted: a and e\n");
	insertSorted(&SL,'a');
	insertSorted(&SL,'e');
	display(SL);
	
	printf("\nSort Stack:\n");
	sortStack(&SL);
	display(SL);
	
	printf("\nInsert Bottom: y\n");
	insertBottom(&SL,'y');
	display(SL);
	
	printf("\nSort Stack:\n");
	sortStack(&SL);
	display(SL);
	
	return 0;
}